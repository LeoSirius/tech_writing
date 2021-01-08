GIL是Python解释层面的锁，解决解释器中多个线程的竞争资源问题

GIL对python程序的影响

- Python中同一时刻有且只有一个线程会执行
- Python中的多个线程由于GIL锁的存在无法利用多核CPU
- Python中的多线程不适合计算机密集型的程序
- 如果程序需要大量的计算，利用多核CPU资源，可以使用多进程来解决