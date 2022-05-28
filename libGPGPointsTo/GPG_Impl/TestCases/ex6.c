#include <stdio.h>

int k = 5;
int o;

int main(int argc, char* argv[]){
    int* l = &k;
    printf("%p", l);
    int a = 4;
    int b = *l;
    int *c = &a;
    int *d = &b;
	int **x;
	if(a*4 == 2*8){
	    x = &c;
	}else{
	    x = &d;
	}
	c = *x;
	return k;
}
