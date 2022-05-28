#include <stdio.h>

int *z;

void f(int** x, int** y){
    z = *y;
    int* temp = *x;
    *x = *y;
    *y = temp;
}

void g(){

printf("hello");
}


int main(int argc, char* argv[]){
    int a = 4;
    int b = 5;
    int *c = &a;
    int *d = &b;
	printf("%d %d %d %d\n", *c, *d, a, b);
	f(&c, &d);
	printf("%d %d %d %d\n", *c, *d, a,b);
	return 1;
}
