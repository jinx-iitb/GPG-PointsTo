#include <stdio.h>
int **p, **x, *a, b;
int main(){
    b = 5;    
    p = &a;
    *x = &b;
    return 0;
}