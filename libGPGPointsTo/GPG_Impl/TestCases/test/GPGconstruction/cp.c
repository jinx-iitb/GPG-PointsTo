
#include<stdio.h>

int **p,**q,*x,*y,a,b,c,d;

void f(int **s){

	*s=&b;
}

int main(){
 
   int **r,*z,e,g;

  
   
    r=&z;
    z=&e;

  

  //a=*z+**r;

  //*r=&g;

  f(&z);

  a =  *z + **r;

  z = &g;


  //printf("%d",e);*/

}
