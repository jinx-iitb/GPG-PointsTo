#include <stdio.h>
int **p, *x, *y, a, b, c;
int main()
{
    x = &a;
    if(a > b + c)
    {
        p = &y;
    }
    else
    {
        p = &x;
    }
    *p = &b;
}