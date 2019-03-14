show databases;

/*
 *
 
创建用户 

CREATE USER  'user_name'@'host'  IDENTIFIED BY  'password'；

user_name：	要创建用户的名字。
host：		表示要这个新创建的用户允许从哪台机登陆，如果只允许从本机登陆，则填‘localhost’，如果允许从远程登陆，则填 ‘%’。
password：	新创建用户的登陆数据库密码，如果没密码可以不写。

*
*/

create user zhangsan identified by 'zhangsan';
select * from mysql.user;
DROP USER zhangsan@'%';
select * from mysql.user;
