#CFLAGS:= -O3 -g -Wall -Werror
CFLAGS:= -ofast -g -Wall -Werror

all: sbrktest sbrk_test sqrt_test float_test mmap_test page_size math


sbrktest: sbrktest.c
	gcc $(CFLAGS) -o $@ $+

sbrk_test: sbrk_test.c
	gcc $(CFLAGS) -o $@ $+

sqrt_test: sqrt_test.c
	gcc $(CFLAGS) -o $@ $+

float_test: float_test.c
	gcc $(CFLAGS) -o $@ $+

mmap_test:mmap_test.c
	gcc $(CFLAGS) -o $@ $+

page_size: page_size.c
	gcc $(CFLAGS) -o $@ $+

math: math.c
	gcc $(CFLAGS) -o $@ $+ 


clean:
	rm -f a.out 
	rm -f sbrktest sbrk_test sqrt_test float_test mmap_test page_size math
