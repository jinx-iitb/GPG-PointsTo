#include <stdio.h>
int **p, *x, *y, *w, *z, a, b, c, d;

void f(){
    x = &a;
    if(a > 10){
        *p = w;
        if(a>20){
            goto L1;            
        }
    }
    else{
        L1: z = y;
    }
    p = &x;
}
int main(){
    y = &b;
    w = &d;
    p = &y;
    f();
    return 0;
}