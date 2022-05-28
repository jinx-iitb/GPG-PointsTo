//without any derefences
#include "../Test.h"
int *x,*y,*z,*w,**p,a,b,c,d,e;

void f(){

  x=&a;

  if(a){
  	y=&b;
  	w=z;
  }
  else{
  	z=&c;
  	y=&e;
  }
  
  p=&x;

  COALESCE(7,14);
  COALESCE(10,14);
}

int main(){

  z=&d;
  f();
}