from socket import * 

HOST = '0.0.0.0'
PORT = 9999

s = socket(AF_INET,SOCK_DGRAM)
s.bind((HOST,PORT)) 
print('...waiting for message..')
while True: 
	data,address = s.recvfrom(1024) 
	print(data,address)
	s.sendto('this is the UDP server'.encode('utf-8'), address)
s.close()
