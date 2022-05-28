int **p;
int *x,*y,a,b,c;

void f(){
  x=y;
  *p=&b;
  *p=&c;
}

int main(){
  y=&a;
  p=&x;
  f();
}
