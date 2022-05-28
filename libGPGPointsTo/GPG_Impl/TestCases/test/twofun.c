
#include "Test.h"
int **p,**q;
int *x,*y,*z;
int  a,b;

void f(){

 *p=z;
}

int main(){

  p=&x;
  z=&a;

  f();

  POINTSTO(p,"x");
  **p=20;

  p=&y;
  z=&b;

  f();

  POINTSTO(p,"y");
  **p=30;


}