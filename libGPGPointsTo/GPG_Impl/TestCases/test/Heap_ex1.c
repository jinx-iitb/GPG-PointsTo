#include<stdio.h>
#include<stdlib.h>
int *x,*y,*z;
int **a,**b,**c;
int ***u,v,w;
int main(){
    int v = 1;
    int w = 120;    
    x = (int*)malloc(sizeof(int));
    *x = 10;
    y = x;
    z = y;
    a = (int**)malloc(sizeof(int*));
    b = a;
    *b = x;
    c = a;
    *a = z;
    **c = 10;
    u = &c;
}
