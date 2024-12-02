# 剪辑

### 遮罩

需要占据一层

#### 字幕遮罩

* [【PR教程】如何制作VLOG中的文字遮罩效果？](https://www.bilibili.com/video/BV1r4411z7qH?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

#### 颜色遮罩

* [颜色遮罩](https://www.bilibili.com/video/BV1nP41197Rr?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

### 蒙版

蒙版为某视频的一种属性，本质上就是一个选区，即每一种效果的使用范围，为了避免效果生硬，可以加上蒙版羽化

* [PR蒙版转场](https://www.bilibili.com/video/BV1mu411M7Ap?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)
  * 蒙版羽化使过度更自然
  * 蒙版路径

#### 蒙版滑屏

> [蒙版滑屏｜剪辑教学](https://www.bilibili.com/video/BV1BG1gYyEpa?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

## 水平翻转

效果：水平

> https://baijiahao.baidu.com/s?id=1760888131837029502

## 色调

### 负片

效果：反转（通道）

### lumetri

效果->lumetri调色,同时打开窗口->lumetri调色，方便调色。

若要调成只有黑白灰的那种，则将饱和度调节为0，曝光也可以通过这个效果进行调节。

## 显示一部分（画中画）

效果->不透明度，然后在该效果的蒙版中用钢笔（或其他方式）选择出区域

## 消除

### 人物消失

* [【剪辑教程】包括使用ps污点消除!](https://www.bilibili.com/video/BV1cB22Y4EUg?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)
  * 使用PS污点消除工具（快捷键J）消除人物

> [人物消失卡点 | 不是pr消除要付费](https://www.bilibili.com/video/BV1WhC2YHEDh?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

### AE消除动态物体

好用的，但要注意渲染视频的时间不能长，1s差不多了。

> 【【AE教程】如何快速去除视频中的动态物体？99%的人都不知道！】https://www.bilibili.com/video/BV1fq421F7Vz?vd_source=ec4e4974e1b56ed330afdb6c6ead1501

### 消除字幕

如果为静态，直接用手机的AI消除或者PS的污点消除工具。

如果为动态，可以用中间值效果。

### 动态抠像

> [【AE教程】一键解决复杂抠像，ROTO笔刷到底多智能？明白这些效率倍增](https://www.bilibili.com/video/BV1dL4y1Y7vR?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)
>
> [【教程】如何进行动态抠像](https://www.bilibili.com/video/BV1RU4y1x7v8?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)
>
> * 项目地址
>
>   [sczhou/ProPainter:  ICCV 2023\] ProPainter: Improving Propagation and Transformer for Video Inpainting](https://github.com/sczhou/ProPainter)
>
>   [halfzm/ProPainter-Webui: A webui for propainter. Easily pick up objects from the video and eliminate them.](https://github.com/halfzm/ProPainter-Webui)
>
> [ProPainter视频移除技术，让后期人员解放双手， 完美移除视频水印及人物](https://www.bilibili.com/video/BV1ep4y1u7HE?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

## 小技巧

* 拖动视频时，双击 效果->位置（似乎叫这个名字），然后就可以在视窗里面拖动了，相比较与调节数值更加方便。
* 选择右侧所有视频片段
* 创建新的序列以使得电脑不卡

## 其他

### 项目降低版本

[Pr工程文件降级工具-在线Pr项目模板降级/高低版本转换网站](https://prmuban.com/jiangji.html)

### 格式转换

* FLAC到mp3

  [FLAC到MP3转换器- FreeConvert.com](https://www.freeconvert.com/zh/flac-to-mp3)

* mgg->ogg

  > [音乐解锁 - Unlock Music](https://tool.liumingye.cn/unlock-music/)

* ogg->mp3

  > [OGG到MP3转换器- FreeConvert.com](https://www.freeconvert.com/zh/ogg-to-mp3)

### 视频移除AI

* 


### 绿幕

* [【PR教程】PR绿幕抠图，教你一分钟搞定绿幕抠图换背景，超级简单的小白教学！](https://www.bilibili.com/video/BV1X8411R7tS?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

## 项目

### 双城之战

* 需要8个画面，每个画面2秒

  1. 正常 

  1. 消失 

  1. 正常 

  1. 反相（消失）

  1. 局部反相

  1. 消失


* 组成

  1. 爆爆 1

  2. 本索 1

  3. 希尔科 1 最后一幕可以进行别的修改 金克斯坐在桌子上

  4. 范德尔 1

  5. 两个伙伴 左右分屏 jinx听到的杂声

  6. 丽莎 

  7. 金克斯 镜子

  8. 艾克 1


* 白色边框
  * 通过绘制矩形实现


* 其他
  * 爆炸，时间倒流

## Trouble Shooting

### 导入mp4后，无声音

* 解决
  * 声音通道，需要点击两个A1，这样才能修改，当只选择一个A1时，视频的声音是没有效果的。
