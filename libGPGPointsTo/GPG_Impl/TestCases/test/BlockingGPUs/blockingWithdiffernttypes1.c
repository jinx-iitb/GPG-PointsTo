int **p;
int *x,*y;
char *z,*w;
int a,b;
char c,d;

void f(){

	w=&c;
	y=&a;
	*p=&b;
	z=w;
    x=y;
}

int main(){
	p=&x;
   
    f();
}