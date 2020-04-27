from socket import *  

# 局域网
HOST='localhost'

# 公网
#HOST='deque.me'
#HOST='36.7.226.209'

PORT=9999  

s = socket(AF_INET,SOCK_DGRAM)  
s.connect((HOST,PORT))  
while True:  
	message = input('send message: ')  
	s.sendall(message.encode('utf-8'))
	data = s.recv(1024)  
	print(data)
s.close()
