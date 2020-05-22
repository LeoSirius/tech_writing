# nginx的访问控制

- 基于IP的访问控制 - http_access_module
- 基于用户的信任登录 - http_auth_basic_module

访问控制在http，server，location下做，会分别影响对应的作用范围。

## http_access_module

按照下面配置后，114.249.220.163访问/admin.html返回403，其他情况都能正常访问。

```
server {

    listen 80;
    server_name localhost;


    location / {
        root /opt/app/code;
    }

    location ~ ^/admin.html {   # ~表示后面是模式匹配
        deny 114.249.220.163;
        allow all;
        root /opt/app/code;
    }
}
```

注意这里deny和allow的顺序很重要。如果是下面则表示除了114.249.220.0/24外，其他都不能访问

```
    location ~ ^/admin.html {   # ~表示后面是模式匹配
        allow 114.249.220.0/24;
        deny all;
        root /opt/app/code;
    }
```

## 代理IP绕过的问题

- remote_addr：直接和server建立连接的IP addr
- x_forwarded_for：会记录下整个过程。

格式：
`x_forward_for = Client IP, Proxy(1) IP, Proxy(2) IP...`

```
         remote_addr = IP1              remote_addr = IP2
IP1  ->  IP2                  ->        Nginx


         x_forwarded_for = IP1          x_forwarded_for = IP1, IP2
IP1  ->  IP2                  ->        Nginx
```
