/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AUDIO_EVENT_H
#define AUDIO_EVENT_H
#include <cstdint>

#include "audio_device_manager.h"
#include "call_state_manager.h"

namespace OHOS {
namespace TelephonyCallManager {
/**
 * @class AudioEvent
 * audio event manager , handle call state events and audio device events.
 */
class AudioEvent {
public:
    AudioEvent();
    virtual ~AudioEvent();
    void Init();
    void HandleEvent(int32_t event);
    void HandleCallStateEvent(int32_t event);
    void HandleAudioDeviceEvent(int32_t event);

private:
    std::unique_ptr<CallStateManager> callStateManager_;
    std::unique_ptr<AudioDeviceManager> audioDeviceManager_;
};
} // namespace TelephonyCallManager
} // namespace OHOS
#endif // AUDIO_EVENT_MANAGER_H