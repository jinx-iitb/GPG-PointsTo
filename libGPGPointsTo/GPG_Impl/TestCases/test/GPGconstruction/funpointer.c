#include<stdio.h>
void f(){

}

void g(){
  f();
}

void h(){
   f();
   g();
}

void (*fp)();

int main(){
   h();
   f();

  fp=g;

  (*fp)();

  printf("hello");

}
