#include <vector>
#include <iostream>

int main() {
	int a = 12;
	int b = -12;
	
	printf("%d %d %x %x", a, b, a, b);
	
	float c = 0.1;
	float d = -0.1;
	
	printf(" size of float = %d \n", sizeof(float));
	
	unsigned char* f = (unsigned char*)&c;
	printf("%02X %02X %02X %02X", f[0], f[1], f[2], f[3]);
	

	//输出结果为12 -12 c fffffff4 其中fffffff4为c的补码，即c的反码+1
}