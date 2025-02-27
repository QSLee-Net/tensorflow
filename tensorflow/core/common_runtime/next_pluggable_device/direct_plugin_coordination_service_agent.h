/* Copyright 2022 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_CORE_COMMON_RUNTIME_NEXT_PLUGGABLE_DEVICE_DIRECT_PLUGIN_COORDINATION_SERVICE_AGENT_H_
#define TENSORFLOW_CORE_COMMON_RUNTIME_NEXT_PLUGGABLE_DEVICE_DIRECT_PLUGIN_COORDINATION_SERVICE_AGENT_H_

#include <string>
#include <string_view>

#include "absl/time/time.h"
#include "xla/tsl/distributed_runtime/coordination/coordination_service_agent.h"
#include "tensorflow/core/common_runtime/next_pluggable_device/plugin_coordination_service_agent.h"
#include "tensorflow/core/platform/status.h"
#include "tensorflow/core/platform/statusor.h"

namespace tensorflow {

class DirectPluginCoordinationServiceAgent
    : public PluginCoordinationServiceAgent {
 public:
  explicit DirectPluginCoordinationServiceAgent(void* agent)
      : agent_(reinterpret_cast<tsl::CoordinationServiceAgent*>(agent)) {}

  bool IsInitialized() const override {
    if (agent_ == nullptr) return false;
    return agent_->IsInitialized();
  }

  absl::Status InsertKeyValue(std::string_view key,
                              std::string_view value) override {
    return agent_->InsertKeyValue(key, value);
  }

  absl::StatusOr<std::string> GetKeyValue(std::string_view key) override {
    return agent_->GetKeyValue(key);
  }

  absl::StatusOr<std::string> GetKeyValue(std::string_view key,
                                          absl::Duration timeout) override {
    return agent_->GetKeyValue(key, timeout);
  }

  absl::StatusOr<std::string> TryGetKeyValue(std::string_view key) override {
    return agent_->TryGetKeyValue(key);
  }

  absl::Status DeleteKeyValue(std::string_view key) override {
    return agent_->DeleteKeyValue(key);
  }

 private:
  tsl::CoordinationServiceAgent* agent_;  // Not owned.
};

}  // namespace tensorflow

#endif  // TENSORFLOW_CORE_COMMON_RUNTIME_NEXT_PLUGGABLE_DEVICE_DIRECT_PLUGIN_COORDINATION_SERVICE_AGENT_H_
