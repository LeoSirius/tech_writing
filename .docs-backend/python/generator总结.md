参考资料：
https://realpython.com/introduction-to-python-generators/

# generator总结

生成器函数返回一个lazy iterator。不同于不同的迭代器，惰性迭代器不会把自己的内容存在内存里

## 两个例子

### 读取大文件

```py
def csv_reader(file_name):
    file = open(file_name)           # open return lazy obj
    result = file.read().split("\n") # 但是这里会加载所有数据到内存，可能会报MemoryError
    return result

csv_gen = csv_reader("test_csv.csv")
row_count = 0

for row in csv_gen:
    row_count += 1

print(f"Row count is {row_count}")
```

csv_reader按照下面的写法就不会一下占满整个内存。这里csv_reader是生成器函数

```py
def csv_reader(file_name):
    for row in open(file_name, "r"):
        yield row
```

生成器表达式也返回一个generator。下面是用生成器表达式的方法来获取csv_reader

```py
csv_gen = (row for row in open(file_name))
```

### 生成一个无限序列

```py
def infinite_sequence():
    num = 0
    while True:
        yield num
        num += 1

for i in infinite_seq():
    print(i)                # 这里会无限打印下去
```

## 理解生成器

yield和return相同处：都会把值范围给caller。不同之处：yield不会结束函数，且会记住函数的状态。

下面的例子可以看出生成器对内存的优化

```py
import sys

nums1 = [i * 2 for i in range(10000)]
nums2 = (i * 2 for i in range(10000))

size1 = sys.getsizeof(nums1)   # 返回字节数
size2 = sys.getsizeof(nums2)

print('size1 = {}\nsize2 = {}'.format(size1, size2))

# size1 = 87632
# size2 = 128
```

但是如果list对象占的内存小于可用内存，则list会比生成器快很多。生成器其实可以变相的理解为以时间换空间的策略。

```py
import cProfile

cProfile.run('sum([i * 2 for i in range(10000)])')
cProfile.run('sum((i * 2 for i in range(10000)))')
```

## 理解yield语句

yield的作用是返回后面的值，并保存函数状态。下次调用next时，恢复状态并从上次yield的地方继续执行。

```py
>>> def multi_yield():
...     str1 = "111"
...     yield str1
...     str2 = "222"
...     yield str2
...
>>> obj = multi_yield()
>>> next(obj)
'111'
>>> next(obj)
'222'
>>> next(obj)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
StopIteration
```

## 高级生成器方法

### send

`gen_obj.send(value)` - 把value发回给yield语句

注意在send之后，控制权也会回到生成器函数里面

```py
>>> def gg():
...     send_in = yield '111'
...     print('send_in = {}'.format(send_in))
...     yield '222'
... 
>>> g_obj = gg()
>>> next(g_obj)
'111'
>>> g_obj.send(666)
send_in = 666
'222'
>>> next(g_obj)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
StopIteration
```

### throw

throw类似send，不过是把一个异常抛到生成器函数里

```py
def gen_items():
    for i, item in enumerate(["", "foo", "", "foo", "bad"]):
        if not item:
            continue
        try:
            yield item
        except Exception:
            raise Exception("error during index: %d" % i)
gen = item_generator()
for item in gen:
    if item == "bad":
        gen.throw(ValueError, "bad value")
```

输出

```
leo@192 slts (master) $ python3 tmp.py 
Traceback (most recent call last):
  File "tmp.py", line 6, in gen_items
    yield item
ValueError: bad value

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "tmp.py", line 13, in <module>
    gen.throw(ValueError, "bad value")
  File "tmp.py", line 8, in gen_items
    raise Exception("error during index: %d" % i)
Exception: error during index: 4
```

### close

close用来结束一个生成器，下面的例子只会输出0-10

```py
def gg():
    i = 0
    while True:
        yield i
        i += 1

g = gg()
for i in g:
    print(i)
    if i == 10:
        g.close()
```
