# vendor_kaihong

## 介绍

该仓库托管深圳开鸿数字产业发展有限公司开发的产品样例代码，主要包括深开鸿【金星】系列智慧屏khdvk_3566b开发板的相关案例代码。

## 目录

```
vendor/kaihong
├── khdvk_3566b                                # khdvk_3566b开发板
└── ...
```

## 新建产品工程

这里以深开鸿【金星】系列智慧屏（khdvk_3566b）开发板为例，用户可以将 "khdvk_3566b"样例复制一份，然后进行裁剪或者修改，实现自己的产品工程，下面举例说明如何新建一个工程。

#### 新建产品工程

1、复制一份 vendor/kaihong目录下的"khdvk_3566b"放在同级目录下，并改名为自己产品工程的名称(例如：xxx_3566)；

2、进入 xxx_3566目录, 编辑config.json文件，修改product_name：

```
"product_name": "xxx_3566"
```

3、在config.json中可删除xts、kv_store、文件管理子系统，保留kernel、startup、hiviewdfx、distributedschedule等必要的子系统，可移除如下代码段：

```
{
      "subsystem": "utils",
      "components": [
        {
          "component": "utils_base",
          "features": []
        },
        {
          "component": "jsapi_sys",
          "features": []
        },
        {
          "component": "jsapi_api",
          "features": []
        },
        {
          "component": "jsapi_util",
          "features": []
        },
        {
          "component": "jsapi_worker",
          "features": []
        },
        {
          "component": "utils_memory",
          "features": []
        }
      ]
},
{
    "subsystem": "xts",
    "components": [
    {
      "component": "xts_acts",
      "features": []
    },
    {
      "component": "xts_hats",
      "features": []
    },
    {
      "component": "xts_dcts",
      "features": []
    }
    ]
}
```

4、同时board/kaihong目录新建xxx_3566目录，编辑 "xxx_3566/BUILD.gn"，group名：

```
group("xxx_3566") {
}
```

5、在OpenHarmony源码根目录下，执行./build.sh --product-name xxx_3566, out目录出现自己的产品名称 "xxx_3566"：



至此，一个简单的产品工程搭建完成，用户可按此方法，搭建自己产品工程。

详细的产品编译构建适配流程，请参考[编译构建适配流程](https://gitee.com/openharmony/docs/blob/master/zh-cn/device-dev/porting/porting-chip-prepare-process.md)

6、XTS编译方法

6.1、acts测试

进入到源码目录：test/xts/hats/

执行编译命令：

```
./build.sh suite=acts system_size=standard product_name=khdvk_3566b target_arch=arm64
```

输出目录：

out/khdvk_3566b/suites/acts/testcases/

6.2、hats测试

进入到源码目录：test/xts/hats/

执行编译命令：

```
./build.sh suite=hats system_size=standard product_name=khdvk_3566b target_arch=arm64
```

输出目录：

out/khdvk_3566b/suites/hats/testcases/

## 贡献

[如何参与](https://gitee.com/openharmony/docs/blob/HEAD/zh-cn/contribute/%E5%8F%82%E4%B8%8E%E8%B4%A1%E7%8C%AE.md)

[Commit message规范](https://gitee.com/openharmony/device_qemu/wikis/Commit%20message%E8%A7%84%E8%8C%83?sort_id=4042860)

## 相关仓

* [device/board/kaihong](https://gitee.com/openharmony-sig/device_board_kaihong)
* [device/soc/rockchip](https://gitee.com/openharmony-sig/device_soc_rockchip)
