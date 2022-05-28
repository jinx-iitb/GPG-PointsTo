#include <stdio.h>
struct s1{
    int *a;
    struct s1* next;
};
struct s1 *p, *q, r, s;
int *x, *y, **z;
int a, b, c;
int main(){
    // p = &r;
    // q = &s;
    // x = &a;
    p->next = &s;
    p->next->a = x; 
    *z = x;
    return 0;
}