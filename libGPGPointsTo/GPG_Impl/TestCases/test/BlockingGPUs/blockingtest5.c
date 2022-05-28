int **p;
int *x,*y,*z,*w;
int a,b;

void f(){
	
	y=&a;
	*p=&b;
	z=y;
    w=*p;
}

int main(){
	p=&z;

    f();
}