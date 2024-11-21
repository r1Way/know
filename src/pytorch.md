# Pytorch

CUDA Version: 12.7 

Driver Version: 566.14  

torch Version: 1.13.1

conda.exe地址： F:\Users\anaconda3\envs\pytorch\Scripts

## 环境配置

> [PyTorch深度学习快速入门教程（绝对通俗易懂！）](https://www.bilibili.com/video/BV1hE411t7RN?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

### 查看cuda版本

```shell
nvidia-smi
```

### 进入环境

```shell
conda activate pytorch
```

### 查看库

```shell
pip list
```

### 查看虚拟环境地址

``` shell
conda env list
```

### 查看torch版本

```shell
import torch
print(torch.__version__)
print(torch.version.cuda)
```

### 检查配置是否成功

```shell
torch.cuda.is_available()
```

### pycharm选择已有环境

setting->项目->python解释器->添加已有解释器->conda环境->使用先有环境->pytorch->应用

## 手写数字识别

### CNN.py

构建自定义类

```python
import torch


class CNN(torch.nn.Module):  # 继承
    def __init__(self):
        super(CNN, self).__init__()
        self.conv = torch.nn.Sequential(
            # 1.卷积(卷积层)
            torch.nn.Conv2d(1, 32, kernel_size=5,  # 卷积核有32个
                            padding=2),  # h2=(28-5+2*2)/1+1=28
            # 2.归一化(BN层)
            torch.nn.BatchNorm2d(32),
            # 3.激活层 Relu函数
            torch.nn.ReLU(),
            # 4.最大池化
            torch.nn.MaxPool2d(2)  # 池化核的大小 14*14
        );
        self.fc = torch.nn.Linear(in_features=14 * 14 * 32, out_features=10);

    def forward(self, x):
        out = self.conv(x)
        # 将图像展开成一维
        # 输入的张量(n,c,h,w) n为数 c为通道数 c
        out = out.view(out.size()[0], -1)
        out = self.fc(out)
        return out

```



### main.py

用于训练模型

```python
import torch
import torchvision.datasets as dataset
import torchvision.transforms as transforms
import torch.utils.data as data_utils
from CNN import CNN

##### 数据加载

train_data = dataset.MNIST(
    root="mnist",
    train=True,
    transform=transforms.ToTensor(),
    download=True
);

test_data = dataset.MNIST(
    root="mnist",
    train=False,
    transform=transforms.ToTensor(),
    download=True
);

# print(train_data)
# print(test_data)


###分批加载
train_loader = data_utils.DataLoader(dataset=train_data,
                                     batch_size=64,
                                     shuffle=True)  # 打乱下标

test_loader = data_utils.DataLoader(dataset=test_data,
                                    batch_size=64,
                                    shuffle=True)  # 打乱下标

# print(train_loader)
# print(test_loader)
cnn = CNN();

#######损失函数
loss_func = torch.nn.CrossEntropyLoss();

######优化函数
optimizer = torch.optim.Adam(cnn.parameters(), lr=0.01)

####训练过程
# epoch 通常指 一次训练数据全部训练一次
for epoch in range(10):
    for index, (images, labels) in enumerate(train_loader):
        # print(index)
        # print(images)
        # print(labels)

        # 前向传播
        outputs = cnn(images)
        loss = loss_func(outputs, labels);
        # 先清空梯度
        optimizer.zero_grad()
        # 反向传播
        loss.backward()
        optimizer.step()
        print("now round{}, it is {}/{},loss is {}".format(epoch + 1, index + 1, len(train_data) // 64, loss.item()))
        # break
    ###########测试集验证
    loss_test = 0
    rightValue = 0
    for index2, (images, labels) in enumerate(test_loader):
        outputs = cnn(images)
        # print(outputs)
        # print(labels)
        loss_test += loss_func(outputs, labels)
        _, pred = outputs.max(1)
        rightValue += (pred == labels).sum().item()
        # print(pred)
        # 把两个张量中的每一个元素进行对比
        # print((pred == labels).sum().item())
        # break;
        print("当前为第{}轮测试集验证, 当前批次为{}/{},loss为{},准确率是{}".format(epoch + 1, index2 + 1,
                                                                                   len(test_data) // 64, loss_test,
                                                                                   rightValue / len(test_data)))

# torch.save(cnn, "model/mnist_model.pkl")

```

### mnist_test.py

使用模型

```python
import cv2
import torch
import torchvision.datasets as dataset
import torchvision.transforms as transforms
import torch.utils.data as data_utils
from CNN import CNN

test_data = dataset.MNIST(
    root="mnist",
    train=False,
    transform=transforms.ToTensor(),
    download=True
);

test_loader = data_utils.DataLoader(dataset=test_data,
                                    batch_size=64,
                                    shuffle=True)  # 打乱下标

cnn = torch.load("model/mnist_model.pkl")
loss_func = torch.nn.CrossEntropyLoss();
loss_test = 0
rightValue = 0
for index, (images, labels) in enumerate(test_loader):
    outputs = cnn(images)
    _, pred = outputs.max(1)
    loss_test += loss_func(outputs, labels)
    rightValue += (pred == labels).sum().item()

    images = images.numpy()  # batch , c ,h ,w
    labels = labels.numpy()
    pred = pred.numpy()

    for idx in range(images.shape[0]):
        im_data = images[idx]
        im_data = im_data.transpose(1, 2, 0)  # 交换维度，将通道维度移到最后
        im_label = labels[idx]
        im_pred = pred[idx]
        print("预测值为{} 真实值为{}".format(im_pred, im_label))
        cv2.imshow("nowImage", im_data)
        cv2.waitKey(0)  # 弹出窗口时程序停止运行
print("loss为{},准确率是{}".format(loss_test, rightValue / len(test_data)))
print(cv2.__version__)

```

> [实战教学！pytorch实现手写数字识别！](https://www.bilibili.com/video/BV1Vm42137D1?p=2&vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

## Trouble Shooting

### pycharm配置anaconda环境时找不到python.exe解决办法

> https://blog.csdn.net/ytusdc/article/details/137782055?fromshare=blogdetail&sharetype=blogdetail&sharerId=137782055&sharerefer=PC&sharesource=r1Way&sharefrom=from_link

### torch为cpu && print(torch.version.cuda)结果为 none

地址torch库地址 F:\Users\anaconda3\pkgs

```shell
print(torch.version.cuda)
```

> [记录一下安装Pytorch和cuda的踩坑经历 - 知乎](https://zhuanlan.zhihu.com/p/424837529)

### pycharm import cv2出错

* 估计是权限的问题

用管理员打开anaconda prompt

切换至你的虚拟环境

输入

``` shell
pip install opencv-python
```

> [在Anaconda中安装opencv库](https://www.bilibili.com/video/BV15t4y1Y7LC?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

### Traceback (most recent call last):

* 报错

```shell
Traceback (most recent call last):
  File "G:\research\number_recognition\main.py", line 2, in <module>
    import torchvision.datasets as dataset
  File "F:\Users\anaconda3\envs\pytorch\lib\site-packages\torchvision\__init__.py", line 5, in <module>
    from torchvision import datasets, io, models, ops, transforms, utils
  File "F:\Users\anaconda3\envs\pytorch\lib\site-packages\torchvision\datasets\__init__.py", line 1, in <module>
    from ._optical_flow import FlyingChairs, FlyingThings3D, HD1K, KittiFlow, Sintel
  File "F:\Users\anaconda3\envs\pytorch\lib\site-packages\torchvision\datasets\_optical_flow.py", line 9, in <module>
    from PIL import Image
  File "F:\Users\anaconda3\envs\pytorch\lib\site-packages\PIL\Image.py", line 103, in <module>
    from . import _imaging as core
ImportError: DLL load failed: 找不到指定的模块。
```

* 解决

```shell
pip uninstall pillow
pip install pillow
```

## 其他

### GNN

> [CS224W | Home](https://web.stanford.edu/class/cs224w/index.html#content)
>
> [图神经网络 | BrainGNN: 用于功能磁共振成像分析的可解释性脑图神经网络](https://roses.blog.csdn.net/article/details/113533359?fromshare=blogdetail&sharetype=blogdetail&sharerId=113533359&sharerefer=PC&sharesource=r1Way&sharefrom=from_link)

### GCN

> [入门](https://www.bilibili.com/video/BV1yP4y1976Z?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

### FMRi

> [静息态fMRI功能性连接: 15分钟知识速览](https://www.bilibili.com/video/BV1dwvse3EAM?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)
