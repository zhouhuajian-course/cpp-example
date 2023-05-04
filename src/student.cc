#include "student.h"
#include <string>
#include <iostream>
using namespace std;

Student::Student(string name, int age) {
    this->name = name;
    this->age = age;
}
void Student::intro() {
    cout << this->name << this->age << endl;
}
Student::~Student() {
    
}