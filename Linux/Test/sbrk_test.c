#include <unistd.h>
#include <stdio.h>

int main()
{
	char  *a, *b;
	int i, j;

	b = (char *)sbrk(9000);

	for (j = 0; j < 1000; j++) {
		i = 0;
		a = b;
		while (i < 9000) {
			*a = 'n';
			a++;
			i++;
		}
	}
	return 0;
}
