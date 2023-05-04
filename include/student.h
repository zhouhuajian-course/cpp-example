#ifndef INCLUDE_STUDENT_H_
#define INCLUDE_STUDENT_H_

#include <string>

using namespace std;

class Student
{
private:
    string name;
    int age;
public:
    Student(string name, int age);
    void intro();
    ~Student();
};

#endif