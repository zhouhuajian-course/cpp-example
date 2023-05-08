#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

void string_test()
{
    string str = "test";
    cout << str.length() << endl;
    string str2 = str;
    cout << str2 << endl;
    // 转为 C 的 char *
    cout << str.c_str() << endl;
    // 输入输出
    // string s;
    // cin >> s;  
    // cout << s << endl;  
    // 访问字符串中的字符
    string s = "1234567890";
    for(int i = 0, len = s.length(); i < len; i++){
        cout << s[i] << " ";
    }
    cout << endl;
    s[5] = '5';
    cout << s << endl;

    string first = "first";
    string second = "second";
    string temp = first + " " + second;
    cout << temp << endl;

    cout << "=============" << endl;
}