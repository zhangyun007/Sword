#CFLAGS:= -O3 -g -Wall -Werror
#CFLAGS:= -ofast -g -Wall -Werror --std=c++11 -stdlib=libc++
CFLAGS:= -ofast -g -Wall -Werror --std=c++11 

CC = g++
#CC = clang

all: deque \
	set1 set2 map1 map2 thread sort1 sort2 bitset1 bitset2 \
	unorderedmap1 prime epoll_example1 epoll_example2 epoll_example3 epoll_test \
	rtsp rtmp

deque: deque.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

set1: set1.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

set2: set2.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

map1: map1.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

map2: map2.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

thread: thread.cpp
	$(CC) $(CFLAGS) -o $@ $+  -lpthread

sort1: sort1.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

sort2: sort2.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

bitset1: bitset1.cpp
	$(CC) $(CFLAGS) -o $@ $+  

bitset2: bitset2.cpp
	$(CC) $(CFLAGS) -o $@ $+  

unorderedmap1: unorderedmap1.cpp
	$(CC) $(CFLAGS) -o $@ $+  

prime: prime.cpp
	$(CC) $(CFLAGS) -o $@ $+  

epoll_example1: epoll_example1.cpp
	$(CC) $(CFLAGS) -o $@ $+  

epoll_example2: epoll_example2.cpp
	$(CC) $(CFLAGS) -o $@ $+  

epoll_example3: epoll_example3.cpp
	$(CC) $(CFLAGS) -o $@ $+  

epoll_test: epoll_test.cpp
	$(CC) $(CFLAGS) -o $@ $+  

rtsp: rtsp.cpp
	$(CC) $(CFLAGS) -o $@ $+ -L/usr/lib/x86_64-linux-gnu/ -I /usr/include/gstreamer-1.0/ -I /usr/include/glib-2.0/ -I /usr/lib/x86_64-linux-gnu/glib-2.0/include -I /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include/ -lgstrtspserver-1.0 -lgstreamer-1.0 -lgstsdp-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0

rtmp: rtmp.cpp
	$(CC) $(CFLAGS) -o $@ $+  -I/usr/include/x86_64-linux-gnu  -lavformat-ffmpeg -lavcodec-ffmpeg -lavutil-ffmpeg

clean:
	rm -f a.out 
	rm -f deque \
	set1 set2 map1 map2 thread sort1 sort2 bitset1 bitset2 \
	unorderedmap1 prime epoll_example1 epoll_example2 epoll_example3 epoll_test \
	rtsp rtmp
