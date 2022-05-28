
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

  **p=20;

  p=&y;
  z=&b;

  f();

  **p=30;


}
