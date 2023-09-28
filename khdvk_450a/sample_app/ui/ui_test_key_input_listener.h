/*
 * Copyright (c) 2022 Shenzhen Kaihong Digital Industry Development Co., Ltd.
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

#ifndef UI_KEY_INPUT_H
#define UI_KEY_INPUT_H

#include <stdio.h>
#include <unistd.h>
#include "dock/input_device.h"
#include "key_input_gd32f450.h"

#define KEY_INPUT_NUM (3)

namespace OHOS {
typedef struct {
    uint16_t id;
    uint8_t status;
} key_info_t;

class UITestKeyInputListener : public RootView::OnKeyActListener {
public:
    explicit UITestKeyInputListener(UIImageView *ImageView, ImageInfo gifFrame)
        :ImageView_(ImageView), gifFrame_(gifFrame)
    {
    }

    virtual ~UITestKeyInputListener() {}
    bool OnKeyAct(UIView& view, const KeyEvent& event) override
    {
        if (ImageView_ == nullptr) {
            return true;
        }
        for (int i = 0; i < sizeof(keyinputmap_) / sizeof(key_info_t); i++) {
            if (keyinputmap_[i].id != event.GetKeyId() || keyinputmap_[i].status == event.GetState()) {
                continue;
            }
            keyinputmap_[i].status = event.GetState();
            switch (event.GetState()) {
                case InputDevice::STATE_PRESS:
                    if (keyinputmap_[i].id == KEY_WAKEUP) {
                        printf("KEY_WAKEUP\r\n");
                    } else if (keyinputmap_[i].id == KEY_TAMPER) {
                        printf("KEY_TAMPER\r\n");
                    }
                    break;
                case InputDevice::STATE_RELEASE:
                    break;
                default:
                    break;
            }
        }
        return true;
    }
private:
    key_info_t keyinputmap_[KEY_INPUT_NUM] = {
        {KEY_WAKEUP, 0},
        {KEY_TAMPER, 0},
        {KEY_USER, 0},
    };
    UIImageView *ImageView_;
    ImageInfo gifFrame_;
};
}
#endif