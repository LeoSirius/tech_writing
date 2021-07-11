#include<iostream>
using namespace std;

// 常量引用
// 作用：修饰形参，防止误操作

int main() {
    // 一般来说，引用的右值必须是个对象
    // 但常量引用右边可以直接用字面量
    // 编译器会加一个临时的变量，相当于
    // int tmp = 10;
    // const int &ref = tmp;
    const int &ref = 10;

    return 0;
}
