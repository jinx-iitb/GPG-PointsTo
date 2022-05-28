int *x,*y,*z,*w,**p,**q,a,b,c,d,e;

void f(){

  x=&a;

  if(a){
    *p=z;
  	y=&b;
  }
  else{
  	z=&c;

    if(b){
     *q=&e;
      z=&d;
    }
    else{
      y=&b;
      x=&c;
    }
  	y=&e;
  }
  
  p=&x;
}

int main(){
  p=&y;
  q=&w;
  z=&d;
  f();
}