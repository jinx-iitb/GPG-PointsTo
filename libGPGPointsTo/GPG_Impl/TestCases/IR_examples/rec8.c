#include <stdio.h>
int *x, a, b;
void g();
void f()
{
    if(a > 10){
        x = &b;
    }
    else{
        g();
    }
} 
void g()
{
    f();
}
int main(){
    x = &a;
    f();
    return 0;
}