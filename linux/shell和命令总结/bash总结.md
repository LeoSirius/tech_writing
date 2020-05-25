# bash总结

## 括号

- 圆括号(Parentheses)
  一般在命令替换的时候使用
- 双圆括号
  在比较过程中使用高级数学表达式
- 方括号(Brackets)
  用于逻辑分支中的条件判断
- 双方括号
  支持字符串比较、正则匹配
- 花括号(Braces)
  用来界定变量

### Parentheses

```bash
#!/bin/bash

today=$(date +%Y%m%d)
touch log.$today
```

### Double Parentheses

```bash
#!/bin/bash

val1=10
if (( $val1 ** 2 > 90 )); then
    ((val2 = $val1 ** 2))
    echo "The square of $val1 is $val2"
fi
```

```bash
leo@ubuntu:~/sh_test$ ./test.sh
The square of 10 is 100
```

### Brackets

### Double Brackets

```bash
#!/bin/bash
# using patter matching
#
if [[ $USER == l* ]]; then
    echo "Hello $USER"
else
    echo "Sorry, I do not know you"
fi
```

### Braces

```
root@ubuntu18:~/monitor_man# VARIABLE=abcdef
root@ubuntu18:~/monitor_man# echo Variable: $VARIABLE
Variable: abcdef
root@ubuntu18:~/monitor_man# echo Variable: $VARIABLE123456
Variable:
root@ubuntu18:~/monitor_man# echo Variable: ${VARIABLE}123456
Variable: abcdef123456
```

## 重定向

重定向的三种形式，都是把stdout和stderr重定向到word

- `&>word`
- `>&word`
- `>word 2>&1`

`some_command && a || b`表示如果some_command正确执行，则执行a，否则执行b

下面的例子根据ping有没有错，分别执行不同的输出。并把ping的stdout和stderr重定向到/dev/null

```bash
ping -c 2 www.baicu.com &>/dev/null && echo "Internet:Connected" || echo "Internet:Disconnected"
```
