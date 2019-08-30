// Copyright 2018 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <lib/fit/result.h>
#include <lib/inspect/cpp/inspect.h>
#include <lib/inspect/cpp/vmo/heap.h>

#include <atomic>
#include <memory>
#include <sstream>

using inspect::internal::Heap;
using inspect::internal::State;

namespace inspect {

namespace {
const InspectSettings kDefaultInspectSettings = {.maximum_size = 256 * 1024};
}  // namespace

Inspector::Inspector(const std::string& name) : Inspector(name, kDefaultInspectSettings) {}

Inspector::Inspector(const std::string& name, const InspectSettings& settings)
    : root_(std::make_unique<Node>()) {
  if (settings.maximum_size == 0) {
    return;
  }

  state_ = State::CreateWithSize(settings.maximum_size);
  if (!state_) {
    return;
  }

  *root_ = state_->CreateNode(name, 0 /* parent */);
}

Inspector::Inspector(const std::string& name, zx::vmo vmo) : root_(std::make_unique<Node>()) {
  size_t size;

  zx_status_t status;
  if (ZX_OK != (status = vmo.get_size(&size))) {
    return;
  }

  if (size == 0) {
    // VMO cannot be zero size.
    return;
  }

  // Decommit all pages, reducing memory usage of the VMO and zeroing it.
  if (ZX_OK != (status = vmo.op_range(ZX_VMO_OP_DECOMMIT, 0, size, nullptr, 0))) {
    return;
  }

  state_ = State::Create(std::make_unique<Heap>(std::move(vmo)));
  if (!state_) {
    return;
  }

  *root_ = state_->CreateNode(name, 0 /* parent */);
}

fit::result<const zx::vmo*> Inspector::GetVmo() const {
  if (!state_) {
    return fit::error();
  }

  return fit::ok(&state_->GetVmo());
}

Node& Inspector::GetRoot() const { return *root_; }

std::string UniqueName(const std::string& prefix) {
  static std::atomic_uint_fast64_t next_id;
  std::ostringstream out;
  auto value = next_id.fetch_add(1);
  out << prefix << "0x" << std::hex << value;
  return out.str();
}

}  // namespace inspect
