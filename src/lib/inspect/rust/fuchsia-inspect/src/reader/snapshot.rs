// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

use {
    crate::{
        format::{bitfields::BlockHeader, block::Block, block_type::BlockType, constants},
        utils, Inspector,
    },
    anyhow::{format_err, Error},
    fuchsia_zircon::Vmo,
    std::{
        convert::{TryFrom, TryInto},
        sync::atomic::{fence, Ordering},
    },
};

pub use crate::reader::tree_reader::SnapshotTree;

/// Enables to scan all the blocks in a given buffer.
pub struct Snapshot {
    /// The buffer read from an Inspect VMO.
    buffer: Vec<u8>,

    version: usize,
}

/// A scanned block.
pub type ScannedBlock<'a> = Block<&'a [u8]>;

const SNAPSHOT_TRIES: u64 = 1024;

impl Snapshot {
    /// Returns an iterator that returns all the Blocks in the buffer.
    pub fn scan(&self) -> BlockIterator {
        return BlockIterator::new(self.buffer.as_ref(), self.version);
    }

    /// Gets the block at the given |index|.
    pub fn get_block(&self, index: u32) -> Option<ScannedBlock> {
        if utils::offset_for_index(index) < self.buffer.len() {
            Some(Block::new_with_version(&self.buffer, index, self.version))
        } else {
            None
        }
    }

    /// Try to take a consistent snapshot of the given VMO once.
    ///
    /// Returns a Snapshot on success or an Error if a consistent snapshot could not be taken.
    pub fn try_once_from_vmo(vmo: &Vmo) -> Result<Snapshot, Error> {
        Snapshot::try_once_with_callback(vmo, &mut || {})
    }

    fn try_once_with_callback<F>(vmo: &Vmo, first_read_callback: &mut F) -> Result<Snapshot, Error>
    where
        F: FnMut() -> (),
    {
        let mut header_bytes: [u8; 16] = [0; 16];
        vmo.read(&mut header_bytes, 0)?;

        let generation = header_generation_count(&header_bytes[..]);

        if cfg!(test) {
            first_read_callback();
        }

        if let Some(gen) = generation {
            let size = vmo.get_size()?;
            let mut buffer = vec![0u8; size as usize];
            vmo.read(&mut buffer[..], 0)?;
            let header = BlockHeader(u64::from_le_bytes(buffer[..8].try_into().unwrap()));
            let mut expected_version = constants::HEADER_VERSION_NUMBER;
            let mut block = Block::new_with_version(&buffer[..16], 0, 1);
            if header.header_version() == 0 {
                block.make_v0();
                expected_version = 0;
            }
            if block.block_type_or().unwrap_or(BlockType::Reserved) == BlockType::Header
                && block.header_magic().unwrap() == constants::HEADER_MAGIC_NUMBER
                && block.header_version().unwrap() == expected_version
                && block.header_generation_count().unwrap() == gen
            {
                let version = block.version.unwrap();
                return Ok(Snapshot { buffer, version });
            }
        }

        Err(format_err!("Failed to get consistent snapshot"))
    }

    fn try_from_with_callback<F>(vmo: &Vmo, mut first_read_callback: F) -> Result<Snapshot, Error>
    where
        F: FnMut() -> (),
    {
        for _ in 0..SNAPSHOT_TRIES {
            if let Ok(ret) = Snapshot::try_once_with_callback(&vmo, &mut first_read_callback) {
                return Ok(ret);
            }
        }
        Err(format_err!("Failed to read snapshot from vmo"))
    }

    // Used for snapshot tests.
    #[cfg(test)]
    pub fn build(bytes: &[u8]) -> Self {
        Snapshot { buffer: bytes.to_vec(), version: 1 }
    }
}

/// Reads the given 16 bytes as an Inspect Block Header and returns the
/// generation count if the header is valid: correct magic number, version number
/// and nobody is writing to it.
fn header_generation_count(bytes: &[u8]) -> Option<u64> {
    if bytes.len() < 16 {
        return None;
    }
    fence(Ordering::Acquire);
    let header = BlockHeader(u64::from_le_bytes(bytes[..8].try_into().unwrap()));
    let mut expected_version = constants::HEADER_VERSION_NUMBER;
    let mut block = Block::new_with_version(&bytes[..16], 0, 1);
    if header.header_version() == 0 {
        block.make_v0();
        expected_version = 0;
    }
    if block.block_type_or().unwrap_or(BlockType::Reserved) == BlockType::Header
        && block.header_magic().unwrap() == constants::HEADER_MAGIC_NUMBER
        && block.header_version().unwrap() == expected_version
        && !block.header_is_locked().unwrap()
    {
        return block.header_generation_count().ok();
    }
    None
}

/// Construct a snapshot from a byte array.
impl TryFrom<&[u8]> for Snapshot {
    type Error = anyhow::Error;

    fn try_from(bytes: &[u8]) -> Result<Self, Self::Error> {
        if header_generation_count(&bytes).is_some() {
            Ok(Snapshot { buffer: bytes.to_vec(), version: 1 })
        } else {
            return Err(format_err!("expected block with at least a header"));
        }
    }
}

/// Construct a snapshot from a byte vector.
impl TryFrom<Vec<u8>> for Snapshot {
    type Error = anyhow::Error;

    fn try_from(bytes: Vec<u8>) -> Result<Self, Self::Error> {
        Snapshot::try_from(&bytes[..])
    }
}

/// Construct a snapshot from a VMO.
impl TryFrom<&Vmo> for Snapshot {
    type Error = anyhow::Error;

    fn try_from(vmo: &Vmo) -> Result<Self, Self::Error> {
        Snapshot::try_from_with_callback(vmo, || {})
    }
}

impl TryFrom<&Inspector> for Snapshot {
    type Error = anyhow::Error;

    fn try_from(inspector: &Inspector) -> Result<Self, Self::Error> {
        inspector
            .vmo
            .as_ref()
            .ok_or(format_err!("Cannot read from no-op Inspector"))
            .and_then(|vmo| Snapshot::try_from(&**vmo))
    }
}

/// Iterates over a byte array containing Inspect API blocks and returns the
/// blocks in order.
pub struct BlockIterator<'h> {
    /// Current offset at which the iterator is reading.
    offset: usize,

    /// The bytes being read.
    container: &'h [u8],

    version: usize,
}

impl<'a> From<&'a [u8]> for BlockIterator<'a> {
    fn from(container: &'a [u8]) -> Self {
        BlockIterator { offset: 0, container: container, version: 1 }
    }
}

impl<'a> BlockIterator<'a> {
    fn new(container: &'a [u8], version: usize) -> Self {
        Self { container, offset: 0, version }
    }
}

impl<'h> Iterator for BlockIterator<'h> {
    type Item = Block<&'h [u8]>;

    fn next(&mut self) -> Option<Block<&'h [u8]>> {
        if self.offset >= self.container.len() {
            return None;
        }
        let index = utils::index_for_offset(self.offset);
        let block = Block::new_with_version(self.container.clone(), index, self.version);
        if self.container.len() - self.offset < utils::order_to_size(block.order()) {
            return None;
        }
        self.offset += utils::order_to_size(block.order());
        Some(block)
    }
}

#[cfg(test)]
mod tests {
    use {
        super::*,
        crate::format::{
            bitfields::{BlockHeader, Payload},
            block::WritableBlockContainer,
        },
        mapped_vmo::Mapping,
        num_traits::ToPrimitive,
        std::sync::Arc,
    };

    #[test]
    fn scan() -> Result<(), Error> {
        let (mapping, vmo) = Mapping::allocate(4096)?;
        let mapping_ref = Arc::new(mapping);
        let mut header = Block::new_free(mapping_ref.clone(), 0, 0, 0)?;
        header.become_reserved()?;
        header.become_header()?;

        let b = Block::new_free(mapping_ref.clone(), 1, 2, 0)?;
        b.become_reserved()?;
        b.become_extent(5)?;
        let b = Block::new_free(mapping_ref.clone(), 5, 0, 0)?;
        b.become_reserved()?;
        b.become_int_value(1, 2, 3)?;

        let snapshot = Snapshot::try_from(&vmo)?;

        // Scan blocks
        let blocks = snapshot.scan().collect::<Vec<ScannedBlock>>();

        assert_eq!(blocks[0].block_type(), BlockType::Header);
        assert_eq!(blocks[0].index(), 0);
        assert_eq!(blocks[0].order(), 0);
        assert_eq!(blocks[0].header_magic().unwrap(), constants::HEADER_MAGIC_NUMBER);
        assert_eq!(blocks[0].header_version().unwrap(), constants::HEADER_VERSION_NUMBER);

        assert_eq!(blocks[1].block_type(), BlockType::Extent);
        assert_eq!(blocks[1].index(), 1);
        assert_eq!(blocks[1].order(), 2);
        assert_eq!(blocks[1].next_extent().unwrap(), 5);

        assert_eq!(blocks[2].block_type(), BlockType::IntValue);
        assert_eq!(blocks[2].index(), 5);
        assert_eq!(blocks[2].order(), 0);
        assert_eq!(blocks[2].name_index().unwrap(), 2);
        assert_eq!(blocks[2].parent_index().unwrap(), 3);
        assert_eq!(blocks[2].int_value().unwrap(), 1);
        assert!(blocks[6..].iter().all(|b| b.block_type() == BlockType::Free));

        // Verify get_block
        assert_eq!(snapshot.get_block(0).unwrap().block_type(), BlockType::Header);
        assert_eq!(snapshot.get_block(1).unwrap().block_type(), BlockType::Extent);
        assert_eq!(snapshot.get_block(5).unwrap().block_type(), BlockType::IntValue);
        assert_eq!(snapshot.get_block(6).unwrap().block_type(), BlockType::Free);
        assert!(snapshot.get_block(4096).is_none());

        Ok(())
    }

    #[test]
    fn invalid_type() -> Result<(), Error> {
        let (mapping, vmo) = Mapping::allocate(4096)?;
        let mapping_ref = Arc::new(mapping);
        mapping_ref.write_bytes(0, &[0x00, 0xff, 0x01]);
        assert!(Snapshot::try_from(&vmo).is_err());
        Ok(())
    }

    #[test]
    fn invalid_order() -> Result<(), Error> {
        let (mapping, vmo) = Mapping::allocate(4096)?;
        let mapping_ref = Arc::new(mapping);
        mapping_ref.write_bytes(0, &[0xff, 0xff]);
        assert!(Snapshot::try_from(&vmo).is_err());
        Ok(())
    }

    #[test]
    fn invalid_pending_write() -> Result<(), Error> {
        let (mapping, vmo) = Mapping::allocate(4096)?;
        let mapping_ref = Arc::new(mapping);
        let mut header = Block::new_free(mapping_ref.clone(), 0, 0, 0)?;
        header.become_reserved()?;
        header.become_header()?;
        header.lock_header()?;
        assert!(Snapshot::try_from(&vmo).is_err());
        Ok(())
    }

    #[test]
    fn invalid_magic_number() -> Result<(), Error> {
        let (mapping, vmo) = Mapping::allocate(4096)?;
        let mapping_ref = Arc::new(mapping);
        let mut header = Block::new_free(mapping_ref.clone(), 0, 0, 0)?;
        header.become_reserved()?;
        header.become_header()?;
        header.set_header_magic(3)?;
        assert!(Snapshot::try_from(&vmo).is_err());
        Ok(())
    }

    #[test]
    fn invalid_generation_count() -> Result<(), Error> {
        let (mapping, vmo) = Mapping::allocate(4096)?;
        let mapping_ref = Arc::new(mapping);
        let mut header = Block::new_free(mapping_ref.clone(), 0, 0, 0)?;
        header.become_reserved()?;
        header.become_header()?;
        assert!(Snapshot::try_from_with_callback(&vmo, || {
            header.lock_header().unwrap();
            header.unlock_header().unwrap();
        })
        .is_err());
        Ok(())
    }

    #[test]
    fn snapshot_from_few_bytes() {
        let values = (0u8..16).collect::<Vec<u8>>();
        assert!(Snapshot::try_from(&values[..]).is_err());
        assert!(Snapshot::try_from(values).is_err());
        assert!(Snapshot::try_from(vec![]).is_err());
        assert!(Snapshot::try_from(vec![0u8, 1, 2, 3, 4]).is_err());
    }

    #[test]
    fn snapshot_v0() -> Result<(), Error> {
        let (mapping, vmo) = Mapping::allocate(4096).expect("failed to allocate");
        let mapping_ref = Arc::new(mapping);
        let header_block = Block::new_free(mapping_ref.clone(), 0, 0, 0)
            .expect("failed to create free for header");
        let mut header = BlockHeader(0);
        header.set_order(0);
        header.set_block_type_v0(BlockType::Header.to_u8().unwrap());
        header.set_header_magic(constants::HEADER_MAGIC_NUMBER);
        header.set_header_version_v0(0);
        header_block.write(header, Payload(0));

        let some_block =
            Block::new_free(mapping_ref.clone(), 1, 0, 0).expect("failed to create free for vlaue");
        let mut header = BlockHeader(0);
        header.set_order(0);
        header.set_block_type_v0(BlockType::UintValue.to_u8().unwrap());
        header.set_value_name_index_v0(1);
        header.set_value_parent_index_v0(2);
        let mut payload = Payload(0);
        payload.set_numeric_value(123);
        some_block.write(header, payload);

        let snapshot = Snapshot::try_from(&vmo).expect("Failed to load snapshot");

        let blocks = snapshot.scan().collect::<Vec<ScannedBlock>>();

        assert_eq!(blocks[0].block_type(), BlockType::Header);
        assert_eq!(blocks[0].index(), 0);
        assert_eq!(blocks[0].order(), 0);
        assert_eq!(blocks[0].header_magic().unwrap(), constants::HEADER_MAGIC_NUMBER);
        assert_eq!(blocks[0].header_version().unwrap(), 0);

        assert_eq!(blocks[1].block_type(), BlockType::UintValue);
        assert_eq!(blocks[1].index(), 1);
        assert_eq!(blocks[1].order(), 0);
        assert_eq!(blocks[1].name_index().unwrap(), 1);
        assert_eq!(blocks[1].parent_index().unwrap(), 2);
        assert_eq!(blocks[1].uint_value().unwrap(), 123);
        assert!(blocks[2..].iter().all(|b| b.block_type() == BlockType::Free));
        Ok(())
    }
}
