
int **p;
int *x,*y,*z;
int a,b;

void f(){
	
	x=&a;
	*p=&b;
	z=y;
}

int main(){
	p=&y;
	y=&a;

    f();
}