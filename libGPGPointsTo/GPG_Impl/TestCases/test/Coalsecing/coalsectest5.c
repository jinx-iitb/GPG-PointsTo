#include "../Test.h"
int *x,*y,**p,a,b,c;

void f(){
	x=&a;
	if(a) {
	  x=&b;
	  p=&y;
	}
    *p=&c;
    COALESCE(7,8);
    NOCOALESCE(7,10);
}
int main(){
	p=&x;
	f();
	NOCOALESCE(7,10);
	COALESCE(7,10);
}