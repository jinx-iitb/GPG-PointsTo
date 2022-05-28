#include <stdio.h>
void f(){
    int *x, *y, *z, a, b, c;
    x = &a;
    y = x;
    z = y; 
}
int main(){
    f();
    return 0;
}