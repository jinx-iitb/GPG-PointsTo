#include <stdio.h>
int **p, **q, *x, *y, *z, a, b, c;

void f(){
    *p = &a;
    y = z;
}
int main(){
    p = &z;
    y = &b;
    z = &c;
    f();
    return 0;
}