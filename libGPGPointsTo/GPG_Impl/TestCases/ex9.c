#include <stdio.h>

int f(int* x){
    int a = 5;
    int b = 10;
    int c = 20;
    x = &a;
    if(*x > 10)
        x = &b;
    else
        x = &c;
    return *x;
}

int main(){
    int *p;
    int x = 5;
    p = &x;
    *p = 6;
    printf("%p %d", p, *p);
    f(p);
    return 1;
}
