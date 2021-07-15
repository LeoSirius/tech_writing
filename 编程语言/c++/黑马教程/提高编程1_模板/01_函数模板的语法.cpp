#include <iostream>
using namespace std;

template<typename T>   // typename 可以换成 class
void mySwap(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}

int main() {
    // 使用模板的两种方法
    // 1. 自动类型推到
    int a = 10;
    int b = 20;
    mySwap(a, b);
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    double c = 1.1;
    double d = 2.2;
    // 2. 显示指定类型
    mySwap<double>(c, d);
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;

    return 0;
}
