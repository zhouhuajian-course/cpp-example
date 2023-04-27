#include <iostream>
#include "version.h"
#include "unix_timestamp.h"

using namespace std;

int main(int argc, char const *argv[])
{
    std::cout << "CPP_MANUAL" << std::endl;
    std::cout << VERSION_MAJOR << std::endl;
    unix_timestamp ut;
    set_unix_timestamp(&ut);
    std::cout << ut.sec << std::endl;
}