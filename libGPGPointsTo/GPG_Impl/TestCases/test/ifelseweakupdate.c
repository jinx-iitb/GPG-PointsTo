
#include "Test.h"
int **p,**q;
int *x,*y;
int a,b,c;

int main(){

   x=&b;
   y=&c;

  if(a>10)
    p=&x;
  else
    p=&y;

  *p=&a;
   POINTSTO(x,"a,b");
}
