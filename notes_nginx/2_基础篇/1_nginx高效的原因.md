

nginx高效的原因：

1. 采用IO多路复用epoll模型
2. CPU亲和
3. sendfile


## epoll模型的IO多路复用

IO多路复用可以在一个线程里处理多个IO流。避免了多进程或多线程的开销。

nginx使用的是epoll模型，httpd使用的是select模型

epoll相对于select的优势：

1. 解决了SELECT模型对于文件句柄FD打开的限制
2. 采用了callback优化了效率

## CPU亲和（affinity）

现在很多服务器有多个cpu。
CPU亲和把CPU核心和Nginx工作进程绑定，把每个worker进行固定在一个cpu上执行，减少切换cpu带来的损耗。

## sendfile

加速静态文件。直接在内核空间把文件传给socket。

