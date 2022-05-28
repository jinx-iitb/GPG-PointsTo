int *p,*q,x,y;

void f(){
   p=&x;
   *q=30;
}

int main(){
    q=&y;
    f();
    *p=20;
}