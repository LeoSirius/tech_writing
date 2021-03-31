# gcc 简要笔记

## 编译多个文件

两种 include 方式

- `include <somefile>` 先搜索系统标准头文件路径（可以用 cpp -v 查看）和 
- `include "somefile"` 从当前目录和 gcc -I 指定的路径来搜索

> gcc -Idir dir 是头文件所在路径，gcc -Ldir dir 是库文件所在路径

## 常用选项解释

## 静态库和动态库

