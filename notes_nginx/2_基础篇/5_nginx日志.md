# nginx日志

## log_format

log_format只能配在http模块下面。可以用`$变量名`的形式把想要的变量记录在日志中

## nginx变量

- HTTP请求变量
  - arg_PARAMETER
  - http_HEADER        # request header
  - sent_http_HEADER   # response header

- nginx内置变量

参见: http://nginx.org/en/docs/http/ngx_http_core_module.html#variables

- 自定义变量