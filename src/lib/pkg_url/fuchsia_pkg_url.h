// Copyright 2018 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SRC_LIB_PKG_URL_FUCHSIA_PKG_URL_H_
#define SRC_LIB_PKG_URL_FUCHSIA_PKG_URL_H_

#include <string>

#include "src/lib/fxl/macros.h"

namespace component {

class FuchsiaPkgUrl {
 public:
  FuchsiaPkgUrl() = default;
  FuchsiaPkgUrl(FuchsiaPkgUrl&) = default;
  FuchsiaPkgUrl& operator=(FuchsiaPkgUrl&) = default;
  FuchsiaPkgUrl(FuchsiaPkgUrl&&) = default;
  FuchsiaPkgUrl& operator=(FuchsiaPkgUrl&&) = default;

  static bool IsFuchsiaPkgScheme(const std::string& url);

  // Returns the default component's .cmx path of this package, i.e.
  // meta/<package_name>.cmx
  std::string GetDefaultComponentCmxPath() const;

  bool Parse(const std::string& url);

  // Serializes this url without a variant or hash included
  std::string WithoutVariantAndHash() const;

  const std::string& host_name() const { return host_name_; }
  const std::string& package_name() const { return package_name_; }
  const std::string& variant() const { return variant_; }
  const std::string& hash() const { return hash_; }
  const std::string& resource_path() const { return resource_path_; }
  std::string package_path() const;
  std::string pkgfs_dir_path() const;

  const std::string& ToString() const;

 private:
  std::string url_;
  std::string host_name_;
  std::string package_name_;
  std::string variant_;
  std::string hash_;
  std::string resource_path_;
};

}  // namespace component

#endif  // SRC_LIB_PKG_URL_FUCHSIA_PKG_URL_H_
