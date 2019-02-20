#include <stdio.h>

#define PAGE_SHIFT        12

#ifdef __ASSEMBLY__
#define PAGE_SIZE        (1 << PAGE_SHIFT)
#else
#define PAGE_SIZE        (1UL << PAGE_SHIFT)
#endif
#define PAGE_MASK        (~(PAGE_SIZE-1))

int main()
{
	printf("%d\n", (1 << PAGE_SHIFT));
	return 0;
}
