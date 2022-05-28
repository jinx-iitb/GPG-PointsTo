#include "../Test.h"

int **p,*x,*y,a,b,c;

int main(){


  x=&a;
  y=&b;


  if(a)
  	p=&x;
  else
  	p=&y;

  *p=&c;

  POINTSTO(x,"a,c");
  POINTSTO(y,"b,c");

}