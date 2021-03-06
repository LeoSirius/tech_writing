# TCP概述

TCP协议的基本特点：

- 面向连接：三次握手、四次挥手
- 可靠
- 基于字节流
- 全双工

## 可靠

IP协议无链接、不可靠：不保证顺序、不保证没有重复，甚至都不保证能接受到

TCP协议保障可靠的机制：

- 校验和：对每个包提供校验和。如果收到校验和有差错的报文，TCP丢到它，等待发送端重传。
- 序列号：解决顺序混乱和重复的问题
- 超时重传：发送数据后启动一个定时器。超过这个时间没有收到ACK确认，则重传。
- 流量控制、拥塞控制

## 面向字节流

流的含义是没有固定的报文边界。

假设你调用 2 次 write 函数往 socket 里依次写 500 字节、800 字节。write 函数只是把字节拷贝到内核缓冲区，最终会以多少条报文发送出去是不确定的。

- 情况 1：分为两条报文依次发出去 500 字节 和 800 字节数据
- 情况 2：两部分数据合并为一个长度为 1300 字节的报文，一次发送
- 情况 3：第一部分的 500 字节与第二部分的 500 字节合并为一个长度为 1000 字节的报文，第二部分剩下的 300 字节单独作为一个报文发送
- 情况 4：第一部分的 400 字节单独发送，剩下100字节与第二部分的 800 字节合并为一个 900 字节的包一起发送。
- 情况 N：还有更多可能的拆分组合

上面出现的情况取决于诸多因素：路径最大传输单元 MTU、发送窗口大小、拥塞窗口大小等。

## 全双工

在 TCP 中发送端和接收端可以是客户端/服务端，也可以是服务器/客户端，通信的双方在任意时刻既可以是接收数据也可以是发送数据，每个方向的数据流都独立管理序列号、滑动窗口大小、MSS 等信息。
