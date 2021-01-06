# InnoDB数据页结构

页是InnoDB管理存储空间的基本单位。页有存放表头信息的页，存放insert buffer的页等。存放记录的页称为索引(INDEX)页，我们这里叫数据页。

## 数据页结构的快速浏览

数据页可以分成7个部分：

![01_数据页的7部分](https://raw.githubusercontent.com/LeoSirius/tc/master/tech_writting/%E6%95%B0%E6%8D%AE%E5%BA%93/mysql%E6%98%AF%E6%80%8E%E6%A0%B7%E8%BF%90%E8%A1%8C%E7%9A%84%EF%BC%88%E6%8E%98%E9%87%91%E7%AC%94%E8%AE%B0%EF%BC%89/06_InnoDB%E6%95%B0%E6%8D%AE%E9%A1%B5%E7%BB%93%E6%9E%84/01_%E6%95%B0%E6%8D%AE%E9%A1%B5%E7%9A%847%E9%83%A8%E5%88%86.webp)