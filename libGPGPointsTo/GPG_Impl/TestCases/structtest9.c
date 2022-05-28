#include <stdio.h>
#include <stdlib.h>
struct node{
    struct node* n;
    int d;
};
struct node *y, *x;
int a, b;
int main(){
    x = x->n;
    y = x;
    return 0;
}