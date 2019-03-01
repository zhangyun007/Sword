from socket import *  

#HOST='localhost'
HOST='deque.me'
PORT=9999  

s = socket(AF_INET,SOCK_DGRAM)  
s.connect((HOST,PORT))  
while True:  
	message = input('send message: ')  
	s.sendall(message.encode('utf-8'))
	data = s.recv(1024)  
	print(data)
s.close()
