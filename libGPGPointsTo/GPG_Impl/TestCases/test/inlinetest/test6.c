int *p,*q,x,y;

void g(){
  p=&x;
}
void f(){
   g();
}

int main(){
    q=&y;
    f();
    *p=20;
}