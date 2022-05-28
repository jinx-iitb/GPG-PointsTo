#include "../Test.h"

int *p,*q,x,y;

void g(){

  if(y){
   p=&x;
   *q=20;
  }
  else{
    q=&y;
    *p=30;
  }

}
void f(){
   g();
   *p=40;
}

int main(){
    p=&y;
    q=&y;
    f();
    POINTSTO(p,"x,y");
    *p=20;
    POINTSTO(p,"x");
}