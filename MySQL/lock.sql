/*
	在InnoDB中，select,insert,update,delete等语句执行时都会自动加解锁。select的锁一般执行完就释放了，修改操作的X锁会持有到事务结束，效率高很多。

　　可以通过检查InnoDB_row_lock状态变量来分析系统上的行锁的争夺情况：
　　mysql> show status like 'innodb_row_lock%';
	
表锁：
　　mysql 还提供了LOCK TABLES，UNLOCK TABLES，用于加表锁。MySQL服务器层提供，而不是存储引擎提供。
	
行锁：	
　　mysql也给用户提供了加行锁的机会，只要在sql后加LOCK IN SHARE MODE 或FOR UPDATE

　　共享锁（S）：SELECT * FROM table_name WHERE ... LOCK IN SHARE MODE 
												...	FOR SHARE (MySQL8.0加入)
　　排他锁（X）：SELECT * FROM table_name WHERE ... FOR UPDATE
	会对查询出来的所有“行”加锁。值得注意的是，自己加的锁没有释放锁的语句，所以锁会持有到事务结束。

	行锁由innodb引擎提供。搜索“InnoDB存储引擎中不同SQL在不同隔离级别下锁比较”。
*/

/* 
 * MySQL Server 5.5上，
 * lock tables read后，其它进程/线程不能修改该表，可以查询。
 */
lock tables test read;
show open tables from test;
unlock tables;


/* lock tables write后，其它进程/线程不能修改或查询该表。*/
lock table test write;

insert into test (checi, qidian, zhongdian, chexiang, zuowei, id) values ('G88', 1, 14, i, j, NULL);

begin;	/* begin会造成unlcok table; 其它进程/线程可以查询。 */

insert into test (checi, qidian, zhongdian, chexiang, zuowei, id) values ('G68', 2, 43, i, j, NULL);

commit;
