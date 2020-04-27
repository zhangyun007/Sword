from socket import * 

HOST = '0.0.0.0'
#HOST='36.7.226.209'
PORT = 9999

s = socket(AF_INET,SOCK_DGRAM)
s.bind((HOST,PORT)) 
print('...waiting for message..')

while True: 
	data,address = s.recvfrom(1024) 
	print(data,address)
	s.sendto('this is from UDP server'.encode('utf-8'), address)
	if data == "EXIT":
		s.close()
		break