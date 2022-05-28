#include "../Test.h"
int *w,*x,*y,*z,*y1,**q,a,b,c,d;

void f(){

  x=&a;

  if(a)
  	z=*q;
  else
  	w=z;
  y=&b;
  y1=z;
  NOCOALESCE(6,9);
  NOCOALESCE(6,11); // because it cannot coalesce with 9
  COALESCE(12,13);
}

int main(){

   w=&b;
   z=&c;
   q=&y;
   y=&d;
   f();
   COALESCE(6,9);
   COALESCE(6,11);
}