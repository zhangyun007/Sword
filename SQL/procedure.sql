# 存储过程示例

status
use test

show engines\G;
show variables like 'datadir';
Show variables like 'have%';

# 存储过程被source后，存储在服务器端，退出mysql连接，重新mysql, 
# 该过程依然还在，直接可以调用。

delimiter //

drop procedure if exists MyProc;
create procedure MyProc()
begin
select version();
end//

delimiter ;

call MyProc();


delimiter //

drop procedure if exists math;
create procedure math (in a int, in b int)
begin
    set @var1 = 1;
    set @var2 = 2;
    select @sum:=(a + b) as sum, @dif:=(a - b) as dif;
end//

delimiter ;

call math(3, 4);
select @var1;
select @var2;

delimiter //

drop procedure if exists TestAdd;
create procedure TestAdd(in a int, in b int) 
begin 
	declare c int default 10;  
    	set c = a + b;
    	select c as c;
end//

delimiter ;

call TestAdd(2, 4);


delimiter //

create procedure Test (name varchar(120)) 
begin 
	set @sql = name; 
	prepare s1 from @sql; 
	execute s1; 
	deallocate prepare s1; 
end//

delimiter ;

call Test("Select count(*) from pet;");


SHOW CREATE PROCEDURE MyProc;
SHOW PROCEDURE STATUS like 'MyProc';
