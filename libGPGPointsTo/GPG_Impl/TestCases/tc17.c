#include <stdio.h>
#include <stdlib.h>
int *x, *y, **p, a, b;
void P(){
    *p = &a;
    x = NULL;    
}
int main(){
    x = &a;
    y = &b;
    p = &x;
    P();
    return 0;
}