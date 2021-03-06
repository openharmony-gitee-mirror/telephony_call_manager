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

#include "missed_call_notification.h"

#include "want.h"
#include "common_event.h"
#include "common_event_manager.h"
#include "common_event_support.h"

#include "telephony_log_wrapper.h"

namespace OHOS {
namespace Telephony {
MissedCallNotification::MissedCallNotification() : isIncomingCallMissed_(true), incomingCallNumber_("") {}

void MissedCallNotification::NewCallCreated(sptr<CallBase> &callObjectPtr)
{
    if (callObjectPtr == nullptr) {
        return;
    }
    if (callObjectPtr->GetTelCallState() == TelCallState::CALL_STATUS_INCOMING &&
        !callObjectPtr->GetAccountNumber().empty()) {
        incomingCallNumber_ = callObjectPtr->GetAccountNumber();
    } else {
        incomingCallNumber_ = "";
    }
    isIncomingCallMissed_ = true;
}

void MissedCallNotification::CallStateUpdated(
    sptr<CallBase> &callObjectPtr, TelCallState priorState, TelCallState nextState)
{
    if (callObjectPtr != nullptr && nextState == TelCallState::CALL_STATUS_DISCONNECTED &&
        callObjectPtr->GetAccountNumber() == incomingCallNumber_ && isIncomingCallMissed_) {
        PublishMissedCallEvent(callObjectPtr);
    }
}

void MissedCallNotification::PublishMissedCallEvent(sptr<CallBase> &callObjectPtr)
{
    AAFwk::Want want;
    want.SetParam("callId", callObjectPtr->GetCallID());
    want.SetParam("phoneNumber", callObjectPtr->GetAccountNumber());
#ifdef ABILITY_NOTIFICATION_SUPPORT
    want.SetAction(CommonEventSupport::COMMON_EVENT_INCOMING_CALL_MISSED);
#endif
#ifndef ABILITY_NOTIFICATION_SUPPORT
    want.SetAction(COMMON_EVENT_INCOMING_CALL_MISSED);
#endif
    EventFwk::CommonEventData data;
    data.SetWant(want);
    data.SetCode(INCOMING_CALL_MISSED_CODE);
    data.SetData(callObjectPtr->GetAccountNumber());
    EventFwk::CommonEventPublishInfo publishInfo;
    publishInfo.SetOrdered(true);
    bool result = EventFwk::CommonEventManager::PublishCommonEvent(data, publishInfo, nullptr);
    TELEPHONY_LOGD("publish missed call event result : %{public}d", result);
}

void MissedCallNotification::IncomingCallActivated(sptr<CallBase> &callObjectPtr)
{
    if (callObjectPtr != nullptr && callObjectPtr->GetAccountNumber() == incomingCallNumber_) {
        isIncomingCallMissed_ = false;
    }
}

void MissedCallNotification::IncomingCallHungUp(sptr<CallBase> &callObjectPtr, bool isSendSms, std::string content)
{
    if (callObjectPtr != nullptr && callObjectPtr->GetAccountNumber() == incomingCallNumber_) {
        isIncomingCallMissed_ = false;
    }
}

void MissedCallNotification::CallDestroyed(sptr<CallBase> &callObjectPtr) {}
} // namespace Telephony
} // namespace OHOS