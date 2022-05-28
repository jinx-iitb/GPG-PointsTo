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
   *q=&b;
   x=&a;
  }
  else{
   *p=&b;
   y=&d;
  }

 // x=y;
 // a=b;
 //**p=30;
 // *x=40;
// Pending use nodes
//  d=*x;  
 *x=30;  
 c=*y;
 a=c;
 c=*x+5;
 //  a = b+ c;
 c=**p;  //work on progress
 **p=**q;
  //printf("%d",e);
}
