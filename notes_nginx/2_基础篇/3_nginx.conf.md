## nginx默认配置语法

user: 工作进程用户
worker_process: 工作进程数，一般和cpu核数保持一致


events:
- worker_connections: 每个进程允许的最大链接数
- use: 工作进程数

```
http {
    server {
        listen      80;
        server_name localhost;

        location / {
            root   /usr/share/nginx/html;  # 默认路径
            index  index.html index.htm;   # 会在root的路径下找index.html, 没有找到则用index.htm
        }

        error_page 500 502 503 504  /50x.html;   意思是把前面几个状态码跳到后面的路经上
        location = /50x.html {
            root   /usr/share/nginx/html;
        }
    }

    server {
        ...
    }
}
```