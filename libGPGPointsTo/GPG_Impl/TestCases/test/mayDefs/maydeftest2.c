#include "../Test.h"

int **p,*x,*y,a,b,c;



void f(){


  x=&a;
  y=&b;


  if(a)
  	p=&x;
  else
  	p=&y;

  *p=&c;



}

int main(){

	f();

  POINTSTO(x,"a,c");
  POINTSTO(y,"b,c");

}