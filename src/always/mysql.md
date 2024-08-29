# Mysql

> http://t.csdnimg.cn/MVKa7

## 数据库

### 清屏

```mysql
system cls
```

### 登录数据库

```shell
mysql -u root -p
```

### 数据类型
INT：整数类型，常用于存储整数数据。
FLOAT：单精度浮点数类型，用于存储小数数据。
DOUBLE：双精度浮点数类型，用于存储大数数据。
DECIMAL：定点数类型，用于存储精确的小数数据，通常用于财务计算。
CHAR：固定长度字符串类型，最多255个字符。
VARCHAR：可变长度字符串类型，最多65535个字符。 

### 创建数据库

```mysql
create database my_database;
```

### 展示数据库

```mysql
show databases;
```

> 有分号

### 选择数据库

```mysql
use <database name>;
```

### 查看数据库默认编码

```mysql
SHOW CREATE DATABASE your_database_name;
```

### 设置数据库编码

```mysql
CREATE DATABASE dbname DEFAULT CHARSET utf8 COLLATE utf8_general_ci;
```

## 数据表

* 都要有`ALTER TABLE <table name>`

### 展示表

```mysql
show tables;
```

### 查询表结构

```mysql
desc student;
```

### 创建数据表

```mysql
create table student(id int,name char(10),age int,sex char(5));
```

### 重命名数据表名

```mysql
ALTER TABLE user10 RENAME TO user11;
```

### 查询数据表编码

```mysql
SHOW CREATE TABLE your_table_name;
```

### 设置数据表编码

```mysql
CREATE TABLE `students` (
    `id` CHAR(30) NOT NULL,
    `name` CHAR(30) NOT NULL,
    `major` CHAR(30) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
```

> 注意是反引号`而不是单引号‘

### 修改数据表的名字

```mysql
ALTER TABLE students RENAME TABLE <table name before> TO <table name after>;
```

### 查询表结构

```mysql
desc studens;
```

### 修改数据表的结构

```mysql
RENAME TABLE users TO students;

ALTER TABLE students
DROP COLUMN age,
CHANGE name student_name VARCHAR(100),
ADD COLUMN student_id INT NOT NULL,
ADD COLUMN major VARCHAR(100) NOT NULL;
```

### 删除表

```mysql
DROP TABLE students;
```

## 数据项

### 插入数据项

```mysql
insert into student(name,id,major) value ("张三","001","计算机");
```

或

```mysql
insert into student value ("张三","001","计算机");
```

### 删除数据项

```mysql
delete from students where name="张三";
```

### 修改数据项

```mysql
UPDATE students
SET student_id = 新的学号
WHERE id = 2;
```

### 展示所有数据

```mysql
select * from students;
```

## 联合查询

### join

```mysql
mysql> SELECT class.class_id,class.name,class.description
-> from class
-> JOIN class_teacher ON class.class_id=class_teacher.class_id
-> WHERE class_teacher.teacher_id=113210;
```

效果

```shell
+----------+-------+-------------+
| class_id | name | description |
+----------+-------+-------------+
| 10293 | 英语I | 星期二1~2节 |
+----------+-------+-------------+
1 row in set (0.00 sec)
```

