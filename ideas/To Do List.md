## To Do List

### 需求

### 使用描述

#### 1.show

1. 分成几个板块（当日，近期，长期，紧急）
2. 展示时间、事件
3. 颜色 可以加重点
#### 2.选择操作板块

* 确定你要对哪个板块的代办进行操作
#### 3.对代办进行操作

1. add
2. remove
3. finish
4. importance



#### debug体系

* error类



### 实现

1. 语法  information = key + sentence

   * 读入几个句子，砍掉最前面的空格以及最后面的空格

   * 搜索关键字，若合法则继续，不合法，则报错，提示重新输入

   * 若正确,则传入sentence，继续执行
2. File类
   * 构造函数，板块名字，写入类型
   * write
   * read
   * edit
3. 文件管理
   * 有三个主文件夹，
     1. 帮助手册
     2. to_do
       *  有 创建日期建在另外一个文件里
     4. finish 
       * 年、月、日
       * 每天都有一个txt文件 finish

### 指令
* a 增加list a + sentence
* r 移除list r + number
* f 完成list f + number
* h 帮助手册 h
* n 创建新版块 n
* s 设置操作对象 s + number
* q 关闭退出 q
* t 设置时间 t + number
* M 回到主界面  M
### improvement
* 可以在遍历时，构建一个函数对象

##旧
1.1展示所有Unit
​		·从to_do_list.txt中获取sentence
​		·用timeGet 从 sentence中获取time
​		·依次输出 序号 time sentence
2.语法
​	通过keyGet获取指令
​	通过myswitch跳转
​	2.1 add+sentence
​		·将sentence录入to_do_list
​		·counter++
​		·从sentence里get time
​	2.2remove
​		·获取n
​			·n通过字符串
​		·从to_do_list读取到temp除了n行
​		·再把temp里的东西copy到to_do_list
​	2.3

bug:
1.bug: r 1会出错
2.获得日期 很困难 数字不仅仅是一个字符

improvement
5.debug当to_do_list与imp的行数不同时，可以进行修改
6.clear清除所有
7.定义一个类，方便打开文件File 有string，fstream，copy，edit且还要包括app或是in的选择
8.每一天都建立一个finish，每一个月为文件夹，在每年的文件夹下面，以方便统计
9.工作区分割，可拖拽。
10.先设置是对哪个文件夹进行操作，再进行子操作
11.支持两套操作方式（命令行/ui）
12.可以固定在桌面上
13.一个目录记录，有多少个种类
14.简化语法，一个句子最多两个部分，前面为关键字，后面为附属，通过关键字确定任务类型，
通过switch（if else）再进行之后执行，之后可以再嵌套myswtich,或者用两层次的switch,这样
可以避免一个switch过于冗长
15.有默认项，每天都保持，但统计完成次数
1.myswitch可以用switch代替，只需要对key[0]的int型进行判断就可以了
2.快捷键展开
3.排名
4.日期提取
	timeGet()
	
5.insert
6.remove
7.分文件编写
8.多文件夹
9.统计完成情况
10.记录常见日期
11.显示今天日期
12.日历
13.help
14.指针动画，两种操作方式