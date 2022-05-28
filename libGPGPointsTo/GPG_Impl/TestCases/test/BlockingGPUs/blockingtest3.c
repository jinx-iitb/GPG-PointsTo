int **p;
int *x,*y,*z;
int a,b;

void f(){
	
	*p=&a;
	 y=&b;
	z=*p;
}

int main(){
	p=&y;

    f();
}