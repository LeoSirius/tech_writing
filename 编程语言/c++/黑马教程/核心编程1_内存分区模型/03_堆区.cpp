#include <iostream>
using namespace std;

int *func() {
    // 对象是存在 堆区 的，不会被函数释放
    // 指针 a 本身是局部变量。但是 a 指向的对象是在堆区
    int *a = new int(10);
    return a;
}

int main() {
    int *p = func();
    cout << *p << endl;

    return 0;
}