#include <stdio.h>
int *x, a, b, c;
void f();
void g();
void h();
void r()
{
    if(a > 2)
    {
        g();
    }
    x = &b;
}
void g()
{
    if(a < b + c)
    {
        x = &a;
        f();
    }
    else{
        r();
    }
}
void f()
{
    if(a > b)
    {
        x = &c;
    }
    else
    {
        g();
    }
}
int main()
{
    f();
    return 0;
}