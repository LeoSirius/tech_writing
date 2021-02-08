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

## http协议的特点

- 是C/S模式，即是一种请求/响应模型
- 简单快速：请求方只需要传送请求方法和路径。
- 灵活：允许传输任意类型的数据对象。传输的类型由Content-Type加以标记
- 无链接：限制每次连接只处理一个请求。
- 无状态：指协议对于事务处理没有记忆

## URL和URI的区别

- url：Uniform Resource Locator，统一资源定位符
- uri：Uniform Resource Identifier，统一资源标识符

url是uri的子集，uri还包括了urn

uri的关键是标识：

- 用location标识就是url
- 用name标识就是urn

## http报文的组成

请求报文：

- 请求头：方法、URL、协议/版本
- 头部
- 正文

响应报文：

- 响应行
- 头部
- 正文

## 请求方法

HEAD方法类似GET，不过响应报文只有头部，没有正文

## 响应状态码

### 状态码的类型

- 1xx：信息型，服务器收到请求，需要请求者继续操作。
- 2XX- 成功型，请求成功收到，理解并处理。
- 3XX - 重定向，需要进一步的操作以完成请求。
- 4XX - 客户端错误，请求包含语法错误或无法完成请求。
- 5XX - 服务器错误，服务器在处理请求的过程中发生了错误。

### 301和302

从含义上来讲，区别如下

- 301表示：资源（网页等）被永久转移到其它URL
- 302表示：临时跳转

## 什么是https

### http的缺陷

- 请求信息明文传输，容易被窃听截取。
- 数据的完整性未校验，容易被篡改
- 没有验证对方身份，存在冒充危险

HTTPS（HyperText Transfer Protocol over Secure Socket Layer）：一般理解为HTTP+SSL/TLS，通过 SSL证书来验证服务器的身份，并为浏览器和服务器之间的通信进行加密。

### 什么是ssl

SSL（Secure Socket Layer，安全套接字层）：1994年为 Netscape 所研发，SSL 协议位于 TCP/IP 协议与各种应用层协议之间，为数据通讯提供安全支持。

TLS（Transport Layer Security，传输层安全）：其前身是 SSL。SSL3.0和TLS1.0由于存在安全漏洞，已经很少被使用到。TLS 1.3 改动会比较大，目前还在草案阶段，目前使用最广泛的是TLS 1.1、TLS 1.2。

### HTTPS的缺点

- HTTPS协议多次握手，导致页面的加载时间延长近50%；
- HTTPS连接缓存不如HTTP高效，会增加数据开销和功耗；
- 申请SSL证书需要钱，功能越强大的证书费用越高。
- SSL涉及到的安全算法会消耗 CPU 资源，对服务器资源消耗较大。


## https传输数据的流程

![02_https流程](https://raw.githubusercontent.com/LeoSirius/tc/master/tech_writting/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/http%E5%8D%8F%E8%AE%AE%E6%80%BB%E7%BB%93/02_https%E6%B5%81%E7%A8%8B.jpg)

1. 客户端发起https请求
2. 服务端的配置
  主要就是证书。证书其实就是一对公钥和私钥。公钥可以理解为锁头，私钥可以理解为这把锁的钥匙。别人可以用这个锁把重要的东西锁起来，然后发给你，因为只有你一个人有这把钥匙。
3. 传送证书
  证书其实就是公钥，只是包含了很多信息，如证书的颁发机构，过期时间等等。
4. 客户端解析证书
  首先会验证公钥是否有效，比如颁发机构，过期时间等等，如果发现异常，则会弹出一个警告框，提示证书存在问题。
  如果证书没有问题，那么就生成一个随机值，然后用证书对该随机值进行加密，就好像上面说的，把随机值用锁头锁起来，这样除非有钥匙，不然看不到被锁住的内容。
5. 传送加密信息
  这部分传送的是用证书加密后的随机值，目的就是让服务端得到这个随机值，以后客户端和服务端的通信就可以通过这个随机值来进行加密解密了。
6. 服务段解密信息
  服务端用私钥解密后，得到了客户端传过来的随机值(私钥)，然后把内容通过该值进行对称加密，所谓对称加密就是，将信息和私钥通过某种算法混合在一起，这样除非知道私钥，不然无法获取内容，而正好客户端和服务端都知道这个私钥
7. 传输加密后的信息
  这部分信息是服务段用client key加密后的信息，可以在客户端被还原。
8. 客户端解密信息
  客户端用之前生成的client key解密服务段传过来的信息，于是获取了解密后的内容

![03_https流程2](https://raw.githubusercontent.com/LeoSirius/tc/master/tech_writting/%E8%AE%A1%E7%AE%97%E6%9C%BA%E7%BD%91%E7%BB%9C/http%E5%8D%8F%E8%AE%AE%E6%80%BB%E7%BB%93/03_https%E6%B5%81%E7%A8%8B2.jpg)

