int *p,*q,x,y,z;

void g(){

  while(y){
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
  while(y){
    q=&y;
    p=&z;
    f();
    *p=20;
  }
}