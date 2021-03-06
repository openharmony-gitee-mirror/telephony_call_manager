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

#ifndef AUDIO_STATE_H
#define AUDIO_STATE_H

#include <cstdint>
#include <string>
#include <memory>
#include <mutex>

namespace OHOS {
namespace Telephony {
class AudioState {
public:
    AudioState() {}
    virtual ~AudioState() {}
    // handle audio events in current state
    virtual bool ProcessEvent(int32_t event) = 0;
};
} // namespace Telephony
} // namespace OHOS
#endif // AUDIO_STATE_H