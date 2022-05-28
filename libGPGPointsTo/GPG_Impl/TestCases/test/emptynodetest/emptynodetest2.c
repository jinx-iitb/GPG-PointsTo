
int *x,a,b,c;

void f(){

  if(b)
   a=b;
  else
   x=&a;

  if(a)
   a=b;
  else
   x=&b;

}

int main(){

   x=&c;
   f();

}

