#include <stdio.h>


int main(int argc, char* argv[]){
    int a = 4;
    int *b = &a;
    int **c = &b;
	printf("%p %p %d\n", c, *c, **c);
	return 1;
}
