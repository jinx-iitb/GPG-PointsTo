#include "../Test.h"

int *x,*y,**p,a,b,c;

void f(){
	x=&a;
	y=&b;
	*p=&c;
   COALESCE(6,7);
  // COALESCE(7,8);
   NOCOALESCE(7,8);
}


main(){
	p=&x;
	f();
	COALESCE(7,8);
}