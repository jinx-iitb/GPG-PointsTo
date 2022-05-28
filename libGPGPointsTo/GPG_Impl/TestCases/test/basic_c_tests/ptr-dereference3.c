//#include "aliascheck.h"
#include "../Test.h"

void foo(int q){
  int i = 10;
  int k = i;

}
int main(){

int *s,*r,*x,**y,t,z,k;
	s = &t;
	r = &z;
	y = &r;
	s = r;
  //MUSTALIAS(s,&z);
	x = *y;
  //MUSTALIAS(x,r);
	foo(k);
	POINTSTO(s,"t");
	POINTSTO(s,"z");
	POINTSTO(x,"z");
return 0;
}
