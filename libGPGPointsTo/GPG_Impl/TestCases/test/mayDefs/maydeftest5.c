#include "../Test.h"

int **p,*x,*y,a,b,c,d;



void f(){


  x=&a;
  y=&b;


  if(a)
  	p=&x;
  else
  	p=&x;

  *p=&c;

}

int main(){

	f();

  POINTSTO(x,"c");
  POINTSTO(y,"b");

}