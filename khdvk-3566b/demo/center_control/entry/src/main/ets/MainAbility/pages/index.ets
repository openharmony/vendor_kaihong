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
struct Index {
  @State message: string = 'Hello World'

  build() {
    Row() {
      Column({ space: 15 }) {

        Row({ space: 15 }){
          Text("智能家居中控面板")
            .fontSize(40)
        }

        Row({ space: 15 }){
          Text("温度:")
            .fontSize(20)

          Text("30")
            .fontSize(20)

          Text("℃")
            .fontSize(20)
        }

        Row({ space: 15 }){
          Text("湿度:")
            .fontSize(20)

          Text("50")
            .fontSize(20)

          Text("%")
            .fontSize(20)
        }

        Row({ space: 35 }){
          Button('开灯', { type: ButtonType.Normal, stateEffect: true })
            .onClick(()=>{
              console.info('Button onClick  led on ')
            })
          Button('关灯', { type: ButtonType.Normal, stateEffect: true })
            .onClick(()=>{
              console.info('Button onClick  led off ')
            })
        }
      }
      .width('100%')
    }
    .height('100%')
  }
}