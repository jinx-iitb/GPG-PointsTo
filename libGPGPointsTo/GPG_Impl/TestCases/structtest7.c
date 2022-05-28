#include <stdio.h>
#include <stdlib.h>
struct node{
    struct node* n;
    int d;
};
struct node *y, *x;
void P(){
    int a,b;
    while (a > 2)
    {        
        x = x->n;                        
    }    
}
int main(){
    int a,b;
    y = (struct node*)malloc(sizeof(struct node));
    x = y;
    while(a < 4){
        y->n = (struct node*)malloc(sizeof(struct node));
        y = y->n;
    }
    P();
    return 0;
}