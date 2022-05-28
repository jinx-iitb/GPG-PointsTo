#include <stdio.h>
int **p, **q, *x , *y, a, b, c;
int main(){
    p = &x;
    if(a > 10){
        x = &a;
        y = &b;
    }
    else{
        x = &c;
        y = &a;
    }
    q = &y;    
    return 0;
}