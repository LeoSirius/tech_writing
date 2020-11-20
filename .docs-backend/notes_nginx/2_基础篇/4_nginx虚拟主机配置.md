# 4 nginx虚拟主机配置

- 基于主机多IP的方式
- 基于端口的配置方式
- 基于多host名称方式（多域名方式）

## 基于主机多IP的方式

重点是实现主机本身多个IP的配置，这又有两种方式：

- 多网卡多IP
- 单网卡多IP（这里使用这种方式。注意阿里云不支持，最好用内网虚拟机）

IP地址不能再局域网中被使用。可以先用PING测一下

```bash
[root@localhost ~]# ip a add 192.168.0.110/24 dev ens33
[root@localhost ~]# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: ens33: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether 00:0c:29:8b:14:c1 brd ff:ff:ff:ff:ff:ff
    inet 192.168.0.105/24 brd 192.168.0.255 scope global noprefixroute dynamic ens33
       valid_lft 6348sec preferred_lft 6348sec
    inet 192.168.0.110/24 scope global secondary ens33
       valid_lft forever preferred_lft forever
    inet6 fe80::b030:ff4b:1f12:8fcb/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever
```

vserver1.conf和vserver2.conf的listen和路径改成不同的，然后再在那两个不同的目录下放两个不同的文件，就可以看到区别了

```
# vserver1.conf
listen 192.168.0.105:80
location / {
    root /opt/app/code1;
    index index.html index.htm;
}
...

# vserver2.conf
listen 192.168.0.110:80
location / {
    root /opt/app/code2;
    index index.html index.htm;
}
```

## 基于端口的配置方式

基于端口的方式也是修改listen，不过把端口号改成不同即可

## 基于多host方式

利用HTTP协议

在客户端可以改/etc/hosts文件来模拟DNS。把多个域名解析到同一个IP地址，如

```
192.168.0.105 1.imoocc.com
192.168.0.105 2.imoocc.com
```

```
# vserver1.conf
listen 80
server_name 1.imoocc.com
location / {
    root /opt/app/code1;
    index index.html index.htm;
}
...

# vserver2.conf
listen 80
server_name 1.imoocc.com
location / {
    root /opt/app/code2;
    index index.html index.htm;
}
```
