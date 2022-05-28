#include <stdio.h>
int a, b, c, *x;
int* arr[10];
int main()
{    
    arr[0] = &a;    
    x = &a;
    arr[1] = arr[0];
    return 0;
}