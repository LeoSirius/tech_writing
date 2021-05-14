# 1 UNIX 基础知识

## pre knowledge: apue 库的使用

apue的库下载好后（注意在make前，确保systype.sh是可执行文件。）

```
sudo apt install libbsd-dev
cd apue.3e
# make
......

sudo cp ./include/apue.h /usr/include/
sudo cp ./lib/libapue.a /usr/local/lib/
```

使用

```c
gcc filename.c -lapue
```

## 1.3 登录

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


