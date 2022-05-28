#include <stdio.h>
int *x, *y, **p, **q, a, b, c;
int main()
{
    int* temp = x;
    x = &a;
    if (a > 5)
    {
        *p = y;
    }
    x = &b;
    y = temp;
}
