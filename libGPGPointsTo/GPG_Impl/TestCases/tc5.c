#include <stdio.h>
int *x, **p, **q, a, c;
float *y, b;
int main()
{
    x = &a;
    if (a > 5)
    {
        y = &b;
    }
    *p = &c;
    if(a < 2){
        q = &x;
    }
    x = &a;
}