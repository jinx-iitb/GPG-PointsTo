#include <stdio.h>
#include <stdlib.h>
struct node{
    struct node* n;
    int d;
};
struct node *y, *x;
void P(){
    int a,b;    
    x = x->n->n;                            
}
int main(){
    int a,b;
    y = (struct node*)malloc(sizeof(struct node));
    y->n = (struct node*)malloc(sizeof(struct node));
    x->n = y->n;
    x->n->n = NULL;
    while(a < 4){
        y = y->n;
    }
    P();
    return 0;
}