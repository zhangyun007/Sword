create database testdb;
use testdb;

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
						


/* 雇员信息和电话号码要么都插入表中，要么都不插入。 beging开始一个“事务” */						
begin;
INSERT INTO `employee` (`id`, `first_name`, `last_name`, `job_title`, `salary`) VALUES (9, 'Grace', 'Williams','Softwaree Engineer', 5000);
INSERT INTO `telephone` (`id`, `employee_id`, `type`, `no`) VALUES (13, 9, 'mobile', '270-598712');
Commit;

select * from employee;
select * from telephone;

/*
 * memory表存储在RAM里。当服务器关闭时，存储在MEMORY表里的数据丢失。表的定义存在磁盘上的.frm文件中，所以表自身继续存在，服务器重启动后它们是空的。
 */
CREATE TABLE tmp ENGINE = InnoDB select * from employee;
select * from tmp;

drop database testdb;