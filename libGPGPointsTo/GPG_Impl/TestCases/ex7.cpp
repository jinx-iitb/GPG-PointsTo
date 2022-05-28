#include <stdio.h>

void f(int* x){
    *x = 5;
}

void g(int &x){
    x = 5;
}

int main(int argc, char* argv[]){
    int a = 4;
    int b = 5;
    int *c = &a;
    int *d = &b;
    int **x = &c;
	c = *x;
	f(c);
	g(a);
	return 1;
}
