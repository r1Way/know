# Makefile

> [如何编译 C++ 程序：轻松搞定 Makefile](https://www.bilibili.com/video/BV1dF41117NV?p=2&vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

# 编译一个简单的程序

## gcc

### 编译

源文件(.cpp)编译生成目标文件(.o)

```shell
gcc -c main.c -o main.o
```

### 链接

目标文件(.o)链接生成可执行文件

``` shell
gcc main.o -o main
```

### 单命令

不生成 .o文件

```shell
gcc main.cpp -o main -lstdc++
```

### 运行

```shell
./main
```

### 链接错误

```shell
test.o:test.cpp:(.text+0x17): undefined reference to `std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)'
test.o:test.cpp:(.text+0x4f): undefined reference to `std::ios_base::Init::~Init()'
test.o:test.cpp:(.text+0x7f): undefined reference to `std::ios_base::Init::Init()'
test.o:test.cpp:(.rdata$.refptr._ZSt4cout[.refptr._ZSt4cout]+0x0): undefined reference to `std::cout'
collect2.exe: error: ld returned 1 exit status
```



* 解决方法

链接某个库

```shell
gcc main.o -o main -lstdc++
```

# 

## g++

### 编译

``` shell
g++ -c main.cpp -o main.o
```

### 链接

```shell
g++ main.o -o main
```

### 单命令

```shell
g++ main.cpp -o main
```

> 区别：g++相较gcc会默认链接标准库

# C++编译流程

1. 预处理

   把#include语句以及一些宏插入程序文本中，得到*.i文件

   ```shell
   g++ -E main.cpp -o main.i
   ```

2. 编译

   将*.i 编译成 *.s的汇编语言程序

   ```shell
   g++ -S main.i -o main.s
   ```

3. 汇编

   将* .s翻译成机器语言的二进制指令，并打包成一种可重定位目标程序的格式，并将结果保存在*.o文件中

   ```she
   g++ -c main.s -o main.o

4. 链接

   合并全部 *.o文件，得到可执行文件。

   ```shell
   g++ main.o -o main
   ```

### 预处理、编译、汇编三合一

```shell
g++ -c main.cpp -o main.o
```

> 生成 .o文件时才加-c

### 预处理、编译、汇编、链接四合一

```shell
g++ main.cpp -o main
```

# 编译和链接错误

## 编译错误

为包含头文件

### 源代码

main.cpp

```c++
#include<iostream>

int main()
{
    std::cout<<"result: "<<add(3,5)<<std::end;
    return 0;
}
```

add.cpp

```c++
int add(int a,int b)
{
    return a+b;
}
```

### 运行

```shell
g++ -c add.cpp -o add.o
g++ -c main.cpp -o main.o
g++ main.o add.o -o main
```

或

```shell
g++ main.cpp add.cpp -o main
```



### 报错

```shell
main.cpp: In function 'int main()':
main.cpp:5:28: error: 'add' was not declared in this scope
     std::cout<<"result: "<<add(3,5)<<std::end;
                            ^~~
main.cpp:5:28: note: suggested alternative: 'rand'
     std::cout<<"result: "<<add(3,5)<<std::end;
                            ^~~
                            rand
```

### 解决

* 写头文件add.h

```c++
#pragma once
int add(int a,int b);
```

* 包含头文件

```c++
#include<iostream>
#include"add.h"
int main()
{
    std::cout<<"result: "<<add(3,5)<<std::endl;
    return 0;
}
```

## 链接错误

未提供实现

### 源代码

add.cpp为空

```c++
// int add(int a,int b)
// {
//     return a+b;
// }
```

### 报错

```shel
main.o:main.cpp:(.text+0x34): undefined reference to `add(int, int)'
collect2.exe: error: ld returned 1 exit status
```

### 解决

在add.cpp中提供实现（记得保存），重新编译。

# 源文件要包含头文件

* 会检查函数定义与函数实现是否一致

# 头文件搜索路径

* `#include "head.h"`按照相对工程的路径去找头文件

* `#include <head.h>`按照头文件搜素路径去找头文件
  * 将当前路径`.`添加到头文件搜索路径

```shell
  g++ -I. add.cpp main.cpp -o main
```

`-I dir `将dir添加到文件查找路径

# 多文件编译 

* 法一

  每个源文件生成.o文件，再链接

* 法二

  ```shell
  g++ -I. add.cpp sub.cpp main.cpp -o main
  ```

  

# Makefile基本功能

## 法一

```makefile
target:
	g++ -I. add.cpp main.cpp -o main
```

* target:目标名称，可以随便命名

* g++ 前面不是空格，必须是 tab 缩进

* Makefile 里如果有多个目标，可以通过 make加目标名称来执行指定的目标，如果不指定目标，则默认选择第一个目标执行

  ```shell
  make target
  ```

## 法二

```makefile
target:main

main:
	g++ -I. add.cpp main.cpp -o main
```

`tatget main`表示 target 目标依赖 main 目标

* 未指定目标

```shell
  make
```

  默认调用第一个目标(target)的第一个目标(main)

* 指定目标

```shell
make main
```

## 法三

```makefile
target: add_o main_o main

main:
	g++ add.o main.o -o main

add_o:
	g++ -I. -c add.cpp -o add.o

main_o:
	g++ -I. -c main.cpp -o main.o 
```

* target的各个目标有顺序，先进行add_o再进行main_o，最后进行main

# Makefile升级用法

## 模式规则

```makefile
target: add.o main.o main

main:
	g++ add.o main.o -o main

%.o: %.cpp
	g++ -I. -c $< -o $@
```

* 说明

  * `%.o:%.cpp` 所有的.o文件都由相同名称的 .cpp文件编译生成
  * `<`表示第一个依赖值
  * `^`表示所有依赖的挨个值
  * `@`表示所有目标的挨个值

  >  “<” ，“@” 被称为自动化变量

## 变量替换

```makefile
OBJS = main.o add.o

target: $(OBJS) main

main:
	g++ $(OBJS) -o main

%.o: %.cpp
	g++ -I. -c $< -o $@
```

说明

* 引用变量时，加上小括号或大括号，这样可以更安全
* `=`是最基本的变量
* `:=`是覆盖之前的值
* `?=`是如果没有被赋值过，就赋予等号后面的值
* `+=`是添加等号后面的值

## 清理文件

* PowerShell

  ```makefile
  OBJS = main.o add.o
  
  target: $(OBJS) main
  
  main:
  	g++ $(OBJS) -o main
  
  %.o: %.cpp
  	g++ -I. -c $< -o $@
  
  clean:
  	del $(OBJS) main.exe
  ```

* Bash

  ```makefile
  OBJS = main.o add.o
  
  target: $(OBJS) main
  
  main:
  	g++ $(OBJS) -o main
  
  %.o: %.cpp
  	g++ -I. -c $< -o $@
  
  clean:
  	rm -rf $(OBJS) main
  ```

  

# Makefile高级用法

## 文件过滤

```makefile
SRCS := $(shell find ./* -type f | grep '\.cpp')
$(warning SRCS is $(SRCS))

OBJS :=$(patsubst %.cpp, %.o,$(filter %.cpp, $(SRCS)))
$(warning OBJS is $(OBJS))

target: $(OBJS) main

main:
	g++ $(OBJS) -o main

%.o: %.cpp
	g++ -I. -c $< -o $@

clean:
	rm -rf *.o main	
```

## 编译选项

```makefile
SRCS := $(shell find ./* -type f | grep '\.cpp')
$(warning SRCS is $(SRCS))

OBJS :=$(patsubst %.cpp, %.o,$(filter %.cpp, $(SRCS)))
$(warning OBJS is $(OBJS))

#编译选项
CFLAGS := -g  -o2 -Wall -Werror -Wno-unused -ldl -std=c++11

#搜索路径
INCLUDE := -I.

target: $(OBJS) main

main:
	g++ $(OBJS) -o main

%.o: %.cpp
	g++ $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o main	
```

# Makefile 多入口编译

## 多入口

```makefile
CC := g++

SRCS := $(shell find ./* -type f | grep '\.cpp' | grep -v './main\.cpp' | grep -v './test\.cpp')
$(warning SRCS is $(SRCS))

OBJS :=$(patsubst %.cpp, %.o,$(filter %.cpp, $(SRCS)))
$(warning OBJS is $(OBJS))

#搜索路径
INCLUDE := -I.

MAIN_SRC :=main.cpp
MAIN_OBJ :=$(patsubst %.cpp,%.o,$(MAIN_SRC))
$(warning $(MAIN_OBJ))
MAIN_EXE :=main

TEST_SRC :=test.cpp
TEST_OBJ :=$(patsubst %.cpp,%.o,$(TEST_SRC))
$(warning $(TEST_OBJ))
TEST_EXE :=test

target:$(MAIN_EXE) $(TEST_EXE)

$(MAIN_EXE):$(OBJS) $(MAIN_OBJ) 
	$(CC)  -o $@ $^ $(INCLUDE) 

$(TEST_EXE):$(OBJS) $(TEST_OBJ) 
	$(CC)  -o $@ $^ $(INCLUDE) 

%.o: %.cpp
	$(CC) $(INCLUDE) -c $< -o $@

clean:
	rm -rf *.o $(MAIN_EXE) $(TEST_EXE)
```

* `$(patsubst %.cpp,%.o,$(MAIN_SRC))`表示将`MAIN_SRC`中的所有.cpp文件替换为.o的文件赋值给`MAIN_OBJ`

## 单入口模板

```makefile
#设置编译器
CC := g++

SRCS := $(shell find ./* -type f | grep '\.cpp' | grep -v './main\.cpp')
$(warning SRCS is $(SRCS))

OBJS :=$(patsubst %.cpp, %.o,$(filter %.cpp, $(SRCS)))
$(warning OBJS is $(OBJS))

#搜索路径
INCLUDE := -I.

MAIN_SRC :=main.cpp
MAIN_OBJ :=$(patsubst %.cpp,%.o,$(MAIN_SRC))
MAIN_EXE :=main

target:$(MAIN_EXE) 
$(MAIN_EXE):$(OBJS) $(MAIN_OBJ) 
	$(CC)  -o $@ $^ $(INCLUDE) 

%.o: %.cpp
	$(CC) $(INCLUDE) -c $< -o $@

clean:
	rm -rf *.o $(MAIN_EXE) 
```



## inc 、src

* 结构图

```she
|-inc
|  └add.h
|-src
|  └add.cpp
|-main.cpp
|-Makefile
```

* 将 add.cpp 挪到 src 目录下仍然可以正常编译
* 将 add.h、sub.h 挪到 inc目录下只需修改 INCLUDE 即可

```makefile
#设置编译器
CC := g++

SRCS := $(shell find ./* -type f | grep '\.cpp' | grep -v './main\.cpp')
$(warning SRCS is $(SRCS))

OBJS :=$(patsubst %.cpp, %.o,$(filter %.cpp, $(SRCS)))
$(warning OBJS is $(OBJS))

#搜索路径
INCLUDE := -I. -I ./inc

MAIN_SRC :=main.cpp
MAIN_OBJ :=$(patsubst %.cpp,%.o,$(MAIN_SRC))
MAIN_EXE :=main

target:$(MAIN_EXE) 
$(MAIN_EXE):$(OBJS) $(MAIN_OBJ) 
	$(CC)  -o $@ $^ $(INCLUDE) 

%.o: %.cpp
	$(CC) $(INCLUDE) -c $< -o $@

clean:
	rm -rf *.o $(MAIN_EXE) 
```

# 静态库 动态库

P11 P12

> 【如何编译 C++ 程序：轻松搞定 Makefile】https://www.bilibili.com/video/BV1dF41117NV?p=11&vd_source=ec4e4974e1b56ed330afdb6c6ead1501
