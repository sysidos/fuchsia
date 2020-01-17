// Copyright 2020 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Header file for using this crate from C. Note that this could be generated
// by cbindgen (https://github.com/eqrion/cbindgen), but it should still be
// checked in rather than generated by the build.

#ifndef EXAMPLES_RUST_CDYLIB_RUST_CRUST_H_
#define EXAMPLES_RUST_CDYLIB_RUST_CRUST_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Returns an integer from the Rust crate.
int32_t crust_get_int(void);

#ifdef __cplusplus
}
#endif

#endif  // EXAMPLES_RUST_CDYLIB_RUST_CRUST_H_