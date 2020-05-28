# nginx的请求限制

- 连接频率限制：limit_conn_module（TCP层面的连接）
- 请求频率限制：limit_req_module（HTTP层面的请求）

## ab 测压介绍

下面表示一共请求50次，20个并发

```
ab -n 50 -c 20 http://39.106.229.224/
```

## 实例

```
http {
    limit_conn_zone &binary_remote_addr zone=conn_zone:1m;          # 1mb的空间来存放
    limit_req_zone &binary_remote_addr zone=req_zone:1m rate=1r/s;  # rate单位是每秒一个

    server {

        limit_req zone=req_zone;                    # 只会有一个请求成功
        limit_req zone=req_zone burst=3;            # 请求速率达到上限后，有3个放到下一秒执行。可以看到最终的成功请求的4个
        limit_req zone=req_zone burst=3 nodely;     # 请求速率达到上限后，可以看到最终的成功请求的4个。其中3个delay了一秒。客户端这边可以明显的感觉到

        limit_conn conn_zone 1;   # 限制一个ip只能有一个连接
    }
}
```