#include<iostream>
using namespace std;

// 1 不要返回局部变量的引用
// 函数执行完后，a 的内存就被释放了
int &test01() {
    int a = 10;
    return a;
}

// 2 函数的调用可以作为左值
int &test02() {
    static int a = 10;
    return a;
}

int main() {
    // int &ref = test01();
    // cout << ref << endl;  // Segmentation fault

    int &ref2 = test02();
    cout << "ref2 = " << ref2 << endl;   // 10

    test02() = 1000;
    cout << "ref2 = " << ref2 << endl;   // 1000
    return 0;
}
