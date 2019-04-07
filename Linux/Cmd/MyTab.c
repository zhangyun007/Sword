#include <stdio.h>
#include <unistd.h>

void set_zero(char *p, int size)
{
        int k;
        for (k = 0; k < size; k++) {
                *(p + k) = '\0';
        }
}

int main()
{
	char buf[1024] = "";
	char *begin, *end;

	read(0, buf, sizeof(buf));
	//write(1, buf, sizeof(buf));

	begin = end = buf;

	while (*end != '\0') {
		while (*end != '\n')
			end++;

		write(1, begin, end - begin);

		begin = end++;
	}
	write(1, "\n", 1);

	return 0;
}
