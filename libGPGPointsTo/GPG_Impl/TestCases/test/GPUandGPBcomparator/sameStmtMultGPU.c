int **p,**q;
int *x,*y;
int a,b,c;

int main(){

   x=&b;
   y=&c;

   
  if(a>10)
    p=&y;
  else
    p=&x;

  *p=&a;

}
