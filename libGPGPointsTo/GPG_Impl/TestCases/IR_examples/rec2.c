#include <stdio.h>
int **p, *x, *y, *z, a, b, c, d;
void f();
void g()
{
    if(a > b)
    {
        p = &y;
        f();
    }
    else
    {
        x = &a;
        y = &b;
    }    
}
void f()
{
    y = &a;
    p = &y;
    if(a > 10)
    {
        p = &x;
        g();
    }
    else
    {
        *p = y;
    }
}
int main()
{
    if(a > 10)
        f();
    else{
        p = &x;
        x = &a;
    }
    return 0;
}