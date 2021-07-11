#include <iostream>
using namespace std;

int func(int a, int b = 20, int c = 30) {
    return a + b + c;
}

// 注意事项
// 1. 默认参数的右边必须全是默认参数
// 2. 声明和实现只能一个有默认参数

int main() {

    cout << func(10) << endl;

    return 0;
}
