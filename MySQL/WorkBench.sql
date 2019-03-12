-- mysql用户管理程序
show databases;
-- 创建用户zhangsan，密码为zhangsan
create user zhangsan identified by 'zhangsan';
select * from mysql.user;
-- 删除用户zhangsan,一般后接@localhost，这里是%
DROP USER zhangsan@'%';
select * from mysql.user;
