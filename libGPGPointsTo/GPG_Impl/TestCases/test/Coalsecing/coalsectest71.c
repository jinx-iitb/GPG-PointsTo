#include "../Test.h"

int *x,*y,*z,*w,**p,a,b,c;

void f(){
  x=&a;
  if(a){

   *p=w;
      if(b)
       goto xyz;

  }
 else{
    xyz: z=y;
  }

 p=&x;
 NOCOALESCE(9,15);
}

int main(int argc){
  p=&y;
  w=&b;
  y=&c;
  z=&a;
  a=argc;
  b=argc-1;
  f();
  COALESCE(9,15);
}
