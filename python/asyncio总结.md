参考文献：
https://realpython.com/async-io-python/

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
    asyncio.run(main())
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
