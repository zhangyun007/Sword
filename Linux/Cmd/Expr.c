#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*****************************
 *  2 + 5
* token[0][BUF_SIZE] == '2'
* token[1][BUF_SIZE] == '+'
* token[2][BUF_SIZE] == '5'
* **************************/

#define BUF_SIZE 64
int len;
char token[64][BUF_SIZE];

char * var[64];

void build_token(char *s)
{
        int i = 0;
        int j = 0;
        char * p = s;
        for (i = 0; i < 64; i++) {

                j = 0;
                while ((*p != '\0') && (*p != ' ') && (*p != '\n')) {
                        token[i][j] = *p;
                        j++;
                        p++;
                }
                token[i][j] = '\0';
                len++;

                while (*p == ' ') {
                        p++;
                }

                if (*p == '\0' || *p == '\n')
                        break;
        }
}

int is_float_point(char *p)
{
        char *h;
        for (h = p; *h != '\0'; h++) {
                if (*h == '.')
                        return 1;
        }
        return 0;
}

int is_alpha(char *p)
{
	while (*p != '\0')
		if  ( ((*p > 'a') && ('p' < 'z'))  ||  ((*p > 'A') && (*p < 'Z')) )
			return 0;
	return 1;
}

int is_number(char *p)
{
	while (*p != '\0') {
		if (*p < 0 || *p > 9) 
		return 0;
	}
	return 1;
}

/*
 * 输出token
 */
void token_out()
{
        int i;
        for (i = 0; i < len; i++) {
                if (token[i][0] != ' ' )
                        printf("%s ", token[i]);
        }
        printf("\n");
}


/*
 * 2 ** 62 is right, 2 ** 63 is wrong.
 */
long my_pow(int m, int n)
{
	int i;
	long j;

	j = m;
	for (i = 0; i < n - 1; i++)
		j = j *m;
	return j;
}

void op_del(char *s)
{
        int i, j, k;
        float a, b, c;
        int m ,n;
        char buf1[BUF_SIZE] = "";
        char buf2[BUF_SIZE] = "";

	long l;

        for (i = 0 ; i < 64; i++) {

                if (strcmp(token[i], s) == 0) {

                        for (k = 0; k < BUF_SIZE; k++)
                                buf1[k] = token[i - 1][k];
                        for (k = 0; k < BUF_SIZE; k++)
                                buf2[k] = token[i + 1][k];

                        if (is_float_point(buf1) || is_float_point(buf2)) {
                                a = atof(buf1);
                                b = atof(buf2);
                                if (strcmp(s, "*") == 0)
                                        c = a * b;
                                if (strcmp(s, "/") == 0)
                                        c = a * b;
                                if (strcmp(s, "+") == 0)
                                        c = a * b;
                                if (strcmp(s, "-") == 0)
                                        c = a * b;
                                sprintf(token[i - 1] , "%f",  c);
                        } else {
                                m = atoi(buf1);
                                n = atoi(buf2);
                                if (strcmp(s, "**") == 0) 
					l = my_pow(m, n);
				if (strcmp(s, "*") == 0)
					l = m * n;
				if (strcmp(s, "/") == 0)
					l = m / n;
				if (strcmp(s, "+") == 0)
					l = m + n;
				if (strcmp(s, "-") == 0)
					l = m - n;
				sprintf(token[i - 1] , "%ld",  l);
                        }
                        for (j = i; j < 64; j++)  {
                                for (k = 0; k < BUF_SIZE; k++) {
                                        token[j][k] = token[j + 2][k];
                                }
                        }
                        len -= 2;
                        i--;

                        token_out();
                }
        }
}

int main()
{
        int i, j;
        char s[128] = "";

        for (i = 0 ; i < 64; i++) {
                for (j = 0; j < 64; j++) {
                        token[i][j] = '\0';
                }
        }

        read(1, s, sizeof(s));

        build_token(s);
        //token_out();

        op_del("**");
        op_del("*");
        op_del("/");
        op_del("+");
        op_del("-");
	
	//printf("%f\n", pow(2, 100));

        return 0;
}
