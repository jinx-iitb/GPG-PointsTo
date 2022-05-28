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
    q=&y;
    p=&z;
    f();
    *p=20;
}