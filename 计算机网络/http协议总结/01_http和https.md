# http和https

## http是什么

- http是超文本传输协议的缩写，英文是`Hyper Text Transfer Protocol`。
- 设计HTTP最初的目的是为了提供一种发布和接收HTML页面的方法。
- 目前广泛使用的是HTTP/1.1版本。

## http访问www.baidu.com

流程如下

1. 现用dns把www.baidu.com这个域名解析为服务器的ip
2. 发起tcp请求，3次握手建立连接
3. 客户端向服务器发起http请求
4. 服务器向客户端发起http响应

![01_访问百度的流程](https://raw.githubusercontent.com/LeoSirius/tc/master/tech_writting/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/http%E5%8D%8F%E8%AE%AE%E6%80%BB%E7%BB%93/01_%E8%AE%BF%E9%97%AE%E7%99%BE%E5%BA%A6%E7%9A%84%E6%B5%81%E7%A8%8B.jpg)
