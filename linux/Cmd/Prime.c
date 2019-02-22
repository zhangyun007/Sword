/*
 * 	100		         25
 * 	1000		     168
 * 	1000,0		     1229
 * 	1000,00		     9592
 * 	1000,000	     78498
 *	1000,000,0       664579 
 *	1000,000,00      5761455
 *	1000,000,000     50847534 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define  E9        100000000
#define  E10       10000000000
#define  E11       100000000000
#define  E12       1000000000000

//是否为质数
char table[E9];

//质数个数
int num = 0;
//int prime[E8];

void cal_table()
{
        int j, k;
        memset(table, 1, E9);
        for (j = 2 ; j < E9; j++) {
                if ( table[j] ) {
                        num++;
                        //j的N倍均为合数，置0。
                        for ( k = j + j; k < E9; k += j )
                        {
                                table[k] = 0;
                        }
                }
        }
        printf("Totaly %d primes until E9.\n", num);
}

int main()
{
    cal_table();
    //init_prime();
    return 0;
}
