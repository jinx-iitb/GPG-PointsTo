int **p;
int *x,*y,*z;
int a,b;

void f(){
	
	y=&a;
	*p=&b;
	z=y;
}

int main(){
	p=&x;

    f();
}