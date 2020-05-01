#!/usr/bin/python3
# 文件名：client.py

# 导入 socket、sys 模块
import socket
import sys


# 创建 socket 对象
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

# 免费的STUN服务器
host = 'stun2.l.google.com'

# 设置端口
port = 19302

# 连接服务，指定主机和端口
s.connect((host, port))

# 接收小于 1024 字节的数据
msg = s.recv(1024)

s.close()

print(msg)
