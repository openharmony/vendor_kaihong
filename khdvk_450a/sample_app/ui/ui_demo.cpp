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

#include <stdlib>
#include "common/screen.h"
#include "components/root_view.h"
#include "components/ui_canvas.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "graphic_config.h"
#include "hal_tick.h"
#include "hilog/log.h"
#include "ui_test.h"

#undef LOG_TAG
#define LOG_TAG "UiDemo"

using namespace OHOS;

class UiDemo : public UIView::OnClickListener {
public:
    static UiDemo *GetInstance()
    {
        static UiDemo instance;
        return &instance;
    }
    void Start();

private:
    UiDemo()
    {
        srand(HALTick::GetInstance().GetTime());
    }
    ~UiDemo()
    {
        if (btn_ != nullptr) {
            delete btn_;
            btn_ = nullptr;
        }
        if (label_ != nullptr) {
            delete label_;
            label_ = nullptr;
        }
    }

    int random(int min, int max)
    {
        return rand() % (max - min) + min;
    }

    bool OnClick(UIView &view, const ClickEvent &event) override
    {
        Point pos = event.GetCurrentPos();
        int16_t x = random(view.GetWidth(), Screen::GetInstance().GetWidth() - view.GetWidth());
        int16_t y = random(view.GetHeight(), Screen::GetInstance().GetHeight() - view.GetHeight());
        view.SetPosition(x, y);
        RootView::GetInstance()->Invalidate();
        HILOG_DEBUG(HILOG_MODULE_APP, "click at (%d,%d), move to (%d,%d)\n", pos.x, pos.y, x, y);
        return true;
    }

    RootView *rootView_ = nullptr;
    UILabelButton *btn_ = nullptr;
    UILabel *label_ = nullptr;
};

void UiDemo::Start()
{
    if (rootView_ != nullptr) {
        return;
    }
    rootView_ = RootView::GetInstance();
    rootView_->SetPosition(0, 0);
    rootView_->Resize(Screen::GetInstance().GetWidth(), Screen::GetInstance().GetHeight());
    HILOG_DEBUG(HILOG_MODULE_APP, "rootView %d-%d\n", rootView_->GetWidth(), rootView_->GetHeight());
    int16_t labelPositionx = 150;
    int16_t labelPositiony = 50;
    int16_t labelWidth = 150;
    int16_t labelHeight = 64;
    label_ = new UILabel();
    label_->SetPosition(labelPositionx, labelPositiony, labelWidth, labelHeight);
    label_->SetText("鸿蒙图形子系统");
    rootView_->Add(label_);

    int16_t btnPositionx = 150;
    int16_t btnPositiony = 200;
    int16_t btnWidth = 150;
    int16_t btnHeight = 64;
    btn_ = new UILabelButton();
    btn_->SetPosition(btnPositionx, btnPositiony, btnWidth, btnHeight);
    btn_->SetText("点不到我!");
    rootView_->Add(btn_);
    btn_->SetOnClickListener(this);

    rootView_->Invalidate();
}

void UiDemoStart(void)
{
    UiDemo::GetInstance()->Start();
}
