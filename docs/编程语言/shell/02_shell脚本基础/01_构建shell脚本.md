# 构建shell脚本

## 使用多个命令

在同一行中使用多个命令可以用`;`隔开

```
(base) root ~ # date; who
Thu Feb  4 08:35:02 CST 2021
root     pts/0        2021-02-04 08:28 (123.123.134.45)
root     pts/1        2021-02-04 08:28 (123.123.134.45)
```

## 创建shell脚本文件

在脚本的第一行指定使用的shell

```bash
#!/bin/bash
date
who
```

## echo输出字符串的处理

- 没有单双引号，直接输出

```bash
#!/bin/bash
echo I am leo
```

- 有单或双引号，用另一种引号包起来

```bash
#!/bin/bash
echo "I'm leo"
echo 'I"m leo'
```

- `-n` 不输出结尾的换行

```bash
#!/bin/bash
echo -n 'Date: '
date
```

> 另外提一下，反引号的作用是命令替换，但是建议用`$()`而不是反引号

## 使用变量

变量在用`$`在字符串中可以直接使用

```bash
(base) root test # echo "home: $HOME"
home: /root
```

用花括号可以更好的隔开变量与字符串其他内容

```bash
(base) root test # echo "home: ${HOME}"
home: /root
```

想输出`$`符可以用转移符号

```bash
(base) root test # echo "money: $15"
money: 5
(base) root test # echo "money: \$15"
money: $15
```

## 命令替换

命令替换可以把命令的结果赋值给一个变量。用`\`\``或`$()`，但是建议使用后者。

命令替换中的命令其实是在一个子shell中跑的。

> 终端中用`路径+程序`执行的命令也是在子shell中执行的。直接执行一个内建命令，则不会创建子shell

## 重定向输入输出

内联输入重定向

```bash
(base) root test # wc << EOF
> string 1
> string 2
> string 3
> EOF
 3  6 27
```

## 数学运算

`Bourne shell`最初提供了`expr`命令来处理数学运算，但这个命令比较拉跨。bash中提供了方括号来进行数学运算

```bash
(base) root test # echo $var1
6
(base) root test # var2=$[$var1*10]
(base) root test # echo $var2
60
```

> 注意bash中的数学运算只支持整数。要计算浮点数，可以使用内建的`bc`命令

