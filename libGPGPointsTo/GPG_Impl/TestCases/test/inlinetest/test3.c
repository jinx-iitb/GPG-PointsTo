int *p,*q,x,y;

void f(){
   p=&x;
}

int main(){
    q=&y;
    f();
    p=&y;
}