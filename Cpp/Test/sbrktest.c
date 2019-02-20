#include <unistd.h>
#include <stdio.h>
#include <string.h>

char s[] = "sbrk() is good enough, you should through malloc/free away!\n";

/*
 * Why large[] do not cause 'free -m' changed ?
 */
char large[50000000] = "";

int main()
{
	void * p;
	char * a;
	char * b;

	int i;
	int len = sizeof(s);

	printf("sizeof s is %d\n", len);

	p = sbrk(10000000);

	a = (char *)p;

	b = a  + 10000000;

	while (a < b - 100) {
		for (i = 0; i < sizeof(s); i++) {
			*a = s[i];
		}
		a += sizeof(s);
	}

	printf("%s\n", s);

	p = sbrk(-10000000);

	sleep(100);

	return 0;
}
