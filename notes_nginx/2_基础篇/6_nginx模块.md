# nginx模块

编译参数中`--with`开头的就是编译时加入的模块

##  --with-http_stub_status_module

文档http://nginx.org/en/docs/http/ngx_http_stub_status_module.html

处理nginx监控连接状态。

在server中加一个location，如下。然后访问url/mystatus就可以看到信息

```
location /mystatus {
    stub_status
}
```

## --with-http_random_index_module

在主目录下随机选择一个文件作为主页。注意不会选择.开头的隐藏文件

## --with-http_sub_module

替换http response指定的行

下面把111替换成aaa。sub_filter_once默认是on，即只换一行
```
        location / {
            root /opt/app/code;
            sub_filter '111' 'aaa';
            sub_filter_once off;
        }
```
