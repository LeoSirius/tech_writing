#include <iostream>
using namespace std;

// 1. new 的基本语法
int *func() {
    // 在堆区创建一个整型数据
    // new 返回的是 该数据类型的指针
    int *p = new int(10);
    return p;
}

void test01() {
    int *p = func();
    cout << *p << endl;
}

// 2. 用 new 在堆区开辟数组
void test02() {
    int *arr = new int[10];  // 返回这个数组的首地址
    for (int i = 0; i < 10; i++) {
        arr[i] = i + 100;
    }
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << endl;
    }

    // 释放数组的时候，要加中括号
    delete []arr;
}

int main() {
    test01();
    test02();

    return 0;
}
