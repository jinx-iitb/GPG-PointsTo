#include "../Test.h"

int **p,*x,*y,a,b,c,d;



void f(){


  x=&a;
  y=&b;


  if(a)
  	p=&x;
  else
  	p=&y;

  *p=&c;

   y=&d;



}

int main(){

	f();

  POINTSTO(x,"a,c");
  POINTSTO(y,"d");

}