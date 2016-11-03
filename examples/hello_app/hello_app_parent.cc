// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>

#include <memory>
#include <string>

#include "apps/modular/examples/hello_app/hello.fidl.h"
#include "apps/modular/lib/app/connect.h"
#include "apps/modular/lib/app/application_context.h"
#include "lib/ftl/macros.h"
#include "lib/mtl/tasks/message_loop.h"

using examples::HelloPtr;

namespace {

class HelloAppParent {
 public:
  HelloAppParent()
      : context_(modular::ApplicationContext::CreateFromStartupInfo()) {
    context_->launcher()->CreateApplication("file:///boot/apps/hello_app_child",
                                            fidl::GetProxy(&child_services_),
                                            fidl::GetProxy(&child_));

    modular::ConnectToService(child_services_.get(), fidl::GetProxy(&hello_));

    DoIt("hello");
    DoIt("goodbye");
  }

 private:
  void DoIt(const std::string& request) {
    hello_->Say(request, [request](const fidl::String& response) {
      printf("%s --> %s\n", request.c_str(), response.get().c_str());
    });
  }

  std::unique_ptr<modular::ApplicationContext> context_;

  modular::ApplicationControllerPtr child_;
  modular::ServiceProviderPtr child_services_;
  HelloPtr hello_;

  FTL_DISALLOW_COPY_AND_ASSIGN(HelloAppParent);
};

}  // namespace

int main(int argc, const char** argv) {
  mtl::MessageLoop loop;
  HelloAppParent app;
  loop.Run();
  return 0;
}
