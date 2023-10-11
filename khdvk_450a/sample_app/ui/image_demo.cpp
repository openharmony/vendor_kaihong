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
#include "cmsis_os.h"
#include "common/screen.h"
#include "components/root_view.h"
#include "components/ui_label.h"
#include "components/ui_label_button.h"
#include "components/ui_scroll_view.h"
#include "components/ui_image_view.h"
#include "components/ui_view.h"
#include "ui_test.h"
#include "logo_interface.h"
#ifdef LOSCFG_DRIVERS_USER_KEY_INPUT
#include "ui_key_input.h"
#endif

static const int32_t IMG_HORIZONTAL_RESOLUTION = 240;
static const int32_t IMG_VERTICAL_RESOLUTION = 320;
static const int32_t IMG_ARGB_BYTES_PER_PIXEL = 4;
static const int32_t GIF_DELAY_TIME_US = 300000;
static const int32_t IMG_START_X = 40;
static const int32_t IMG_START_Y = 80;

using namespace OHOS;
class ImageDemo : public UIView::OnClickListener {
public:
    static ImageDemo *GetInstance()
    {
        static ImageDemo inst;
        return &inst;
    }
    void SetUp();
    UIView *GetView();
    void GifPlayLoop();

private:
    ImageDemo() {}
    ~ImageDemo();
    void CreateImageSwitch();
    void GifPlayThread();

#ifdef LOSCFG_DRIVERS_USER_KEY_INPUT
    UITestKeyInputListener* keyListener_ = nullptr;
#endif
    UIScrollView *container_ = nullptr;
    UIImageView *gifImageView_ = nullptr;
    UILabelButton *gifToGif_ = nullptr;
    UILabelButton *gifToJpeg_ = nullptr;
    UILabelButton *gifToPng_ = nullptr;
    uint8_t* gifImageData_ = nullptr;
    int16_t g_height = 0;
    ImageInfo gifFrame_;
};

static void DeleteChildren(UIView *view)
{
    if (view == nullptr) {
        return;
    }
    while (view != nullptr) {
        UIView *tempView = view;
        view = view->GetNextSibling();
        if (tempView->IsViewGroup() && (tempView->GetViewType() != UI_DIGITAL_CLOCK)) {
            DeleteChildren(static_cast<UIViewGroup *>(tempView)->GetChildrenHead());
        }
        if (tempView->GetParent()) {
            static_cast<UIViewGroup *>(tempView->GetParent())->Remove(tempView);
        }
        delete tempView;
    }
}

void ImageDemo::SetUp()
{
    g_height = 0;
    if (container_ == nullptr) {
        container_ = new UIScrollView();
        container_->SetPosition(0, 0, Screen::GetInstance().GetWidth() - 1, Screen::GetInstance().GetHeight() - 1);
        container_->SetHorizontalScrollState(false);
    }
}

ImageDemo::~ImageDemo()
{
    DeleteChildren(container_);
#ifdef LOSCFG_DRIVERS_USER_KEY_INPUT
    keyListener_ = nullptr;
#endif
    container_ = nullptr;
    gifImageView_ = nullptr;
    gifToGif_ = nullptr;
    gifToJpeg_ = nullptr;
    gifToPng_ = nullptr;
}

UIView *ImageDemo::GetView()
{
    CreateImageSwitch();
    return container_;
}

void ImageDemo::GifPlayLoop()
{
    int cnt = GetGifImgCnt();
    while (1) {
        for (int i = 0; i < cnt; i++) {
            gifImageData_ = GetGifData(i);
            gifFrame_.data = gifImageData_;
            gifImageView_->SetSrc(&gifFrame_);
            usleep(GIF_DELAY_TIME_US);
        }
    }
}

static void GifPlayThread()
{
    ImageDemo *view = ImageDemo::GetInstance();
    view->GifPlayLoop();
}

void ImageDemo::CreateImageSwitch()
{
    if (container_ == nullptr) {
        return;
    }

    gifImageView_ = new UIImageView();
    gifImageView_->SetPosition(IMG_START_X, IMG_START_Y);
    gifImageView_->SetWidth(IMG_HORIZONTAL_RESOLUTION);
    gifImageView_->SetHeight(IMG_VERTICAL_RESOLUTION);
    gifImageView_->SetStyle(STYLE_IMAGE_OPA, OPA_OPAQUE);
    gifFrame_.header.width = IMG_HORIZONTAL_RESOLUTION;
    gifFrame_.header.height = IMG_VERTICAL_RESOLUTION;
    gifFrame_.header.colorMode = ARGB8888;
    gifFrame_.dataSize = IMG_HORIZONTAL_RESOLUTION * IMG_VERTICAL_RESOLUTION * IMG_ARGB_BYTES_PER_PIXEL;
    container_->Add(gifImageView_);
#ifdef LOSCFG_DRIVERS_USER_KEY_INPUT
    if (keyListener_ == nullptr) {
        keyListener_ = new UITestKeyInputListener(gifImageView_, gifFrame_);
    }
    RootView::GetInstance()->SetOnKeyActListener(keyListener_);
    HILOG_DEBUG(HILOG_MODULE_ACE, "CreateImageSwitch mark\r\n");
#endif
}

void ImageDemoStart(void)
{
    RootView *rootView_ = RootView::GetInstance();
    rootView_->SetPosition(0, 0, Screen::GetInstance().GetWidth(), Screen::GetInstance().GetHeight());
    ImageDemo *view = ImageDemo::GetInstance();
    view->SetUp();
    rootView_->Add(view->GetView());
    rootView_->Invalidate();

    osThreadAttr_t attr;
    attr.name = "display-gif";
    attr.attr_bits = 0U;
    attr.cb_mem = NULL;
    attr.cb_size = 0U;
    attr.stack_mem = NULL;
    const int32_t UI_THREAD_STACK_SIZE = 1024 * 64;
    attr.stack_size = UI_THREAD_STACK_SIZE;
    attr.priority = osPriorityNormal;

    if (osThreadNew((osThreadFunc_t)GifPlayThread, NULL, &attr) == NULL) {
        GRAPHIC_LOGE("Failed to create UiMainTask");
    }
}