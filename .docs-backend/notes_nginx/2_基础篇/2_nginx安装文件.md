## rpm -ql nginx

这个命令可以显示rpm包安装了那些东西

## nginx安装文件详解

- nginx日志轮转，用于logrotate服务的日志切割
  - /etc/logrotate.d/nginx/
- nginx主配置文件
  - /etc/nginx
  - /etc/nginx/nginx.conf
  - /etc/nginx/conf.d/default.conf
- cgi相关配置
  - /etc/nginx/fastcig_params
  - /etc/nginx/uwsgi_params
  - /etc/nginx/scgi_params
- 编码转换的映射文件
  - /etc/nginx/koi-utf
  - /etc/nginx/koi-win
  - /etc/nginx/win-utf
- 设置http协议content-type与扩展名的对应关系
  - /etc/nginx/mime.types
- 配置守护进程管理器管理方式
  - /usr/lib/systemd/system/nginx.service
  - /etc/sysconfig/nginx
- nginx模块目录
  - /usr/lib64/nginx/modules
  - /etc/nginx/modules
- nginx命令
  - /usr/sbin/nginx
  - /usr/sbin/nginx-debug
- nginx手册和帮助文件
  - /usr/share/doc/...
  - /usr/share/man/...
- nginx缓存、日志
  - /var/cache/nginx
  - /var/log/nginx

## nginx安装编译参数

`nginx -V` 查看编译参数

`--prefix`和`--xxx-path`等为nginx的一些安装目录

`--http-xxxx-temp-path`会放在`/var/cache/nginx/`下面，是执行响应模块时的临时文件

`--user`和`--group`是nginx worker进程的用户和组

`--with-cc-opt=params`设置CFLAGS变量
`--with-ld-opt=params`链接系统库

