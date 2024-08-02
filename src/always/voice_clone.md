## AI声音克隆

### 来源

> [你的声音，现在是我的了！- 手把手教你用 GPT-SoVITS 克隆声音！](https://www.bilibili.com/video/BV1P541117yn?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)
>
> [RVC-Boss/GPT-SoVITS: 1 min voice data can also be used to train a good TTS model! (few shot voice cloning) (github.com)](https://github.com/RVC-Boss/GPT-SoVITS?tab=readme-ov-file)

### 流程

1. 下载

2. 人声伴奏分离

3. 语音切割

   将1~2 mins的语言分割成多个单句。

4. 打标

   让文字，标点与语音对应。

5. 训练

6. 微调

7. 推理

### 关键路径

* 人声伴奏分离

`H:\voice_clone\GPT-SoVITS-beta\GPT-SoVITS-beta0706\output\uvr5_opt`

* 语音切割

`H:\voice_clone\GPT-SoVITS-beta\GPT-SoVITS-beta0706\output\slicer_opt`

* 打标

`H:\voice_clone\GPT-SoVITS-beta\GPT-SoVITS-beta0706\output\asr_opt`

* 训练后的模型

`H:\voice_clone\GPT-SoVITS-beta\GPT-SoVITS-beta0706\SoVITS_weights`

`H:\voice_clone\GPT-SoVITS-beta\GPT-SoVITS-beta0706\GPT_weights`

> 上面仅做参考，记得替换盘符。

### 说明

优点：部署简单，效果不错。

缺点：8个g，步骤有点多，占显存，推理字数多了，会有漏字的情况。
