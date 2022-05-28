#include <stdio.h>
int **p, *x, *y, a, b, c;
int g()
{
	p = &y;
	f();
	return 0;
}
int f()
{
	*p = &b;
	if(*x > 1)
	{
	   x = &c; 
	}
	else
	{
	   y = &a;
	}
	*x = *y + 2;
	return 0;
}
int main()
{
    p = &x;
	f();
	g();
	return 0;
}
