int *p,*q,**w,x,y,z;

void g(){

  while(y){
   //p=&x;
    w=&p;
   *q=20;
   //**w=20;
  }

}
void f(){
   w=&p;
   p=&y;
   q=&z;
  if(x){
   g();
  }
  else *p=40;
}

int main(){
  if(y){
    q=&y;
    f();
    *p=20;
  } 
 // w=&p;
 // g();
}