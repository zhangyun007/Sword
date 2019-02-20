# Python连接MySQL需要安装这个东西：http://dev.mysql.com/downloads/connector/python/ 

import mysql.connector

config = {
    'user':'root',
    'password':'root',
    'host':'localhost',
    'database':'test'}

l=[]

for x in range(1000):
    print(x)
    cnx = mysql.connector.connect(**config)
    l.append(cnx)

for x in l:
    
    cursor=x.cursor()

    cursor.execute('show tables;')
    for (owner) in cursor:
        print(owner)
        pass

    cursor.execute('select * from test_user;')
    for (name) in cursor:
        print(name)
        pass

for x in l:
    cnx.close()
