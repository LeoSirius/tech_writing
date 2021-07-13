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



