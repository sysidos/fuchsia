// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SRC_DEVELOPER_FEEDBACK_FEEDBACK_AGENT_ATTACHMENTS_PREVIOUS_SYSTEM_LOG_PTR_H_
#define SRC_DEVELOPER_FEEDBACK_FEEDBACK_AGENT_ATTACHMENTS_PREVIOUS_SYSTEM_LOG_PTR_H_

#include <fuchsia/mem/cpp/fidl.h>
#include <lib/fit/promise.h>

namespace feedback {

// Collects the system log from the previous boot.
fit::promise<fuchsia::mem::Buffer> CollectPreviousSystemLog();

}  // namespace feedback

#endif  // SRC_DEVELOPER_FEEDBACK_FEEDBACK_AGENT_ATTACHMENTS_PREVIOUS_SYSTEM_LOG_PTR_H_
