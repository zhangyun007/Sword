#CFLAGS:= -O3 -g -Wall -Werror
#CFLAGS:= -ofast -g -Wall -Werror --std=c++11 -stdlib=libc++
CFLAGS:= -ofast -g -Wall -Werror --std=c++11 

CC = g++
#CC = clang

all: first vector1 vector2 vector3 vector4 deque list1 list2 list3 \
	set1 set2 map1 map2 thread sort1 sort2 bitset1 bitset2 \
	unorderedmap1 prime epoll_example1 epoll_example2 epoll_example3 epoll_test \
	rtsp rtmp

first: first.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

vector1: vector1.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

vector2: vector2.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

vector3: vector3.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

vector4: vector4.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

deque: deque.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

list1: list1.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

list2: list2.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

list3: list3.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

map: map.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

set1: set1.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

set2: set2.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

map1: map1.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

map2: map2.cpp
	$(CC) $(CFLAGS) -o $@ $+ 

hash: hash.cpp
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

bst: bst.cpp
	$(CC) $(CFLAGS) -o $@ $+  

avl: avl.cpp
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
	rm -f first vector1 vector2 vector3 vector4 deque list1 list2 list3 \
	set1 set2 map1 map2 hash thread sort1 sort2 bitset1 bitset2 bst avl \
	unorderedmap1 prime epoll_example1 epoll_example2 epoll_example3 epoll_test \
	rtsp rtmp
