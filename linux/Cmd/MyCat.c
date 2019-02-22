#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int fd, i, j, n;
	char *p;
	char buf[1024] = "";

	if (argc < 2) {
		n = read(0, buf, sizeof(buf));
		write(1, buf, n);

		while (n == sizeof(buf)) {

			for (j = 0; j < sizeof(buf); j++) {
				buf[j] = 0;
			}

			n = read(0, buf, sizeof(buf));
			write(1, buf, n);
		}
		return 0;
	}
	
	write(1, "\n", 1);

	memset(buf, 0, sizeof(buf));
	i = 1;
	p = argv[i];

	while (p != NULL) {

		char tmp[64];
		sprintf(tmp, "-----------------------%s---------------------\n\n", p);
		write(1, tmp, sizeof(tmp));

		//加上sync会导致程序不正确 ./MyCat *.c | ./MyCat
		//sync();

		fd = open(p, O_RDONLY);
		
		if (fd == -1) {
			char tmp[64];
			sprintf(tmp, "No such file : %s", p);
			write(1, tmp, sizeof(tmp));
			return -1;
		}


		n = read(fd, buf, sizeof(buf));
		write(1, buf, n);

		while (n == sizeof(buf)) {

			for (j = 0; j < sizeof(buf); j++) {
				buf[j] = 0;
			}

			n = read(fd, buf, sizeof(buf));
			write(1, buf, n);
		}
		close(fd);
		write(1, "\n", 1);

		i++;
		p = argv[i];

		for (j = 0; j < 1024; j++) {
			buf[j] = 0;
		}
	}

	return 0;
}
