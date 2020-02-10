// Copyright 2019 The Fuchsia Authors. All rights reserved.
// Use of this source is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/developer/feedback/utils/rotating_file_set.h"

#include <assert.h>

namespace feedback {

RotatingFileSet::RotatingFileSet(const std::vector<const std::string>& file_paths,
                                 const FileSize set_size)
    : file_paths_(file_paths), individual_file_size_(set_size / file_paths.size()) {
  assert(file_paths_.size() > 0 && "|file_paths_| must have non-zero size");

  for (size_t i = 0; i < file_paths_.size(); ++i) {
    files_.emplace_back(individual_file_size_);
  }

  current_file_ = &files_.front();

  // This will truncate the file.
  current_file_->Open(file_paths_.front());
}

void RotatingFileSet::Write(const std::string& line) {
  if (individual_file_size_.to_bytes() < line.size()) {
    return;
  }

  if (current_file_->BytesRemaining() < line.size()) {
    PositionNewFile();
    RotateFilePaths();

    // This re-creates the first file in the list.
    current_file_->Open(file_paths_.front());
  }
  current_file_->Write(line);
}

void RotatingFileSet::PositionNewFile() {
  files_.pop_back();
  files_.emplace_front(individual_file_size_);
  current_file_ = &files_.front();
}

void RotatingFileSet::RotateFilePaths() {
  // Assuming we have 4 files file0.txt, file1.txt, file2.txt, and file3.txt, in that order, their
  // names will change as follows:
  // files2.txt -> file3.txt, file1.txt -> file2.txt, file0.txt -> file1.txt.
  // The contents of file3.txt no longer exist.
  for (size_t i = file_paths_.size() - 1; i > 0; --i) {
    rename(file_paths_[i - 1].c_str(), file_paths_[i].c_str());
  }
}

}  // namespace feedback
