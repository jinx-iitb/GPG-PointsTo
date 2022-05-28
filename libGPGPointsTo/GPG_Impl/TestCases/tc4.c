#include <stdio.h>

int f(int** x, int** y, int* z){
    *x = z;
    *y = z;
}


int main(){
    int a = 1;
    int b = 2;
    int* p = &a;
    int* q = &b;
    int** x = &p;
    int** y = &p;
    f(x,y,&b);
    return 0;
}
