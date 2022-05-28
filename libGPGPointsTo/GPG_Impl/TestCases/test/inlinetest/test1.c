#include "../Test.h"

int **p,**q,*x,*y,a,b;

void f(){
   p=&x; INITIALGPU(6,"p,1-->x,0 [6]");
   POINTSTO(p,"x");
   POINTSTO(q,"y");
}

int main(){
    f();
    q=&y;  INITIALGPU(12,"p,1-->y,0 [12]");
    *p=&a; INITIALGPU(13,"p,2-->a,0 [13]");
    POINTSTO(p,"x,y");
    POINTSTO(q,"y");
}
