#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	//调用glibc库函数daemon,创建daemon守护进程
	if (daemon(0, 0)) {
		perror("daemon error");
		return -1;
	}
	printf("end.\n");
	while (1) {
		sleep(1);
	}
	return 0;
}
