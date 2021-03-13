# Redis基础数据结构

> Redis全称 `Remote Dictionary Service`

## Redis基础数据结构

5种数据结构

- string
- list
- set
- hash
- zset（有序集）

Redis 所有的数据结构都是以唯一的 key 字符串作为名称，然后通过这个唯一 key 值来获取相应的 value 数据。不同类型的数据结构的差异就在于 value 的结构不一样。

## string

Redis 的字符串是动态字符串，是可以修改的字符串。采用预分配冗余空间的方式来减少内存的频繁分配。

这里先介绍一些简单的操作

### 单独设置和获取数据

```r
127.0.0.1:6379> set name leo
OK
127.0.0.1:6379> get name
"leo"
```

### 批量设置和获取数据

```r
127.0.0.1:6379> mset name leo age 18
OK
127.0.0.1:6379> mget name age
1) "leo"
2) "18"
```

### 设置过期时间

```r
127.0.0.1:6379> setex name 5 leo
OK
# after 5s
127.0.0.1:6379> get name
(nil)
```

### 计数

```r
127.0.0.1:6379> set age 18
OK
127.0.0.1:6379> incr age
(integer) 19
127.0.0.1:6379> incrby age 100
(integer) 119
127.0.0.1:6379> get age
"119"
```

