#include <iostream>
#include "version.h"
#include "unix_timestamp.h"
#include "student.h"

using namespace std;

// 直接声明，不需要额外头文件
// 参数名可以去掉，可以多次声明
void log(const char*);
void log(const char* message);

int main(int argc, char const *argv[])
{
    log("Hello World!");

    Student stu("zhouhuajian", 18);
    stu.intro();

    std::cout << "CPP_MANUAL" << std::endl;
    std::cout << VERSION_MAJOR << std::endl;
    unix_timestamp ut;
    set_unix_timestamp(&ut);
    std::cout << ut.sec << std::endl;
}