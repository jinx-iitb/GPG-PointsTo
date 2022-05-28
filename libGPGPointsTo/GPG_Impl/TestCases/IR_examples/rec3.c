#include <stdio.h>
int **p, **q, *x, *y, *z, a, b, c, d;
void g();
void f()
{
    p = &y;
    q = &x;
    if(b > d)
    {
        x = &c;
        z = &b;
        y = z;
        g();
    }
    else
    {
        x = &b;
        y = &c;
        z = &a;
        f();
    }
    *p = *q;
}
void g()
{
    if(a > 10){
        x = &d;
        y = &b;
        z = &c;
        f();
    }
    else{
        x = &c;
        y = &a;
        z = x;
    }
}
int main()
{
    x = &a;
    p = &x;
    q = &y;
    if(a > 10)
    {
        f();
    }
    else
    {
        g();
    }
    *p = &d;
}