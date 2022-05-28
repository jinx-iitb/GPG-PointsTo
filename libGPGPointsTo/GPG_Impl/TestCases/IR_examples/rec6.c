#include <stdio.h>
void f();
void g();
int *x, a, b, c, d, e;
void f()
{
    x = &a;
    if(a > 10){
        x = &e;
        f();
    }
    else{
        x = &b;
        g();
    }
}
void g()
{
    x = &c;
    if(a < b)
    {
        f();
    }
    else
    {
        x = &d;
    }

}
int main()
{
    if(a > 10)
        f();
    else
        g();
}