#include <stdio.h>
#include <sys/sysinfo.h>

int main()
{
        struct sysinfo si;
        sysinfo(&si);
        printf("Totalram:       %lu\n", si.totalram);
        printf("Available:      %lu\n", si.freeram);
        return 0;
}
