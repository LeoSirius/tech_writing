# web安全问题总结

## SQL注入

如果后台直接把用户输入的信息用来查询数据库，则用户可能在输入的信息的注入一些不良的SQL操作。

## XSS攻击

全称`XSS是跨站脚本攻击(Cross Site Scripting)`。其实归根结底，XSS的攻击方式就是想办法“教唆”用户的浏览器去执行一些这个网页中原本不存在的前端代码。

举一个例子：A网站有留言板功能，一个用户的留言是`<script>alert(“hey!you are attacked”)</script>`

当其他用户看留言的时候，html就是下面这个。会弹出一个窗口。

```html
<html>
    <head>
       <title>留言板</title>
    </head>
<body>
<div id=”board” 
    <script>alert(“hey!you are attacked”)</script>
</div>
    </body>
</html>
```

除了上面这个简单的例子，常见的XSS常见的例子还包括：

- 窃取网页浏览中的cookie值。即通过嵌入script脚本获得当前页面的cookie值
- 劫持流量实现恶意跳转。如在网页中插入`<script>window.location.href="http://www.baidu.com";</script>`

> 除了script标签外，img标签和可能被插入来进行xss攻击

### 防御方法

#### 1.对要展示的文本进行转义

如下面一段html，直接用浏览器打开会弹出alert窗口。

```html
<html>
  <script>alert('1')</script>
</html>
```

下面是转义后的HTML，在页面上能看到`<script>alert(1)</script>`这段文本

```html
<html>
&lt;script&gt;alert(1)&lt;&#x2F;script>
</html>
```

#### 2. Content Security Policy （CSP）

本质也是白名单，通过设置白名单， 我们可以设置允许浏览器加载哪些外部资源。

开启CSP可以通过两种方式：

- 设置 HTTP Header 中的 Content-Security-Policy
- 设置 meta 标签的方式

## CSRF攻击

本质：攻击者盗用了你的身份，以你的名义发送恶意请求

要完成一次CSRF攻击，受害者必须依次完成两个步骤：

- 1.登录受信任网站A，并在本地生成Cookie。
- 2.在不登出A的情况下，访问危险网站B。

### 示例

银行网站A，它以GET请求来完成银行转账的操作，如：`http://www.mybank.com/Transfer.php?toBankId=11&money=1000`

危险网站B，它里面有一段HTML的代码如下

```html
<img src=http://www.mybank.com/Transfer.php?toBankId=11&money=1000>
```

先登录银行网站A，然后访问网站B，这时转账操作就会执行。

> 如果银行网站A用POST方法来转账，还是有被攻击的风险，只要B网站中的代码复杂一点，也可以发起POST请求

### 防御方法

#### 服务端防御

> 总体思想：在客户端页面上加伪随机数

比如django的csrf token。在`django.middleware.csrf.CsrfViewMiddleware`这个中间层来完成验证

