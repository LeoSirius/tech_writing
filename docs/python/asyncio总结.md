# asyncio总结

> 参考资料：https://realpython.com/async-io-python/

## 基本概念

首先明确三个概念：

- Asynchronous IO (async IO): 语言中性的编程范式。
- async/await: python中用来定义协程的两个新的关键字
- asyncio: python管理协程的一个包

python中，协程是一种特殊的生成器函数。协程是一个函数，是能暂停的函数，是能在暂停时把控制权交给其他协程的函数。

```py
#!/usr/bin/env python3
# 这里例子执行了三个函数，只用了一秒多。

import asyncio

async def count():
    print("One")
    await asyncio.sleep(1)
    print("Two")

async def main():
    await asyncio.gather(count(), count(), count())

if __name__ == "__main__":
    import time
    s = time.perf_counter()
    asyncio.run(main())                # 注意main是function对象，main()才是协程对象
    elapsed = time.perf_counter() - s
    print(f"{__file__} executed in {elapsed:0.2f} seconds.")
```

## 关键字 async/await 和 asyncio pkg

```
async def g():
    # Pause here and come back to g() when f() is ready
    r = await f()
    return r
```

### 语法规则

`async def`定义的函数时协程。其中可以用`await` `yield` `return`。也可以都没有，如`aysnc def foo(): pass`也是合法的。

- async def + yield 是异步生成器函数，用在async for中。
- async def + await/return 是常规的协程
- async def + yield from 是语法错误

在函数外用yield是语法错误，在函数外用await也是语法错误。

另外使用装饰器修饰的协程是老式的，是基于生成器函数的协程。下面两种协程使用上是等价的。基于生成器的协程最好不要使用，在未来的版本中会被移出。引入async/await就是为了把协程和生成器函数独立出来，使得语法更简洁，更不易混淆。

```py
import asyncio

@asyncio.coroutine
def py34_coro():
    """Generator-based coroutine, older syntax"""
    yield from stuff()

async def py35_coro():
    """Native coroutine, modern syntax"""
    await stuff()
```

## 启动协程的三种方法

- asyncio.run()
- 
