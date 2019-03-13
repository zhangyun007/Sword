create database test;
use test;

show engine innodb status;

CREATE TABLE pet (
	name VARCHAR(20), 
	owner VARCHAR(20), 
	species VARCHAR(20), 
	sex CHAR(1), 
	birth DATE, 
	death DATE 
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ;

SHOW TABLES;

warnings 
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

start transaction;
update pet set sex="m" where name = "Claws";
/* 提交并开始一个新事务 */
commit and chain; 
update pet set sex="f" where name = "Claws";
commit;

SHOW GLOBAL STATUS LIKE 'Created_tmp%tables';

SHOW GLOBAL VARIABLES LIKE '%table_size';
SHOW GLOBAL VARIABLES LIKE 'tmpdir';
show variables like 'AUTOCOMMIT';
SHOW VARIABLES LIKE 'have_query_cache';

drop view IF EXISTS TestView;
create view TestView as select name, owner from pet;
show create view TestView;
select * from TestView;

drop table if exists apet;
create table apet like pet;
insert apet select * from pet;
select * from apet;

create index TestIndex on pet(name);
show index from pet;

drop table if exists employee;
drop table if exists telephone;

CREATE TABLE `employee` (
  `id` int NOT NULL AUTO_INCREMENT,
  `first_name` varchar(100) NOT NULL,
  `last_name` varchar(100) NOT NULL,
  `job_title` varchar(100) DEFAULT NULL,
  `salary` double DEFAULT NULL,
  `notes` text,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `employee` (`first_name`, `last_name`, `job_title`, `salary`) VALUES
                       ('Robin', 'Jackman', 'Software Engineer', 5500),
                       ('Taylor', 'Edward', 'Software Architect', 7200),
                       ('Vivian', 'Dickens', 'Database Administrator', 6000),
                       ('Harry', 'Clifford', 'Database Administrator', 6800),
                       ('Eliza', 'Clifford', 'Software Engineer', 4750),
                       ('Nancy', 'Newman', 'Software Engineer', 5100),
                       ('Melinda', 'Clifford', 'Project Manager', 8500),
                       ('Harley', 'Gilbert', 'Software Architect', 8000);

CREATE TABLE `telephone` (
  `id` int NOT NULL AUTO_INCREMENT,
  `employee_id` int DEFAULT NULL,
  `type` varchar(20) NOT NULL,
  `no` varchar(50) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO `telephone` (`employee_id`, `type`, `no`) VALUES
                        (1, 'mobile',   '245-249697'),
                        (2, 'mobile',   '270-235969'),
                        (2, 'land',     '325-888885'),
                        (3, 'mobile',   '270-684972'),
                        (4, 'mobile',   '245-782365'),                     
                        (4, 'land',     '325-888886'),
                        (5, 'mobile',   '245-537891'),
                        (6, 'mobile',   '270-359457'),
                        (7, 'mobile',   '245-436589'),                                                      
                        (7, 'land',     '325-888887'),
                        (8, 'mobile',   '245-279164'),                                                      
                        (8, 'land',     '325-888888');

begin;

INSERT INTO `employee` (`id`, `first_name`, `last_name`,
`job_title`, `salary`) VALUES (9, 'Grace', 'Williams',
'Softwaree Engineer', 5000);

INSERT INTO `telephone` (`id`, `employee_id`, `type`,
`no`) VALUES (13, 9, 'mobile', '270-598712');

Commit;

select * from employee;
select * from telephone;


/*
 *memory表存储在RAM里。当服务器关闭时， 所有存储在MEMORY表里的数据被丢失。
 *因为表的定义被存在磁盘上的.frm文件中，所以表自身继续存在，在服务器重启动
 *时它们是空的。');
 */

DROP TABLE if exists test;
CREATE TABLE test ENGINE=MEMORY select * from pet;
ALTER TABLE test ENGINE = InnoDB;

/* MySQL Server 5.5上，
 * lock tables read后，其它进程/线程不能修改该表，可以查询。
 * lock tables write后，其它进程/线程不能修改或查询该表。
 */
lock tables test read;
show open tables from test;
unlock tables;

lock table test write;
insert into test values('wang', 'ping', 'people', 'm', NULL, NULL);
# begin会造成unlcok table; 其它进程/线程可以查询。
begin;
insert into test values('li', 'ping', 'people', 'm', NULL, NULL);
commit;



/*
	在InnoDB中，select,insert,update,delete等语句执行时都会自动加解锁。select的锁一般执行完就释放了，修改操作的X锁会持有到事务结束，效率高很多。至于详细的加锁原理，见这里，搜“InnoDB存储引擎中不同SQL在不同隔离级别下锁比较”

　　mysql也给用户提供了加锁的机会，只要在sql后加LOCK IN SHARE MODE 或FOR UPDATE

　　共享锁（S）：SELECT * FROM table_name WHERE ... LOCK IN SHARE MODE
　　排他锁（X）：SELECT * FROM table_name WHERE ... FOR UPDATE

　　值得注意的是，自己加的锁没有释放锁的语句，所以锁会持有到事务结束。

　　mysql 还提供了LOCK TABLES，UNLOCK TABLES，用于加表锁。

*/
