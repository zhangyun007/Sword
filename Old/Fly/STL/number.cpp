#include <vector>
#include <iostream>

int main() {
	int a = 12;
	int b = -12;
	
	printf("%d %d %x %x", a, b, a, b);
	//输出结果为12 -12 c fffffff4 其中fffffff4为c的补码，即c的反码+1
}