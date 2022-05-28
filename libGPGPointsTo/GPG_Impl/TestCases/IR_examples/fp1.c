#include <stdio.h>
int *x, *y, a, b;
int (*f_ptr)();
int f(){
    x = &a;
    y = &b;
    if(a > 10)
        f();
    return 0;
}
int g(){
    (*f_ptr)();
    return 0;
}
int main()
{
    x = &b;
    y = &a;
    f_ptr = f;
    g();
    return 0;
}
