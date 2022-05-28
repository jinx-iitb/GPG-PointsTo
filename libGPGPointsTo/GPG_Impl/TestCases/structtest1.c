#include <stdio.h>
#include <stdlib.h>
struct s1{
    int* a;
    struct s1* next;       
};
struct s1 *x, y, z;
int a, b, c;
int main(){
    x = &y;
    y.next = &z;
    x = y.next;
    y.a = &a;
    return 0;
}