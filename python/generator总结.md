参考资料：
https://realpython.com/introduction-to-python-generators/

# generator总结

生成器函数返回一个lazy iterator。不同于不同的迭代器，惰性迭代器不会把自己的内容存在内存里

## 

```py
def csv_reader(file_name):
    file = open(file_name)           # open return lazy obj
    result = file.read().split("\n") # 这里会加载所有数据到内存，可能会报MemoryError
    return result

csv_gen = csv_reader("test_csv.csv")
row_count = 0

for row in csv_gen:
    row_count += 1

print(f"Row count is {row_count}")
```
