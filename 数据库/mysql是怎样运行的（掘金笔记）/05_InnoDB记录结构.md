# InnoDB记录结构

## InnoDB页简介

InnoDB磁盘和内存交换数据的基本单位是页，一般一页大小是16kb

## InnoDB行格式

- 行格式：记录在磁盘上的存放方式。

InnoDB有四种行格式：

- Compact
- Redundant
- Dynamic
- Compressed

### Compact的行格式

![01_compact行格式](https://raw.githubusercontent.com/LeoSirius/tc/master/tech_writting/%E6%95%B0%E6%8D%AE%E5%BA%93/mysql%E6%98%AF%E6%80%8E%E6%A0%B7%E8%BF%90%E8%A1%8C%E7%9A%84%EF%BC%88%E6%8E%98%E9%87%91%E7%AC%94%E8%AE%B0%EF%BC%89/05_InnoDB%E8%AE%B0%E5%BD%95%E7%BB%93%E6%9E%84/01_compact%E8%A1%8C%E6%A0%BC%E5%BC%8F.png)

记录存储可以分成两部分：

- 记录的额外信息（包括：变长字段长度列表、NULL值列表、记录头信息）
- 记录的真实数据

我们创建一个测试表来说明情况

```sql
CREATE TABLE record_format_demo (
    c1 VARCHAR(10),
    c2 VARCHAR(10) NOT NULL,
    c3 CHAR(10),
    c4 VARCHAR(10)
) CHARSET=ascii ROW_FORMAT=COMPACT;
```

插入数据

```sql
INSERT INTO record_format_demo(c1, c2, c3, c4) VALUES
    ('aaaa', 'bbb', 'cc', 'd'),
    ('eeee', 'fff', NULL, NULL);
```

```sql
mysql> SELECT * FROM record_format_demo;
+------+-----+------+------+
| c1   | c2  | c3   | c4   |
+------+-----+------+------+
| aaaa | bbb | cc   | d    |
| eeee | fff | NULL | NULL |
+------+-----+------+------+
2 rows in set (0.00 sec)
```


#### 变长字段长度列表

变长字段有：`VARCHAR(M)`、`VARBINARY(M)`、各种`TEXT`类型，各种`BLOB`类型等

这些变长字段的`字节数`会`逆序`存放在每个记录的开头

我们的c1，c2和c4是变长类型

|列名|存储内容|内容长度（十进制表示）|内容长度（16进制表示）|
|-|-|-|-|
|c1|aaaa|4|0x04|
|c2|bbb|3|0x03|
|c4|d|1|0x01|

所以第一条记录的变长字段长度列表的内容就会是：`010304`

另外注意，值为NULL字段的长度是不会存储的。所以第二条记录的变长字段长度列表的内容就会是：`0304`

#### InnoDB的三个常用符号

- W：字符集表示一个字符最多需要用到的字节数。如utf8的W是3，gbk的W是2，ascii的W是1
- M：变长类型最多存储的字符个数，如`VARCHAR(M)`，就最多能存储M个字符
- L：字段实际存储的字符串占用的字节数


