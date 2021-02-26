# linux环境变量

## 全局环境变量与局部环境变量

- 全局环境变量：对定义其的父进程所创建的子进程中可用。
- 局部环境变量：只能在定义其的进程中使用。

系统环境变量一般全用大写。可以用`env`或`printenv`列出全局变量。

如果看查看其值，可以用

```bash
$ printenv HONE
```

或者

```bash
$ echo $HOME
```

linux中没有专门查看局部变量的命令。`set`命令会列出所有变量：全局变量、局部变量、用户自定义变量

删除变量用命令`unset variable_name`

## 用户自定义变量

- 变量类型：数值、字符串
- 变量名与值和它们之间的等号中间没有空格
- `export variable_name`后，变量便成为了全局变量
- 修改、删除子进程中的全局变量不会影响父进程中的那个变量

```sh
$ name='Leo'
$ export name
$ echo $name
Leo
$ bash                  # 创建子shell
$ echo $name
Leo
$ name='Siria'          # 在子shell中改变量的值
$ echo $name
Siria
$ exit
exit
$ echo $name            # 父shell中变量的值不变
Leo
```

## `PATH`环境变量

这个环境变量的路径就是输入外部命令时，shell会去搜索这个程序的路径。A

添加新路径的方法:

```bash
$ PATH=$PATH:/root/new_folder/new_bin
```

## 数组环境变量


