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

import socket from '@ohos.net.socket'
import wifi from '@ohos.wifi';

function resolveIP(ip) {
  if (ip < 0 || ip > 0xFFFFFFFF) {
    throw ("The number is not normal!");
  }
  return (ip >>> 24) + "." + (ip >> 16 & 0xFF) + "." + (ip >> 8 & 0xFF) + "." + (ip & 0xFF);
}

let udp = socket.constructUDPSocketInstance()
let port = 3861

let localAddr = {
  address: resolveIP(wifi.getIpInfo().ipAddress),
  port: port
}

let mixerAddr = {
  //  address: '255.255.255.255', //局域网关播地址
  address: '192.168.255.78', //打蒜器地址
  port: port
}

udp.bind(localAddr, e => {
  if (e) {
    console.log('==bind error')
    return
  }
  console.log('==bind ok')
})

udp.on('listening', () => {
  console.log("==on listening success");
})

udp.on('message', data => { //收到指定端口来的消息
  console.log("==on message!")

  let dataView = new DataView(data.message)

  let str = ""
  for (let i = 0;i < dataView.byteLength; ++i) {
    let c = String.fromCharCode(dataView.getUint8(i))
    if (c !== "\n") {
      str += c
    }
  }
  console.log("==message:" + str + "From:" + data.remoteInfo.address)
  mixerAddr.address = data.remoteInfo.address //更新打蒜器的地址

  // 发送数据
  udp.send({ data: 'recv ok!\r\n',address: mixerAddr});
})


setTimeout(() => {
  // 发送数据
  udp.send({ data: 'hello!\r\n',address: mixerAddr});
}, 5 * 1000);



@Entry
@Component
struct Index {
  @State message: string = 'Hello World'

  build() {
    Row() {
      Column() {
        Text(this.message)
          .fontSize(50)
          .fontWeight(FontWeight.Bold)

        Button('send', { type: ButtonType.Normal, stateEffect: true })
          .onClick(() => {
            this.sendData()
          })
      }
      .width('100%')
    }
    .height('100%')
  }

  async sendData() {
    let order = 'hello\r\n'

    try {

      await udp.send({ data: order,address: mixerAddr})

      console.log(`==Send ${order} >:  + ${mixerAddr.address}`)

    } catch (e){
      console.log('==Error send: ' + e)
    }

  }
}