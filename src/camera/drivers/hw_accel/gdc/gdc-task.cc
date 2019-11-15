// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gdc-task.h"

#include <lib/syslog/global.h>
#include <stdint.h>
#include <zircon/types.h>

#include <memory>

#include <ddk/debug.h>
#include <fbl/alloc_checker.h>

namespace gdc {

zx_status_t GdcTask::PinConfigVmos(const gdc_config_info* config_vmo_list, size_t config_vmos_count,
                                   const zx::bti& bti) {
  fbl::AllocChecker ac;
  pinned_config_vmos_ =
      fbl ::Array<fzl::PinnedVmo>(new (&ac) fzl::PinnedVmo[config_vmos_count], config_vmos_count);
  if (!ac.check()) {
    return ZX_ERR_NO_MEMORY;
  }

  for (uint32_t i = 0; i < config_vmos_count; i++) {
    zx::vmo vmo(config_vmo_list[i].config_vmo);
    if (!vmo.is_valid()) {
      return ZX_ERR_INVALID_ARGS;
    }

    uint64_t size;
    auto status = vmo.get_size(&size);
    if (status != ZX_OK) {
      FX_LOG(ERROR, "%s: Unable to get VMO size\n", __func__);
      return status;
    }

    zx::vmo contig_vmo;
    status = zx::vmo::create_contiguous(bti, size, 0, &contig_vmo);
    if (status != ZX_OK) {
      FX_LOG(ERROR, "Unable to get create contiguous VMO\n", __func__);
      return status;
    }

    fzl::VmoMapper mapped_buffer_vmo;
    status = mapped_buffer_vmo.Map(vmo, 0, 0, ZX_VM_PERM_READ);
    if (status != ZX_OK) {
      FX_LOG(ERROR, "Unable to get map VMO\n", __func__);
      return status;
    }

    fzl::VmoMapper mapped_buffer_contig_vmo;
    status = mapped_buffer_contig_vmo.Map(contig_vmo, 0, 0, ZX_VM_PERM_READ | ZX_VM_PERM_WRITE);
    if (status != ZX_OK) {
      FX_LOG(ERROR, "Unable to get map contig VMO\n", __func__);
      return status;
    }

    memcpy(mapped_buffer_contig_vmo.start(), mapped_buffer_vmo.start(), size);

    status = pinned_config_vmos_[i].Pin(contig_vmo, bti, ZX_BTI_CONTIGUOUS | ZX_VM_PERM_READ);
    if (status != ZX_OK) {
      FX_LOG(ERROR, "%s: Failed to pin config VMO\n", __func__);
      return status;
    }
    if (pinned_config_vmos_[i].region_count() != 1) {
      FX_LOG(ERROR, "%s: buffer is not contiguous", __func__);
      return ZX_ERR_NO_MEMORY;
    }

    gdc_config_info config_info;
    config_info.config_vmo = std::move(contig_vmo.release());
    config_info.size = config_vmo_list[i].size;
    config_contig_vmos_.push_back(std::move(config_info));

    // Release the vmos so that the handle doesn't get closed
    __UNUSED zx_handle_t handle = vmo.release();
  }
  return ZX_OK;
}

zx_status_t GdcTask::Init(const buffer_collection_info_2_t* input_buffer_collection,
                          const buffer_collection_info_2_t* output_buffer_collection,
                          const image_format_2_t* input_image_format,
                          const image_format_2_t* output_image_format_table_list,
                          size_t output_image_format_table_count,
                          uint32_t output_image_format_index,
                          const gdc_config_info* config_vmo_list, size_t config_vmos_count,
                          const hw_accel_callback_t* callback, const zx::bti& bti) {
  if (callback == nullptr || config_vmo_list == nullptr || config_vmos_count == 0 ||
      config_vmos_count != output_image_format_table_count ||
      (output_image_format_table_count < 1) ||
      (output_image_format_index >= output_image_format_table_count)) {
    return ZX_ERR_INVALID_ARGS;
  }

  zx_status_t status = PinConfigVmos(config_vmo_list, config_vmos_count, bti);
  if (status != ZX_OK) {
    FX_LOG(ERROR, "%s: PinConfigVmo Failed\n", __func__);
    return status;
  }

  status = InitBuffers(input_buffer_collection, output_buffer_collection, input_image_format, 1, 0,
                       output_image_format_table_list, output_image_format_table_count,
                       output_image_format_index, bti, callback);
  if (status != ZX_OK) {
    FX_LOG(ERROR, "%s: InitBuffers Failed\n", __func__);
    return status;
  }

  return status;
}

}  // namespace gdc
