use test

drop table if exists test;
CREATE TABLE test (c1 float(10,2),c2 decimal(10,2));
insert into test values(131072.32, 131072.32);
select * from test;

show character set;
show collation like 'utf8%';
show variables like 'character_set_server';