# CPP Manual

## 代码规范

https://google.github.io/styleguide/cppguide.html

## 引入头文件

include "" 和 <>

自己编写的头文件使用 #include "..."
标准库和第三方库使用 #include <...>

## cmake 命令文档

https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html

## cmake 自动生成 配置文件

.h.in 输入文件

里面的 @XXX@ 会被相应的变量值所替换
输出对应的 .h 文件

例如 include/version.h.in -> include/version.h

## 文件后缀

C语言 头文件 .h 源文件 .c

C++语言 

头文件最开始使用 .h .c 但和C语言无法区分，于是使用.H .C .h++ .c++进行区分，  
但个别系统文件名不区分大小写，个别系统则文件不能出现+， 
于是大家开发C++程序普通使用以下文件后缀

头文件 .h  .hpp .hxx (.h 仍然被普遍使用在c++ 可能是解析原理一样 都是简单地引入和替换)  
源文件 .cc .cpp .cxx 