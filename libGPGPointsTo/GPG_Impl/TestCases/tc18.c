#include <stdio.h>
int *x, *y, *z, **p, a, b;
int P(){
    *p = &a;
    if( a > 10){
        y = &b;
    }
    else{
        x = &a;
    }
    *p = &b;
}
int main(){
    p = &z;
    x = NULL;
    y = NULL;
    P();
    return 0;
}