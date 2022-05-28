#include<stdio.h>
int **p,**q;
int *x,*y;
int a,b,c,d;
int main(){

 int e;
  p=&x;
  q=&y;
  
  d=40;

  if(b){
   *q=&a;
   x=&b;
  }
  else{
   *p=&b;
   y=&a;
  }

  x=y;

  a=b;
  
 **p=30;

  *x=40;


// Pending use nodes
//   d=*x;  
  // *x=*y;  

  // c=*x+5;

  // e=**p;  //work on progress

   //**p=**q;
  printf("%d",e);
}
