#include <stdio.h>
int *p, a, b;
void P(int **x){
    p = &b;
    *x = &a;
}
int main(){
    int *p;
    p = &a;
    P(&p);
}