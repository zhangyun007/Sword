create database testdb;
use testdb;

show engines\G;
show engine innodb status;

show variables like '%storage_engine%';
show variables like 'datadir';
Show variables like 'have%';

/*大约是查看字符集相关的信息，具体含义不明。*/
show character set;
show collation like 'utf8%';
show variables like 'character_set_server';


/* MySQL基本类型*/

/*
1. 整数类型：

类型 		存储 		正负数范围 				全正数范围 		全正长度 	备注
tinyint 	1字节 		-128~127 				0~255 			3
smallint 	2字节 		-32768~32767 			0~65535 		5
mediumint 	3字节 		-8388608~8388607 		0~16777215 		8 			可用于邮编号
int 		4字节 		-2147483648~2147483647 	0~4294967295	10 			可用拼接1的方式存手机号
bigint 		8个字节 	±9223372036854775808-1 	18------- 		20位 		可存储手机号

2.数值型（DEMICAL,NUMERIC）

"Decimal则以字符串的形式保存数值"

DEMICAL,NUMERIC都是用来存储精确的数值，一般金额使用这个参数，DEMICAL是基本类型，NUMERIC按DEMICAL进行计算。DEMICAL按照二进制的格式存储
例如：我们公司使用DEMICAL(18,4)来存储金额数值
小数位为4位，整数位位18-4=14位
DEMICAL(0),无法存数据，DEMICAL(X)不指定小数位数时，默认为0，理论上DEMICAL最长可以容纳65位数字

3.位值型（bit）

用于存储位值，最长可达64位，mysql命令行客户端无法查看位值数据。导出时也可能显示乱码，不要担心。
应用：bit(1) 用于判断是否
bit(32) 用于存储IP地址，只占4字节，应该是最省空间的选择
例如：bit(6) 存入 b'101'，其实是按照00101来存储，不足的会在左边补零，读取出来视不同客户端也会补零

4.浮点类型
float与double
其小数点位数和总位数的关系与DEMICAL相似。浮点类型的数值是不精确的，需要精确计算的数值不建议设置为浮点型
例如：float(7,4) 存入9999.00009,小数位超出1位，其他的类型都

*/
CREATE TABLE test (c1 float(10,2),c2 decimal(10,2));
insert into test values(131072.32, 131072.32);
select * from test;

drop database testdb;