#include <stdio.h>
int *x, a, b;
int (*f_ptr)();
int g()
{
    x = &b;
}
int f()
{
    x = &a;
    (*f_ptr)();    
}
int main()
{
    f_ptr = g;
    f();
    return 0;
}