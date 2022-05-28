#include <stdio.h>

int **p;
int *y;

void f(int** x){
    int* temp = *x;
    if(*temp > 10){
        *p = *x; 
    }else{
        //q = x;
        *p = y;
    }
    y = temp;
    *x = y;
    //**p = 10;
    //return *p;
}

int main(int argc, char* argv[]){
    int a = 4;
    int b = 5;
    int *c = &a;
    int *d = &b;
	int **x;
	if(a*4 == 2*8){
	    x = &c;
	}else{
	    x = &d;
	}
	f(x);
	c = *x;
	return 1;
}
