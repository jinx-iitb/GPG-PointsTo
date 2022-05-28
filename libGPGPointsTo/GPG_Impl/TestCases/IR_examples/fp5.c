#include <stdio.h>
int **p, *x, *y, a, b, c;
int (*f_ptr)();
int g()
{
    p = &x;
    (*f_ptr)();
    return 0;
}
int f()
{
    (*f_ptr)();
    return 0;
}
int main()
{
    f_ptr = g;
    f();
    return 0;
}