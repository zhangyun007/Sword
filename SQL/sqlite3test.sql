.open test.db
.databases
.table
.schema
drop table test;
CREATE TABLE test (name char(10));
insert into test (name) values('zhangfei'), ('liubei'), ('zhugeliang'), ('caocao'), ('guanyu');
select * from test;
