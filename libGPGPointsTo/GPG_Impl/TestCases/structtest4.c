#include <stdio.h>
#include <stdlib.h>
struct s1{
    int* a;
    struct s1* next;       
};
struct s1 *x, y, z, z2;
int a, b, c;
int main(){

    x = &y; // [*] | []
    y.next = &z; // [n] | []
    x->next = &z2;// [*,n] | []
        
    x = y.next; // [*] | [n]
    y.a = &a;
    return 0;
}