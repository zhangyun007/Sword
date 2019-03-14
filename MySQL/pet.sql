create database testdb;
use testdb;

CREATE TABLE pet (
	name VARCHAR(20), 
	owner VARCHAR(20), 
	species VARCHAR(20), 
	sex CHAR(1), 
	birth DATE, 
	death DATE 
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ;

SHOW TABLES;

/* warnings; */
/* 8.0不允许怎么办？*/
LOAD DATA LOCAL INFILE './pet' INTO TABLE pet;
show create table pet;

ALTER TABLE pet ROW_FORMAT = DEFAULT;
 show table status like 'pet'\G;
ALTER TABLE pet ROW_FORMAT = compact;
 show table status like 'pet'\G;
ALTER TABLE pet ROW_FORMAT = dynamic;
 show table status like 'pet'\G;

desc pet;
show columns from  pet;

SET @counter=0;
select @counter:=@counter+1 AS Rank, name, owner from pet order by name;
select @counter;


/* 事务 */
start transaction;
update pet set sex="m" where name = "Claws";
commit and chain; 
update pet set sex="f" where name = "Claws";
commit;


SHOW GLOBAL STATUS LIKE 'Created_tmp%tables';

SHOW GLOBAL VARIABLES LIKE '%table_size';
SHOW GLOBAL VARIABLES LIKE 'tmpdir';
show variables like 'AUTOCOMMIT';
SHOW VARIABLES LIKE 'have_query_cache';


/* 复制表 */
drop table if exists backup;
create table backup like pet;
insert backup select * from pet;
select * from backup;


/* 创建视图 */
drop view IF EXISTS TestView;
create view TestView as select name, owner from pet;
show create view TestView;
select * from TestView;


/* 创建索引*/
create index TestIndex on pet(name);
show index from pet;


drop database testdb;
