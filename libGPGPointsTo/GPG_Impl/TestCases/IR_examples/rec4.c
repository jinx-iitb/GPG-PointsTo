#include <stdio.h>
int **p, **q, *x, *y, *z, a, b, c, d, e;
int g();
int f()
{    
    if(a > 10)
    {
        x = &a;
    }
    else
    {
        x = &d;
        g();
    }
    return 0;
}
int g()
{    
    if(a > b)
    {        
        x = &c;
    }
    else
    {
        y = &e;
        f();
    }
    return 0;
}
int main()
{
    f();
    g();
    return 0;
}