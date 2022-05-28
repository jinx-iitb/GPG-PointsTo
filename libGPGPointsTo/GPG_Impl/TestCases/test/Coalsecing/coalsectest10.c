int *x,*y,**z,**w,**p,a,b,*c,d,e;

void f(){

  x=&a;

  if(a){
  	y=&b;
  	*z=&d;
  }
  else{
  	z=&c;
  	*w=&e;
  }
  
  p=&x;
}

int main(){

  z=&x;
  w=&y;
  x=&b;

  f();
}