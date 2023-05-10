# CPP Manual

https://cplusplus.com/reference/

## 函数或方法默认值

error: default argument given for parameter 1

不能 函数或方法声明和定义同时设置默认值，只需要声明或定义设置一次即可，推荐声明时设置

## 字符串 string

https://cplusplus.com/reference/string/string/

字符串拼接
```c++
string content = "success";  
// 分多行写，不需要+号，自动拼接
string responce = "HTTP/1.1 200 OK\r\n" 
                  "Content-Type: text/html\r\n" 
                  "Content-Length: ";
responce += content.length();
responce += "\r\n\r\n";
responce += content;
// 暂时不能使用 responce += content.length() + "..." + "..."
// 原因不明，可能不支持
```                            


```
需要包含 #include <string>
需用命名空间std using namespace std;
length() 获取真实长度
+或+= 拼接字符串
下标访问字符 str[i]
str.c_str() 生成不可改的字符指针 const char* 指向字符串第一个字符，最后有\0 ("test\0")
使用C语言字符串 需要包含 #include <string.h>
使用C语言输入输出 需要包含 #include <stdio.h>
C语言的 strlen 也是 真实长度 不包括\0

可以抽象理解为，实际实现比较复杂，通过vs调试，更容易理解
class string {
  private:
	char* _ptr;						  // 实际存储字符串内容的空间 跟string::c_str()返回的地址一样 
	size_t _size;					  // 存储字符串当前的容量 
	size_t _capacity;				// 存储字符串最大容量 
}
例如
string str = "test";
使用16字节空间存储内容，15个字节可用，最后一个字节必须为\0
所以 size=4 capacity=15 
ptr 指向16字节首个字节 
t e s t \0 \0 \0 \0 \0 \0 \0 \0 \0 \0 \0 \0

C语言两种方式表示字符串
字符数组、字符指针
```

## epoll 多路复用

src/epoll

不管是select、epoll还是其他，原理基本如下

服务端，创建一个文件(socket文件，文件ID FD)，监听某个端口，  
创建一个多路复用管理器，文件注册到管理器，提供文件感兴趣的事件，服务端Socket对读事件感兴趣  
有可读事件，表示有客户端连接，连接后，创建一个文件(socket文件 文件ID FD)
将socket文件注册到管理器，提供文件感兴趣的事件，最开始只需要注册读事件，  
如果有可读事件，读取数据，写出数据，如果一次性没写完，避免阻塞线程，修改感兴趣事件增加写事件，  
有可写事件再继续写（客户端正常断开连接和异常断开连接，都会触发可读事件，根据返回值或抛异常判断）  
注册到管理器，由一个列表或集合统一维护，然后阻塞等待事件发生，如果有事件发生，  
一般会返回发生事件的个数，并且可以获取另一个集合，包含所有发生的事件，  
处理事件，一般事件对应fd为服务端fd，则表示有客户端连接，其他是跟客户端fd相关的事件，  
有些语言的注册管理器，处理完事件后不会自动删除，需要手动删除，例如java  
如果没处理事件，该事件会一直留在第二个集合中，会让多路复用管理器一直有未处理事件提供，  
所以必须及时处理每个事件

基本原理了解后，大多数都是代码实现问题，如果再加上多线程，加上不同线程分工合作，加上异步任务，加上处理粘包半包，处理大数据量读写，处理nagle，处理一个线程绑定多个客户端，保证一个客户端始终由同一个线程处理，避免读写混乱等，就能实现高性能服务器

事件注册、事件循环

## extern "C" C/C++混合编程

不使用 C++ 的函数重载 用 C 语言的方式处理

```c++
extern "C" int add(int a, int b) {
  return a + b;
}
```

## 获取环境变量

```c++
#include <stdlib.h>

char *str;
str = getenv("PATH");
str = getenv("USER");
str = getenv("HOME");
```

## 代码规范

https://google.github.io/styleguide/cppguide.html

1. 所有头文件，可以被多次引入，但必须避免重复编译  #ifndef #define #endif
2. 类名、结构体使用大驼峰命名，
3. 文件名使用小写和下划线
4. 项目名使用 小写和短横线

备注：不同开发人员遵循的规范可能会很不一样


## C++ 程序 编译成可执行程序

1. 所有头文件都不会被编译；
2. 所有C++文件都会被编译成一个.o或.obj文件，编译前所以#开头的都会做预处理，#include只是简单复制粘贴内容
3. 所有C++的符号都必须声明，可以在头文件声明，再引入，或者直接声明，直接使用，定义可以其他文件定义
4. 所有C++文件被编译后，会被Link拼接在一起，变成可执行文件
5. 运行可执行文件 就会运行main函数

```
#include只是简单的打开文件 读取内容 粘贴 (例如 #include "endbrace.h")
VS可通过输出预处理内容、输出可读的汇编代码来查看编译结果，是否开启优化，以及不同的优化等级，会有不同的编译结果
主函数比较特别，即使返回类型写int，也可以不写return语句
static关键字，函数前，可以让函数只在当前obj文件中使用
inline关键字，函数前，内联，减少一次调用栈
extern关键字，函数声明前
application必须要有入口点，入口点可以不是main函数，可以自己指定
c++文件或头文件的所有内容，其实都是写给预编译器、编译器或链接器看的
错误信息 C开头为编译错误 LNK开头为链接错误 根据不同的错误分析问题
C++所有符号都有在某个命名空间下，没指定，就是std
C++编译时，会根据函数名、函数参数、函数返回值类型生成唯一的函数签名，链接时，会根据唯一的函数签名进行链接
类的public: private: 可以理解为，省去多次写public private而设计，默认private，
构造函数是 类名，析构函数是 ~类名
```

`g++ [options] file...`

-g            Produce debugging information. GDB can work with this debugging information. （输出的文件更大，GDB 调试时用，不兼容其他调试工具。）
-I dir        Add the directory dir to the list of directories to be searched for header files during preprocessing.      
-o <file>     Place the output into <file>. 生成可执行文件

`g++ -o app.exe a.cc b.cc c.cc`

> https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html#:~:text=To%20tell%20GCC%20to%20emit%20extra%20information%20for,GCC%20allows%20you%20to%20use%20-g%20with%20-O.
> -g Produce debugging information in the operating system’s native format (stabs, COFF, XCOFF, or DWARF). GDB can work with this debugging information. On most systems that use stabs format, -g enables use of extra debugging information that only GDB can use; this extra information makes debugging work better in GDB but probably makes other debuggers crash or refuse to read the program. If you want to control for certain whether to generate the extra information, use -gvms (see below).
> https://gcc.gnu.org/onlinedocs/cpp/Invocation.html#index-I

## Doxygen @param 参数方向 [in],[out],[in,out] 

示例

```c++
// https://www.doxygen.nl/manual/commands.html#cmdparam

// \param '['dir']' <parameter-name> { parameter description }

// The \param command has an optional attribute, dir, specifying the direction of the parameter. Possible values are "[in]", "[in,out]", and "[out]", note the [square] brackets in this description. When a parameter is both input and output, [in,out] is used as attribute. Here is an example for the function memcpy:
/*!
   Copies bytes from a source memory area to a destination memory area,
   where both areas may not overlap.
   @param[out] dest The memory area to copy to.
   @param[in]  src  The memory area to copy from.
   @param[in]  n    The number of bytes to copy
  /
void memcpy(void *dest, const void *src, size_t n);

// mysql-8.0.33/storage/innobase/include/row0mysql.h

/** Read the total number of records in a consistent view.
@param[in,out]  trx             Covering transaction.
@param[in]  indexes             Indexes to scan.
@param[in]  max_threads         Maximum number of threads to use.
@param[out] n_rows              Number of rows seen.
@return DB_SUCCESS or error code. */
dberr_t row_mysql_parallel_select_count_star(
    trx_t *trx, std::vector<dict_index_t *> &indexes, size_t max_threads,
    ulint *n_rows);
```

## 所有头文件都要避免多次编译

规则 文件相对路径，文件目录文件名变成大写，/.变成下划线，最后再加一个下划线

按情况是否要把项目名加上，如果是多项目的大项目，需要加上。

**The #define Guard**

All header files should have #define guards to prevent multiple inclusion. The format of the symbol name should be <PROJECT>_<PATH>_<FILE>_H_.

To guarantee uniqueness, they should be based on the full path in a project's source tree. For example, the file foo/src/bar/baz.h in project foo should have the following guard:

```c++
#ifndef FOO_BAR_BAZ_H_
#define FOO_BAR_BAZ_H_

...

#endif  // FOO_BAR_BAZ_H_
```

## 引入头文件

include "" 和 <>

自己编写的头文件和第三方库使用 #include "..."
标准库使用 #include <...>

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

## 其他

```
ifdef 读作 [if def]
```