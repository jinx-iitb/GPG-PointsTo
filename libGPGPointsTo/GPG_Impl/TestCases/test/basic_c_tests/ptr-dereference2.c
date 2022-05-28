//#include "aliascheck.h"
#include "../Test.h"

int main(){

  int **a, *b, *x ,c;
  c = 10;
  a = &b;
  b = &c;
  POINTSTO(a,"c");
  x = *a;
  POINTSTO(x,"c");
  int y = *x;
  //MUSTALIAS(x,&c);
  //MUSTALIAS(x,b);
  return 0;
}
