// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DEVTOOLS_DEVTOOLS_MANAGER_H_
#define CONTENT_BROWSER_DEVTOOLS_DEVTOOLS_MANAGER_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/singleton.h"
#include "content/common/content_export.h"
#include "content/public/browser/devtools_manager_delegate.h"

namespace content {

class DevToolsAgentHostImpl;

// This class is a singleton that manage global DevTools state for the whole
// browser.
// TODO(dgozman): remove this class entirely.
class CONTENT_EXPORT DevToolsManager {
 public:
  // Returns single instance of this class. The instance is destroyed on the
  // browser main loop exit so this method MUST NOT be called after that point.
  static DevToolsManager* GetInstance();

  DevToolsManager();
  virtual ~DevToolsManager();

  DevToolsManagerDelegate* delegate() const { return delegate_.get(); }

  void AgentHostStateChanged(DevToolsAgentHostImpl* agent_host, bool attached);

 private:
  friend struct base::DefaultSingletonTraits<DevToolsManager>;

  scoped_ptr<DevToolsManagerDelegate> delegate_;
  int attached_hosts_count_;

  DISALLOW_COPY_AND_ASSIGN(DevToolsManager);
};

}  // namespace content

#endif  // CONTENT_BROWSER_DEVTOOLS_DEVTOOLS_MANAGER_H_
