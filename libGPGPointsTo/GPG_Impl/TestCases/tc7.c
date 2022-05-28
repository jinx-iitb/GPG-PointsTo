#include <stdio.h>
int **p, **q, **r, *x, *y, *z, a, b, c;
int main(){
    x = &a;
    if(a > 10){
        y = &b;
        if(c < 10){
            p = &x;
        }
    }
    else{
        z = &c;
        if(b < 10){
            q = &y;
        }
    }
    z = x;
    *r = y;
    return 0;
}