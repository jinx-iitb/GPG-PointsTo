#include <stdio.h>
int **pp, **q, *x ,*y, a, b, c;
int p(){
    int **r, *xx, **yy;
    r = &x;
    xx = *r;
    *yy = xx;
    pp = &xx;
    return 0;
}
int main(){
    p();
    return 0;    
}