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

#ifndef NET_CALL_BASE_H
#define NET_CALL_BASE_H
#include <cstdio>
#include <cstdlib>

namespace OHOS {
namespace TelephonyCallManager {
class NetCallBase {
public:
    NetCallBase();
    virtual ~NetCallBase() = default;

    int StartConference();
    int InviteToConference();
    int KickOutConference();
    int LeaveConference();

    int GetNetCallType();
    int ChangeNetCallType();
};
} // namespace TelephonyCallManager
} // namespace OHOS

#endif // NET_CALL_BASE_H