#include "../Test.h"
int *x,*y,*w,**p,a,b,c;

void f(){
	x=&a;
	if(a)
	  *p=w;
    y=&b;
    NOCOALESCE(5,7); 
    NOCOALESCE(5,8); 
}


int main(){
	p=&y;
	w=&c;
	f();
	COALESCE(5,8);
	COALESCE(5,7); //5,7 fails due to dead gpu elimination y=&c(in 7 will be removed)
}