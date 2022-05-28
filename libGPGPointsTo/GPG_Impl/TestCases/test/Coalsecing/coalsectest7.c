
#include "../Test.h"
int *x,*y,*z,*w,**p,a,b,c;

int main(int argc){
  
  w=&b;
  x=&a;

  a=argc;
  b=a-5;
  if(a){

   *p=w;
      if(b)
       goto xyz;

  }
 else{
    xyz: z=y;
  }

 p=&x;

 COALESCE(7,8);
 NOCOALESCE(14,20);

}
