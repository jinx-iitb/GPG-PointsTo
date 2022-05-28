int **p;
int *x,*y,a,b,c;

void f(){
  x=y;
  *p=&b;
  *p=&c;
}

int main(){
 if(c)
  p=&x;
 else
  p=&y;
  f();
}