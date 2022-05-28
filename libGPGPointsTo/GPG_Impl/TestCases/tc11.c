#include <stdio.h>
int **p, **q, **r, *x, *y, *z, a, b, c;

void f(int** xx,int **yy){
    int* temp = xx;
    *xx = yy;
    *yy = temp;
}

int main(){
    p = &x;
    *q = &a;
    r = &y;
    f(&x,&y);
    x = &a;
    return 0;
}