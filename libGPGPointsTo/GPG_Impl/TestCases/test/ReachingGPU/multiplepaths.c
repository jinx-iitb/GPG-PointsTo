
int *x,*y,*z,a,b,c;

void f(){
	
	if(c)
	z=&b;
	else
	y=&c;


	x=z;
}

int main(){
	
    z=&a;
	f();
}