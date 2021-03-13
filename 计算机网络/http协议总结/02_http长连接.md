# http长连接

## 什么是长连接

http协议采用“请求-应答”模式，当使用普通模式，即非Keep-Alive模式时，每个请求/应答，客户端和服务器都要新建一个连接，完成之后立即断开连接；当使用Keep-Alive模式时，Keep-Alive功能使客户端到服务器端的连接持续有效，当出现对服务器的后继请求时，Keep-Alive功能避免了建立或者重新建立连接。

http1.0中默认是关闭的，需要在http头加入”Connection: Keep-Alive”，才能启用Keep-Alive；
http 1.1中默认启用Keep-Alive，如果加入”Connection: close “才关闭。

目前大部分浏览器都是用http1.1协议，也就是说默认都会发起Keep-Alive的连接请求了，所以是否能完成一个完整的Keep- Alive连接就看服务器设置情况。下图是普通模式和长连接模式的请求对比

![01_非常连接和长连接](https://raw.githubusercontent.com/LeoSirius/tc/master/tech_writting/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/http%E5%8D%8F%E8%AE%AE%E6%80%BB%E7%BB%93/02_http%E9%95%BF%E8%BF%9E%E6%8E%A5/01_%E9%9D%9E%E5%B8%B8%E8%BF%9E%E6%8E%A5%E5%92%8C%E9%95%BF%E8%BF%9E%E6%8E%A5.png)

## 长连接的缺点

虽然为客户保留打开的连 接有一定的好处，但它同样影响了性能，因为在处理暂停期间，本来可以释放的资源仍旧被占用。

下面是限制长连接的一个例子

```
HTTP/1.1 200 OK
Connection: Keep-Alive
Content-Encoding: gzip
Content-Type: text/html; charset=utf-8
Date: Thu, 11 Aug 2016 15:23:13 GMT
Keep-Alive: timeout=5, max=1000
Last-Modified: Mon, 25 Jul 2016 04:32:39 GMT
Server: Apache

(body)
```

- timeout：过期时间5秒
- max：最多100次请求，强制断掉连接。就是在timeout时间内又有新的连接过来，同时max会自动减1，直到为0，强制断掉。
