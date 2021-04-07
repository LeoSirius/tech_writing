# C 程序的编译过程

大概可以分成4步

- Preprocessing: -E
- Compilation: -S
- Assembly: -c
- Linking

我们以下面一段程序为例（在本文中，文件名为 test.c）

```c
/*
 * "Hello, World!": A classic
 */

#include <stdio.h>

int
main(void)
{
    puts("Hello, World!");
    return 0;
}
```

## Preprocessing

预处理阶段要做的就是处理`预处理命令`。代码中以 # 开头的行是预处理命令。预处理命令有自己独特的语法和语义。预处理命令的主要作用：

- include 其他文件
- 定义宏
- 按条件忽略代码

gcc 的选项 -E 可以产生 preprocessed code, that is, stop after preprocessing

```
gcc -E test.c
```

## Compilation

这个阶段会把预处理后的代码编译成处理器架构相关的汇编代码。

gcc 的选项 -S stop after compilation

```
gcc -S test.c
```

-S 会生成 .s 文件，而 -E 默认是直接输出到标准输出

## Assembly

这一阶段生成机器代码（目标文件，以 .o 结尾）

gcc -c 生成目标文件

```
gcc -c test.c
```

是用 hexdump 或 od 可以查看其内容

## Linking

这个阶段把缺的地方和顺序不对的地方进行调整，生成最后的可执行文件。gcc 不加参数即可

```
gcc test.c
```
