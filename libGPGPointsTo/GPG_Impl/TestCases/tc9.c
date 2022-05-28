#include <stdio.h>
int **p, **q, **r, *x, *y ,*z, a, b, c;
int main(){    
    *p = &a;
    if(a > 1000){
        y = &b;
        x = &c;
        z = &a;        
    }
    else{
        x = &b;
        y = &a;
        z = &c;
    }
    *p = &b;
    return 0;
}