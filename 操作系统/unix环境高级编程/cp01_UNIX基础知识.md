# 1 UNIX 基础知识

这一章的例子都不用深究，后面会有详细的介绍

## pre knowledge: apue 库的使用

apue的库下载好后（注意在make前，确保systype.sh是可执行文件。）

```
sudo apt install libbsd-dev
cd apue.3e
# make
......

sudo cp ./include/apue.h /usr/include/    # 这是个头文件
sudo cp ./lib/libapue.a /usr/local/lib/   # 这个是库
```

使用

```c
gcc filename.c -lapue
```

## 1.4 文件和目录

```c
#include "apue.h"
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR              *dp;
    struct dirent    *dirp;


    if (argc != 2) {
        err_quit("usage: ls directory_name");
    }
    if ((dp = opendir(argv[1])) == NULL)
        err_sys("can't open %s", argv[1]);

    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }
    closedir(dp);
    exit(0);
}
```

## 1.5 输入和输出

### 文件描述符

文件描述符是一个小的非负整数，进程在内核中每打开或是创建一个新的文件，都会返回其文件描述符。

### 标准输入、标准输出和标准错误

每当运行一个新的程序是，所有 shell 都会为其打开 3 个文件描述符，即标准输入、标准输出和标准错误

### 不带缓冲的 IO

open read write lseek close 等函数都是不带缓冲的，她们都用文件描述符作为参数
