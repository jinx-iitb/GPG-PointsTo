#include "../Test.h"
int *x,*y,**p,a,b,c;

void f(){
	x=&a;
	if(a)
	  x=&b;
	POINTSTO(x,"a,b");
    *p=&c;
}


int main(){
	p=&x;
	f();
	POINTSTO(x,"c");
}