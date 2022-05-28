#include <stdio.h>
void f();
void g();
int *x, a, b, c, d;
void g()
{
    x = &c;
    if(a < b)
    {
        g();
    }
    else
    {
        f();
        x = &d;                
    }

}
void f()
{
    x = &a;
    if(a > 10)
    {
        x = &a; 
        f();       
    }
    else if(a > 20 )
    {
        x = &b;
        g();
    }
    else
    {
            
    }
}
int main()
{
    f();
}