int *x,*y,*z,*w,**p,a,b,c,d,e;

void f(){

  x=&a;

  if(a){
    *p=z;
  	y=&b;
  }
  else{
  	z=&c;
  	y=&e;
  }
  
  p=&x;
}

int main(){
  p=&y;
  z=&d;
  f();
}