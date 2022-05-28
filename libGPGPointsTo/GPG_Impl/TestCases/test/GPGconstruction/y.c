
#include<stdio.h>

int **p;
int *x,*y,*z;
int a,b,c;

void f(){


    if(a){
   p=&y;
   x = &a;
   y = &b;
    return;
    }
   
   if(a*2){
   x=&b;
   y=&c;
  }

  p=&z;

}

int main(){


   scanf("%d",&a);
   
   p=&x;

   f();
  
   *p=&c;

   printf("%d%d",a,b);
}
