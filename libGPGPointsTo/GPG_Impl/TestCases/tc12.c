#include <stdio.h>
int **p, *x, a, c;
float **q, *y, b;
double *xx, yy;
int main(){
    xx = &yy;
    if(a > 10){
        *q = &b;
        x = &c;
    }
    else{        
        *p = &a;
        y = &b;
    }
    *p = &c;
    return 0;
}