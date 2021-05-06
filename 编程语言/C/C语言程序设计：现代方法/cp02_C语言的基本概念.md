# 2 C 语言的基本概念

## 2.1 编写一个简单的 C 程序

```c
#include <stdio.h>

int main(void)
{
    printf("To C, or not to C: that is the question.\n");
    return 0;
}
```

## 2.2 简单程序的一般形式

C 的 3 个关键语言特性：

- 指令：即预处理指令，由预处理器进行处理。由 # 开头
- 函数：C 程序即是函数的集合
- 语句

## 2.3 注释

两种注释：

- `\* comment contents *\`
- `\\ comment contents` 这种是 C99 中新加的

## 2.6 常量

可以用宏定义

```c
#define INCHES_PER_POUND 166
```
