# 3 文件 IO

## 3.1 引言

本章讨论的是`不带 buffer` 的IO。这里`不带 buffer`的意思是：每个 read 和 write 都会调用一个内核中的系统调用。

## 3.2 文件描述符

对内核而言，所有打开的文件都通过文件描述符引用。

文件描述符的范围是 0 到 OPEN_MAX - 1

## 3.3 函数 open 和 openat

openat 比 open 多了一个参数 fd

- path 参数为绝对路径。这是 fd 被忽略，openat 等于 open
- path 参数为相对路径。则以 fd 为相对。 fd 就是相对路径起点目录的文件描述符
- path 参数为相对路径。fd 值为一个特殊值 AT_FDCWD，则以 CWD 为相对起点，这时也和 open 一样

openat 是后来新加的，其加上的原因是：

- 可以用相对路径打开文件名
- 避免 time-of-check-to-time-of-use （TOCTTOU）的错误

TOCTTOU 的基本思路：

如果有两个基于文件的函数调用。第二个调用依赖于第一个调用的结果。那么程序是脆弱的。因为两个调用之间没有原子性，文件可能在中间被修改了。

常量 `_POSIX_NO_TRUNC` 决定了文件名或路径名超过上限时，是返回错误还是直接截断。在 linux 中是返回一个错误

## 3.6 函数 lseek

### lseek 的基本使用

文件偏移量的单位是字节。打开一个文件时，除非指定 O_APPEND，否则文件偏移量默认为0。

进行读写操作时，从文件偏移量开始，并增加所读写的字节数。

lseek 函数可以显示的设置一个文件的文件偏移量。

```c
off_t lseek(int fd, off_t offset, int whence)  // 返回新的偏移量
```

- whence == SEEK_SET, 则设置文件偏移量为 0 + offset
- whence == SEEK_CUR, 则设置文件偏移量为 当前偏移量 + offset
- whence == SEEK_END, 则设置文件偏移量为 文件长度 + offset


offset 传0，可以获取当前文件的文件偏移量

```c
off_t currpos;
currpos = lseek(fd, 0, SEEK_CUR);
```

下面的程序测试标准输入能不能设置偏移量

```c
#include "apue.h"

int main(void)
{
    if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1) {
        printf("cannot seek\n");
    } else {
        printf("seek OK\n");
    }
    return 0;
}
```

测试结果

```
(base) root test # ./a.out
cannot seek
(base) root test # ./a.out < 1.c
seek OK
```

> lseek 本身不会引起 IO 操作，只是在内核中记录偏移量

### 文件中的空洞

如果文件的偏移量大于文件的长度，这时进行写操作，则会在文件中留一个空洞。空洞对应的字节会被读为 0。

下面的程序会创建一个有洞的文件

```c
#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
    int fd;

    if ((fd = creat("file.hole", FILE_MODE)) < 0)
        err_sys("creat error");

    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error");
    // offset now 10

    if (lseek(fd, 16384, SEEK_SET) == -1)
        err_sys("lseek error");
    // offset now 16384

    if (write(fd, buf2, 10) != 10)
        err_sys("buf2 write error");
    // offset now 16394

    exit(0);
}
```

可以看到文件大小为 16394B，但只占了 8 个磁盘块，用 `od -c` 看到文件内容。中间全是 `\0`

```
(base) root test # ls -ls file.hole
8 -rw-r--r-- 1 root root 16394 Jul 15 17:01 file.hole
(base) root test # od -c file.hole
0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
*
0040000   A   B   C   D   E   F   G   H   I   J
0040012
```

在创建一个无洞的同样大小的文件，可以看到无洞的文件占了 20 个磁盘块。说明有洞的文件的洞虽然会撑起来文件的大小，但并不会占磁盘空间。

```
(base) root test # dd if=/dev/zero of=file.nohole bs=16394 count=1
1+0 records in
1+0 records out
16394 bytes (16 kB, 16 KiB) copied, 0.00130466 s, 12.6 MB/s
(base) root test # ls -ls file.nohole file.hole
 8 -rw-r--r-- 1 root root 16394 Jul 15 17:01 file.hole
20 -rw-r--r-- 1 root root 16394 Jul 15 17:13 file.nohole
```

## 3.7 read 函数

返回值：读到的字节，若已到文件尾，则返回 0；若出错，返回 -1

很多情况下实际返回值可能小于要求读取的字节数，如：从管道或 FIFO 中读，网络的缓冲机制、某些面向记录的设备一次最多返回一个记录

## 3.8 write 函数

返回值的意义和 read 函数相同

## 3.10 文件共享

### 内核中打开文件的数据结构

内核使用三种数据结构表示打开文件：

- 每个进程中有一个「打开文件描述符表」，其中每项包含：
    - 文件描述符
    - 指向文件表项的指针
- 每个打开的文件有一个文件表项，其中每项包含：
    - 文件状态标志（读、写、添加、同步和非阻塞等）
    - 当前文件偏移量
    - 指向文件 v-node 的指针
- 每个打开的文件（或设备）都有一个 v-node，v-node 包含「文件类型」和「对文件进行操作的各种函数的指针」。v-node 会包含 i-node （从磁盘读入的索引节点）

i-node 中包含文件所有者、文件长度、物理磁盘地址等信息。

> linux 中没有 v-node，而是直接用的通用的 i-node

### 两个独立的进程打开共一个文件

- 打开文件描述符表：每个进程自个有一个（即有两个）
- 文件表项：每个进程相应的 fd 各指向一个（即有两个）
- v-node：两个文件表项的指针都指向同一个 v-node（即只有一个）

但是当在 fork 或其他一些情况时（如 dup），父子进程的 fd 会指向同一个「文件表项」。因为「文件表项」不在进程空间中

## 3.11 原子操作

### 追加到文件末尾

早起没有 O_APPEND 标志时，在一个文件末尾添加需要手动 lseek 偏移量，然后再 write。如果多个进程并发地这样操作同一个文件，则会把数据写错。

若用 O_APPEND 打开文件，则在每次写操作前，内核都会把文件偏移量移动到最新的 EOF。

### pread 和 pwrite 函数

pread 比 read 多一个 offset 参数，类似于先 lseek 再 read，但又有两个重要区别：

- pread 的定位和读操作无法中断
- 不更新当前的文件偏移量

pwrite 和 pread 也类似

## 3.12 dup 和 dup2 函数

### dup 和 dup2 简单介绍

这两个函数的作用都是复制文件描述符。复制出来的新的文件描述符和原文件描述符会指向同一「文件表项」

```c
int dup(int fd);
int dup2(int fd, int fd2);
```

dup 复制 fd 并返回一个最小能用的文件描述符。dup2 中的 fd2 可指定要想的文件描述符，若已被占用，则关闭原来的文件描述符。

### fcntl 函数

fcntl 也可以用来复制文件描述符。其在后面详细介绍

`dup(fd)` 等效于 `fcntl(fd, F_DUPFD, 0)`

而调用

```c
dup2(fd, fd2);
```

等效于

```c
close(fd2);
fcntl(fd, F_DUPFD, fd2)
```

后一个等效的两者之前还是与区别：

- dup2 是原子操作，而先 close 再 fcntl 则不是
- dup2 和 fcntl 有一些不用的 errno

## 3.13 函数 sync、fsync 和 fdatasync

这三个函数用来保证「磁盘」中的数据和「缓冲区」的数据一致

- `void sync(void);` 将修改过的块缓冲区排入写队列，然后返回。不等实际写操作结束
- `int fsync(fd);` 只对特定的 fd 起作用。并等写操作结束再返回
- `int fdatasync(fd);` fdatasync 和 fsync 类似。不过 fdatasync 只对文件数据起作用，而 fsync 还会对文件的属性起作用

## 3.14 fcntl 函数

fcntl 用来改变已打开的文件的属性

```c
int fcntl(int fd, int cmd, .../* int arg */);
```

根据 cmd 的不同，其有 5 种功能

- 复制一个已有的文件描述符 cmd = F_DUPFD or F_DUPFD_CLOEXEC
- 获取/设置文件描述符标志 cmd = F_GETFD or F_SETFD
- 获取/设置文件状态标志 cmd = F_GETFL or F_SETFL （即是在 open 时传的文件状态标志）
- 获取/设置异步IO所有权 cmd = F_GETOWN or F_SET_OWN
- 获取/设置记录锁 cmd = F_GETLK or F_SETLK or F_SETLKW

fcntl 的返回值和 cmd 有关。如果出错都返回 -1。

- cmd = F_DUPFD 返回新的文件描述符
- cmd = F_GETFD or F_GETFL 返回相应的标志
- cmd = F_GETOWN 返回正的进程 ID 或负的进程组 ID

下面的程序打印指定文件描述符的一些标志

```c
#include "apue.h"
#include <fcntl.h>


int main(int argc, char *argv[])
{
    int val;

    if (argc != 2)
        err_quit("usage: a.out <descriptor#>");

    if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
        err_sys("fcntl error for fd %d", atoi(argv[1]));

    switch (val & O_ACCMODE) {
        case O_RDONLY:
            printf("read only");
            break;
        case O_WRONLY:
            printf("write only");
            break;
        case O_RDWR:
            printf("read write");
            break;
        default:
            err_dump("unknown access mode");
    }

    if (val & O_APPEND)
        printf(", apppend");
    if (val & O_NONBLOCK)
        printf(", nonblocking");
    if (val & O_SYNC)
        printf(", synchronous writes");

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if (val & O_FSYNC)
        printf(", synchronous writes");
#endif
    putchar('\n');
    exit(0);
}
```

`5<>tmp.foo` 表示在描述符 5 上打开文件 tmp.foo 以供读写

```
(base) root test # ./a.out 0 < /dev/tty
read only
(base) root test # ./a.out 1 > tmp.foo
(base) root test # cat tmp.foo
write only
(base) root test # ./a.out 2 2>>tmp.foo
write only, apppend
(base) root test # ./a.out 5 5<>tmp.foo
read write
```

## 3.15 ioctl

这个函数用来进行一些 IO 操作。终端是使用这个函数最多的地方

## 3.16 /dev/fd

打开文件 `/dev/fd/n` 等效于复制文件描述符 n


