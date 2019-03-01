import threading
import socket
import sys

def worker():
    # 创建 socket 对象
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

    # 连接服务，指定主机和端口
    s.connect(('deque.me', 6666))

    # 接收小于 1024 字节的数据
    s.send(b"------------------Strings from clientmt.py-------------------\n")

    s.close()

l = []
for i in range(1000):
    l.append(threading.Thread(target=worker))

for t in l:
    t.start()

for t in l:
    t.join() 
