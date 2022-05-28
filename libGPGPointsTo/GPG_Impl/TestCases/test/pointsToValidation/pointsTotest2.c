#include "../Test.h"
int *x,*y,**p,a,b,c;

void f(){
	x=&a;
	if(a)
	  x=&b;
    *p=&c;
}


int main(){
	p=&y;
	f();
	p=&x;
	f();
}