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
