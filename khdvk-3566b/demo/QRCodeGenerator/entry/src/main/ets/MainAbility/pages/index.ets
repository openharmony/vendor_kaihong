/*
 * Copyright (C) 2022 HiHope Open Source Organization .
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http:// www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 *
 * limitations under the License.
 */
@Entry
@Component
struct QRCodeExample {
  @State private content: string = 'OpenHarmony快速入门'
  private title: string = '二维码生成器'
  build() {
    Column({}) {
      Text(this.title).fontColor(Color.Orange).fontSize(50).fontWeight(FontWeight.Bold)
      TextInput({ placeholder: '请输入要生成的内容', }).fontSize(36).
      onChange((value) => {
        this.content = value;
      }).height(80).margin({left:20,right:20})
      QRCode(this.content)
        .color(Color.Orange)
        .width(200)
        .height(200)

        .border({
          width: 12, color: Color.Pink, style: BorderStyle.Dotted
        }).margin({bottom:60})
    }.width("100%").height("100%").justifyContent(FlexAlign.SpaceAround)
  }
}