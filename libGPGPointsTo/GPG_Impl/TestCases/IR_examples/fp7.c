#include <stdio.h>
int *x, *y, a, b;
int (*f_ptr)();
int f2();
int f(){
    x = &a;
    y = &b;    
    f2();
    return 0;
}
int f2()
{
    if(a > 10){
        x = &a;
    }
    else{
        f();
    }
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
