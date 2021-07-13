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

下面这个程序简单的实现了 ls 的功能

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

每当运行一个新的程序时，所有 shell 都会为其打开 3 个文件描述符，即标准输入、标准输出和标准错误

### 不带缓冲的 IO

open read write lseek close 等系统调用都是不带缓冲的，她们都用文件描述符作为参数

下面这个程序将标准输入复制到标准输出

```c
#include "apue.h"

#define BUFFSIZE 4096

int main(void)
{
    int n;
    char buf[BUFFSIZE];

    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");

    if (n < 0)
        err_sys("read error");

    exit(0);
}
```

### 标准 I/O

标准库里的 IO 函数自动处理的缓冲。这些函数不用我们去指定缓冲区。

stdin 和 stdout 是标准 IO 对标准输入、标准输出的常量

下面的程序使用标准 IO 将标准输入复制到标准输出

```c
#include "apue.h"

int main(void)
{
    int c;

    while ((c = getc(stdin)) != EOF)
        if (putc(c, stdout) == EOF)
            err_sys("output error");

    if (ferror(stdin))
        err_sys("input error");

    exit(0);
}
```

## 1.6 程序和进程

### 程序

内核使用 exec 函数将程序读入内存，并执行

### 进程

下面这个程序输出自己的 pid，pid_t 是一个长整型

```c
#include "apue.h"

int main(void)
{
    printf("hello world from process ID %ld\n", (long)getpid());
    exit(0);
}
```

### 进程控制

主要的进程控制函数：fork, exec, waitpid

下面的程序用进程控制函数实现了一个简单的 shell

```c
#include "apue.h"
#include <sys/wait.h>

int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = 0;      // replace newline with null
        }
        if ((pid = fork()) < 0) {
            err_sys("fork error");
        } else if (pid == 0) {                      // child
            // execlp 用新的进程文件 buf 替换了子进程
            // 如果执行成功的话，再下面两行就不会执行
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        // parent
        if ((pid == waitpid(pid, &status, 0)) < 0) {
            err_sys("waitpid error");
        }
        printf("%% ");
    }
    exit(0);
}
```

### 线程和线程ID

线程 ID 是局部于进程的

## 1.7 出错处理

UNIX 系统函数出错时，通常返回一个负值。且将 errno 指定为一个特定值。

linux 支持多线程存取 errno，每个线程有自己独立的 errno

注意两点：

- errno 的值不会清。因此仅当函数返回错误时，再去检查 errno 的值
- 任何函数都不会将 errno 的值置为 0

两个函数：

- strerror 返回 errno 对应的消息字符串
- perror(const cahr *msg) 输出 `msg: strerror(errno)\n`

```c
#include "apue.h"
#include <errno.h>

int main(int argc, char *argv[])
{
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    errno = ENOENT;   // No such file or directory
    perror(argv[0]);
    exit(0);
}
```

### 出错恢复

- 致命性错误：无法恢复，最多打印一个消息，然后退出
- 非致命性错误：如资源短缺等

## 1.9 信号

对信号的三种处理方式：

- 忽略信号
- 按系统默认方式处理
- 提供一个信号处理函数

## 1.10 时间值

- 日历时间：从1970年1月1日00:00:00开始的秒数
- 进程时间（CPU时间）：以时钟滴答计算。每秒曾取过50, 60 或 100 个滴答

