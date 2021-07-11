#include <iostream>
using namespace std;

// 全局变量
int g_a = 10;
int g_b = 10;

// const 修饰的全局变量（即全局常量）
const int c_g_a = 10;
const int c_g_b = 10;

int main() {
    // 全局区存放：
    // 全局变量、静态变量、常量

    // 普通的局部变量
    int a = 10;
    int b = 10;

    // (long)&a 把内存地址转换成10进制。不转默认是16进制
    cout << "局部变量 a 的地址" << (long)&a << endl;  // 局部变量 a 的地址140722278760304
    cout << "局部变量 b 的地址" << (long)&b << endl;  // 局部变量 b 的地址140722278760308

    cout << "全局变量 g_a 的地址" << (long)&g_a << endl;
    cout << "全局变量 g_b 的地址" << (long)&g_b << endl;

    // 静态变量
    static int s_a = 10;
    static int s_b = 10;
    cout << "静态变量 s_a 的地址" << (long)&s_a << endl;
    cout << "静态变量 s_b 的地址" << (long)&s_b << endl;

    // 常量
    // 字符串常量 (双引号引起来的字符串)
    cout << "字符串常量的地址" << (long)&"hello world" << endl;

    // const 修饰的变量
    // const 修饰的全局变量（全局常量），const 修饰的局部变量
    cout << "全局常量 c_g_a 的地址" << (long)&c_g_a << endl;
    cout << "全局常量 c_g_b 的地址" << (long)&c_g_b << endl;

    // !!! 注意这里 const 修饰的局部两变量在 栈区，不在全局区
    const int c_l_a = 10;
    const int c_l_b = 10;
    cout << "局部常量 c_l_a 的地址" << (long)&c_l_a << endl;
    cout << "局部常量 c_l_b 的地址" << (long)&c_l_b << endl;

    return 0;
}