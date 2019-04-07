#include	<stdio.h>
#include	<math.h>

long double stra(unsigned num);
long double sinloop( long double x, unsigned t);
long double cosloop( long double x, unsigned t);
long double Pow(long double, int);

int
main(int argc, char *argv[])
{
	long double x;

	printf("请输入x:");
	scanf("%Lf", &x);
	printf("sinx=%Lf\n", sinloop(x, 1));
	printf("cosx=%Lf\n", cosloop(x, 1));

	return 0;
}
	
long double
sinloop(long double x, unsigned t)
{
	if(fabs(Pow(x, 4*t-3)/stra(4*t-3)-Pow(x, 4*t-1)/stra(4*t-1)) < 0.000001)
		return 0.000001;
	else
		return Pow(x, 4*t-3)/stra(4*t-3)-Pow(x, 4*t-1)/stra(4*t-1)+sinloop(x, t+1);
}

long double
stra(unsigned num)
{
	if(num == 1 || num == 0)
		return 1;
	else
		return num*stra(num-1);
}

long double
Pow(long double x, int t)
{
	if(t == 0)
		return 1;
	if(t == 1)
		return x;
	if(t%2 == 0)
		return Pow(x*x, t/2);
	else
		return x*Pow(x*x, t/2);
}

long double
cosloop(long double x, unsigned t)
{
        if(fabs(Pow(x, 4*t-4)/stra(4*t-4)-Pow(x, 4*t-2)/stra(4*t-2)) < 0.000001)
                return 0.000001;
        else
                return Pow(x, 4*t-4)/stra(4*t-4)-Pow(x, 4*t-2)/stra(4*t-2)+cosloop(x, t+1);
}

