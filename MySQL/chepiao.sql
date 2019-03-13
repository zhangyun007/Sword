drop table if exists chepiao;

create table chepiao (checi char(10), qidian int, zhongdian int, chexiang int, zuowei int, id char(20));

delimiter //

drop procedure if exists InsertProc;
create procedure InsertProc()
begin
    declare i int;
    declare j int;
    set i = 1;
    set j = 1;
    while i < 11 do
        while j < 121 do
            insert into chepiao (checi, qidian, zhongdian, chexiang, zuowei, id) values ('G162', 1, 14, i, j, NULL);
            set j = j + 1;
        end while;
        set i = i + 1;
        set j = 1;
    end while;        
end//

delimiter ;

call InsertProc();


/*
 *memory表存储在RAM里。当服务器关闭时，存储在MEMORY表里的数据丢失。
 *表的定义存在磁盘上的.frm文件中，所以表自身继续存在，服务器重启动
 *后它们是空的。
 */

DROP TABLE if exists test;
CREATE TABLE test ENGINE=MEMORY select * from chepiao;
ALTER TABLE test ENGINE = InnoDB;


/* MySQL Server 5.5上，
 * lock tables read后，其它进程/线程不能修改该表，可以查询。
 * lock tables write后，其它进程/线程不能修改或查询该表。
 */
lock tables test read;
show open tables from test;
unlock tables;

lock table test write;
insert into test (checi, qidian, zhongdian, chexiang, zuowei, id) values ('G88', 1, 14, i, j, NULL);
/* begin会造成unlcok table; 其它进程/线程可以查询。 */
begin;
insert into test (checi, qidian, zhongdian, chexiang, zuowei, id) values ('G68', 2, 43, i, j, NULL);
commit;


/*
	在InnoDB中，select,insert,update,delete等语句执行时都会自动加解锁。select的锁一般执行完就释放了，修改操作的X锁会持有到事务结束，效率高很多。至于详细的加锁原理，见这里，搜“InnoDB存储引擎中不同SQL在不同隔离级别下锁比较”

　　mysql也给用户提供了加锁的机会，只要在sql后加LOCK IN SHARE MODE 或FOR UPDATE

　　共享锁（S）：SELECT * FROM table_name WHERE ... LOCK IN SHARE MODE
　　排他锁（X）：SELECT * FROM table_name WHERE ... FOR UPDATE

　　值得注意的是，自己加的锁没有释放锁的语句，所以锁会持有到事务结束。

　　mysql 还提供了LOCK TABLES，UNLOCK TABLES，用于加表锁。

　　可以通过检查InnoDB_row_lock状态变量来分析系统上的行锁的争夺情况：
　　mysql> show status like 'innodb_row_lock%';

*/
