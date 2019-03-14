create database testdb;
use testdb;

show engine innodb status;

/*大约是查看字符集相关的信息，具体含义不明。*/
show character set;
show collation like 'utf8%';
show variables like 'character_set_server';


CREATE TABLE test (c1 float(10,2),c2 decimal(10,2));
insert into test values(131072.32, 131072.32);
select * from test;

/*
 *memory表存储在RAM里。当服务器关闭时，存储在MEMORY表里的数据丢失。
 *表的定义存在磁盘上的.frm文件中，所以表自身继续存在，服务器重启动
 *后它们是空的。
 */
CREATE TABLE newtest ENGINE = MEMORY select * from test;
ALTER TABLE newtest ENGINE = InnoDB;


drop database testdb;