#include <stdio.h>
int *x, a, b, c, d;
int f()
{
    if(a > b + d)
    {
        x = &c;
    }
    else
    {
        x = &b;
        f();
    }
    return 0;
}
int main()
{
    x = &a;
    if(a > 10)
    {
        f();
    }
    else
    {
        x = &d;
    }
    return 0;
}