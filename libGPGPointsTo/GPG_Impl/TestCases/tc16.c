#include <stdio.h>
int a;
void f(){
    int *x, *y, *z, b, c;
    x = &a;
    y = x;
    z = y; 
}
int main(){
    f();
    return 0;
}