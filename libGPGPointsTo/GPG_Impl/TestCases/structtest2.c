#include <stdio.h>
#include <stdlib.h>
struct s1{
    int a;
    struct s1* next;   
    int* ptr; 
};

int **p, **q, **r, *z, a, b, c; 
struct s1 *x, *y, *w;

int f(){
    
    x = malloc(sizeof(struct s1));    
    y = malloc(sizeof(struct s1));
    x->next = malloc(sizeof(struct s1));

    y->ptr = &a;
    y->next = x->next;    
    w = y->next->next->next;

    z = y->ptr;     
    return 0;
}
int main(){
    f();
    return 0;
}