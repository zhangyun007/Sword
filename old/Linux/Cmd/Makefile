#CFLAGS:= -O3 -g -Wall -Werror
CFLAGS:= -ofast -g -Wall -Werror
#CFLAGS:= -ofast -g -Wall -Werror -cc1 -ast-dump 
CC = gcc
#CC = clang

all: MyCat MyTab Expr Prime Sysinfo TestDaemon Client Server

MyCat: MyCat.c
	$(CC) $(CFLAGS) -o $@ $+ 

MyTab: MyTab.c
	$(CC) $(CFLAGS) -o $@ $+ 

Expr: Expr.c
	$(CC) $(CFLAGS) -o $@ $+ 

Prime: Prime.c
	$(CC) $(CFLAGS) -o $@ $+ 
	
Sysinfo: Sysinfo.c
	$(CC) $(CFLAGS) -o $@ $+ 

TestDaemon: TestDaemon.c
	$(CC) $(CFLAGS) -o $@ $+ 

Client: Client.c
	$(CC) $(CFLAGS) -o $@ $+ 

Server: Server.c
	$(CC) $(CFLAGS) -o $@ $+ 

clean:
	rm -f a.out 
	rm -f MyCat MyTab Expr Prime Sysinfo TestDaemon Client Server
