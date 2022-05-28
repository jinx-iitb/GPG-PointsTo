
#include<stdio.h>
int *x,*y,*z;
int a,b;


void f(){
   x=y;
}

int main(){

  int g;

   y=&a;

   f();

   *x=20;

  y=&b;

  f();

  *x=30;


}



