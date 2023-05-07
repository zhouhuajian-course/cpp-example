#include <iostream>
#include "version.h"
#include "unix_timestamp.h"
#include "student.h"
#include <stdlib.h>

using namespace std;

// 直接声明，不需要额外头文件
// 参数名可以去掉，可以多次声明
void log(const char*);
void log(const char* message);

extern "C" int add(int a, int b) {
  return a + b;
}

// int main_my_epoll();

int main(int argc, char const *argv[])
{
    // C/C++混合编程
    cout << add(1, 2) << endl;

    // 获取环境变量值
    char *str;
    str = getenv("PATH");
    cout << str << endl;
    str = getenv("USER");
    cout << str << endl;
    str = getenv("HOME");
    cout << str << endl;

    log("Hello World!");

    Student stu("zhouhuajian", 18);
    stu.intro();

    std::cout << "CPP_MANUAL" << std::endl;
    std::cout << VERSION_MAJOR << std::endl;
    unix_timestamp ut;
    set_unix_timestamp(&ut);
    std::cout << ut.sec << std::endl;

    // main_my_epoll();
}