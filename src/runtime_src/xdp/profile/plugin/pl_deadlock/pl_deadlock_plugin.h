/**
 * Copyright (C) 2016-2021 Xilinx, Inc
 * Copyright (C) 2023 Advanced Micro Devices, Inc. - All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may
 * not use this file except in compliance with the License. A copy of the
 * License is located at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#ifndef PL_DEADLOCK_PLUGIN_DOT_H
#define PL_DEADLOCK_PLUGIN_DOT_H

#include <vector>
#include <atomic>

#include "xdp/profile/plugin/device_offload/device_offload_plugin.h"

namespace xdp {

  class PLDeadlockPlugin : public XDPPlugin
  {
  private:
    virtual void pollDeadlock(void* handle, uint64_t index);
    void forceWrite();
  
  private:
    uint32_t mPollingIntervalMs = 100;
    std::map<void*, std::thread> mThreadMap;
    std::map<void*,std::atomic<bool>> mThreadCtrlMap;
    bool fileExists;
    std::mutex writeLock;

  public:
    PLDeadlockPlugin();
    ~PLDeadlockPlugin();

    virtual void updateDevice(void* handle);
    virtual void flushDevice(void* handle);

    // Virtual functions from XDPPlugin
    virtual void writeAll(bool openNewFiles);
  };

} // end namespace xdp

#endif
