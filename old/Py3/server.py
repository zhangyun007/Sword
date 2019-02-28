#!/usr/bin/python3

import socket
import sys

# 创建 socket 对象
serversocket = socket.socket(
            socket.AF_INET, socket.SOCK_STREAM) 

# 获取本地主机名
host = socket.gethostname()
print(host)

port = 9999

# 绑定端口
serversocket.bind((host, port))

# 设置最大连接数，超过后排队
serversocket.listen(5)

while True:
    # accept函数返回一个元组(a ,b)，将a赋给clientsocket, b赋给addr。
    clientsocket,addr = serversocket.accept()      

    print("Address: %s" % str(addr))
    
    msg = 'Welcome to Server\n'
    clientsocket.send(msg.encode('utf-8'))
    clientsocket.close()
