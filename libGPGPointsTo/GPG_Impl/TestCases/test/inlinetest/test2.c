
int *p,x,y;

void f(){
   p=&x;
}

int main(){
    f();
    p=&y;
    f();
}