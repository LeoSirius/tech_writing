参考：
https://www.toptal.com/python/pythons-wsgi-server-application-interface

WSGI就是Web Server Gateway Inteface，是web server和web app交互的一个标准。

## web app接口

app的接口必须是：

- 一个以`environ`和`start_response`作为参数的可调用对象
- 在返回body之前，必须调用`start_response`
- 必须返回包含body的可迭代对象

下面是app接口的两种实现形式

```py
def application(environ, start_response):
    body = b'Hello world!\n'
    status = '200 OK'
    headers = [('Content-type', 'text/plain')]
    start_response(status, headers)
    return [body]
```

```py
class Application:
    def __init__(self, environ, start_response):
        self.environ = environ
        self.start_response = start_response

    def __iter__(self):
        body = b'Hello world!\n'
        status = '200 OK'
        headers = [('Content-type', 'text/plain')]
        self.start_response(status, headers)
        yield body
```

### environ

environ是一个字典对象，把请求和server本身的一些信息传给web app。

### start_response

start_response参数：

- status: 标准的HTTP状态码，以空格分隔的字符串，如`'200 OK'`
- headers: list of tuples
- exc_info: 可选参数，用来处理错误

## wsgi server接口

下面是一个简单的wsgi server接口

```py
def write(chunk):
    '''Write data back to client'''
    ...

def send_status(status):
   '''Send HTTP status code'''
   ...

def send_headers(headers):
    '''Send HTTP headers'''
    ...

def start_response(status, headers):
    '''WSGI start_response callable'''
    send_status(status)
    send_headers(headers)
    return write         # 这里的return在application中没有使用，实际上已经deprecated

# Make request to application
response = application(environ, start_response)
try:
    for chunk in response:
        write(chunk)
finally:
    if hasattr(response, 'close'):
        response.close()
```
