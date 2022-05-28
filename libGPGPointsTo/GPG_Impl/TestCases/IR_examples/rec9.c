#include <stdio.h>
void f();
int a,b;
void g(){
    a = 10;
    b = 1;
    while(a >= 0)    
    {
        f();
        a--;
    }
}
void f()
{
    if( a == 10)
    {
        a = a/2;
        g();
    }
    else
    {
        b = b + a;
    }
}
int main()
{
    f();
    return 0;
}