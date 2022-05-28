#include <stdio.h>
int main()
{
    int* z[10][10],a;
    z[0][1] = &a;
    z[0][0] = z[0][1];
    return 0;
}