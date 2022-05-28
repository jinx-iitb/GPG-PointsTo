int **p,**q;
int *x,*y;
int a,b;

main(){

  p=&x;

  if(a>10)
    *p=&b;
  else
    *p=&a;

  //p=&y;

  *p=&b;

}
