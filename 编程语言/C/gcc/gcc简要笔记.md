# gcc 简要笔记

## 编译多个文件

两种 include 方式

- `include <somefile>` 先搜索系统标准头文件路径（可以用 cpp -v 查看, cpp is shortcut for C preprocessor）
- `include "somefile"` 从当前目录和 gcc -I 指定的路径来搜索

> gcc -Idir dir 是头文件所在路径，gcc -Ldir dir 是库文件所在路径

I 和 L 是指定 dir，而 llibrary 则是指定库

-l 和 -L

- -l: -larchive Add archive file archive to the list of files to link. ld will search its path-list for occurrences of libarchive.a for every archive specified.
- -L: -Lsearchdir Add path searchdir to the list of paths that ld will search for archive libraries and ld control scripts.

## 常用选项解释

## 静态库和动态库

