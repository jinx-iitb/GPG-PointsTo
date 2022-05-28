#include <stdio.h>

int *x, *y, a, b, c, d;
void g()
{
    if(b > c)
	    y = &c;
    else    
        y = &d;
	a = b; // a_2 = b_1
}
void f()
{
    if(a > 10)
	    x = &a;
    else
        x = &b;
	c = a + 2; //c_1 = 	a_2 + 2
}
int main()
{
	a = b = 1; // a_1 = 1; b_1 = 1
	g();
	f();
	*y = *x + 2; // ???
}
