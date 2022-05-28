#include <stdio.h>
int (*p)[5];
int *x, *y, c;
int main()
{
    int a[5];
    p = &a;
    x = &c;
    y = &c;
    return 0;
}