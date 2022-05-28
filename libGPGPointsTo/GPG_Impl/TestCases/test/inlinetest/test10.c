int *p,*q,x,y,z;

void g(){

  if(y){
   p=&x;
   *q=20;
  }

}
void f(){
  if(x){
   g();
  }
  else *p=40;
}

int main(){
  p=&z;
  if(y){
    q=&y;
    f();
    *p=20;
  }
  *p=30;
}