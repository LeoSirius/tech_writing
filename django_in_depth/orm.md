# ORM

- Model
- Manager
- QuerySet
- Query
- SQLCompiler
- Database backend

## Database Backend

django.db.backends.base - 连接具体数据库的基类，形如BaseXXXX

django原生支持四种数据库的链接：（如果要使用其他数据库，需要使用第三方数据库驱动）
这四种数据库继承base中的基类

- django.db.backends.mysql
- django.db.backends.sqlite3
- django.db.backends.oracle
- django.db.backends.postgresql

### db.backend中的类

- BaseDatabaseWrapper:
    - Represent a database connection.
- BaseDatabaseOperations:
    - Encapsulate backend-specific differences, such as the way a backend performs ordering or calculates the ID of a recently-inserted row.
- BaseDatabaseFeatures:
    - as name
- BaseDatabaseCreation
- BaseDatabaseIntrospection
    - map DB's columns to Django's columns。inspectdb命令使用这个类。
- BaseDatabaseSchemaEditor
    - This class and its subclasses are responsible for emitting schema-changing statements to the databases - model creation/removal/alteration, field renaming, index fiddling, and so on. 即数据库变动的语句
- BaseDatabaseClient
    - dbshell命令会使用这个类

### SQLCompiler

db.models.sql.compiler

SQLCompiler生成SQL语句。Turns Django Query instance into sql.

- SQLInsertCompiler生成Insert语句
- SQLDeleteCompiler生成Delete语句，etc
