#include <stdio.h>
int ***u, **x, *y, a;
float *z, *w, b, c;
int main()
{    
    y = &a;
    if(a > 2)
    {
        z = &b;
    }
    else
    {
        *x = &a;
    }
    w = &c;
    u = &x;
    return 0;
}