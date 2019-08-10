#CFLAGS:= -O3 -g -Wall -Werror
#CFLAGS:= -ofast -g -Wall -Werror --std=c++11 -stdlib=libc++
CFLAGS:= -ofast -g -Wall -Werror --std=c++11 

CC = g++
#CC = clang

all: set1 set2 map1 map2 thread

set1: set1.cpp
	$(CC) $(CFLAGS) -o $@ $+

set2: set2.cpp
	$(CC) $(CFLAGS) -o $@ $+

map1: map1.cpp
	$(CC) $(CFLAGS) -o $@ $+

map2: map2.cpp
	$(CC) $(CFLAGS) -o $@ $+

clean:
	rm -f a.out
	rm -f set1 set2 map1 map2