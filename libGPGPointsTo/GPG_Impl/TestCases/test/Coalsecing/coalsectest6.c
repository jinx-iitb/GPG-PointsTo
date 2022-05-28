#include "../Test.h"
int *x,*y,**p,a,b,c;

void f(){
	x=&a;
	if(a)
	  x=&b;
	else
      y=&b;
    *p=&c;
    COALESCE(7,9);
    COALESCE(5,9);
    COALESCE(9,10);
}


int main(){
	//p=&y;
	//f();
	y=&c;
	p=&x;
	f();
}