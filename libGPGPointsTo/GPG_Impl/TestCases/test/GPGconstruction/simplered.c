
int *x,*y;
int a,b;
int **p;
int main(){
   x=&a;

   y=x;

   p=&x;

  *p=&b;

}
