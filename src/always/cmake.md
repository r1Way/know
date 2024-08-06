# CMake

## 模板

```cmake
cmake_minimum_required(VERSION 3.14)

project(hello)

include_directories(./ ./inc)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(main ${SOURCES} main.cpp)s
```

## 参考

* 本文件为下方链接中视频的笔记

> [如何编译 C++ 程序：轻松搞定 CMake](https://www.bilibili.com/video/BV15j411b7F8?vd_source=ec4e4974e1b56ed330afdb6c6ead1501)

## 安装

* 检验

```shell
cmake --version
```

>  [Windows下Cmake安装步骤详解（图文）_windows终端安装cmake-CSDN博客](https://blog.csdn.net/qq_42598221/article/details/121952160?ops_request_misc=%7B%22request%5Fid%22%3A%22172282160116800222890009%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=172282160116800222890009&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~blog~top_positive~default-1-121952160-null-null.nonecase&utm_term=windows Cmake&spm=1018.2226.3001.4450)

## CMake 编译流程

1. 编写  
2. 执行 `cmake PATH` 生成 Makefile(PATH 为CMakeLists.txt所在目录)
3. 执行 make 编译

## 编写CMakeLists.txt

```cmake
add_executable(main main.cpp)
```

> add_executable：使用指定的源文件生成目标可执行文件

## 生成Makefile文件

* 一般

```shell
cmake .
```

* 若未生成 Makefile文件，而是生成了一大堆其他文件

第一次

```shell
cmake . -G "Unix Makefiles"
```

之后

```shell
cmake .
```

> [解决【Windows】下CMake不能生成makefile的问题_cmake不生成makefile-CSDN博客](https://blog.csdn.net/qq_32939413/article/details/112381319)

## 编译项目

```shell
make
```

## 修复告警

```cmake
cmake_minimum_required(VERSION 3.14)

project(hello)

add_executable(main main.cpp)
```

> cmake_minimum_required:用于设定CMake的最低版本
>
> project:指定工程名称

## 语言版本

```cmake
cmake_minimum_required(VERSION 3.14)

project(hello)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp)
```

> set(CMAKE_CXX_STANDARD 11)：增加c++ 11

## 编译选项

```cmake
cmake_minimum_required(VERSION 3.14)

project(hello)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-g -Wunused)

add_executable(main main.cpp)
```

> add_compile_options:给后续的目标加上编译选项

```cmake
target_compile_options(main PUBLIC -Wall -Werror)
```

> target_compile_options:给指定的目标加上编译选项

## 多文件编写

### 代码

add.h

```c++
#pragma once
int add(int x,int y);
```

add.cpp

```c++
#include"add.h"
int add(int x,int y)
{
    return x+y;
}
```

main.cpp

```c++
#include<iostream>
#include"add.h"

int main()
{
    std::cout<<add(3,2);
    return 0;
}
```

### 单个添加

```cmake
cmake_minimum_required(VERSION 3.14)

project(hello)

add_executable(main add.cpp main.cpp)
```

> 紧需将其他.cpp添加到add_executable即可

### 自动添加

自动把src目录下的cpp文件添加到项目里

```cmake
include_directories(./)
file(GLOB_RECURSE SOURCES "src/*.cpp")
```

>  file:获取src目录下的所有.cpp文件，并将其保存到变量中
>
> include_directories:添加头文件搜索路径

### 添加多个头文件搜索路径

```cmake
include_directories(./ ./inc)
```



## Trouble Shooting

### Invalid argument

* 报错

```shell
CMake Error: Target DependInfo.cmake file not found
Building CXX object CMakeFiles/main.dir/main.cpp.obj
c++.exe: error: C:/Users/錯sktop/temp/main.cpp: Invalid argument
c++.exe: fatal error: no input files
```

* 解决

  路径有中文

### add.h: No such file or directory
* 报错

```shell
C:/temp/src/add.cpp:1:9: fatal error: add.h: No such file or directory
 #include"add.h"
```

* 解决

   #include"add.h"为相对路径，需要将.h文件所在路径添加到搜素路径

```cmake
include_directories(./)
```

