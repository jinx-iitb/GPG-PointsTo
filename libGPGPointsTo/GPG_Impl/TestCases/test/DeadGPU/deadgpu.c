int *x,*y,*z;
int a,b,c;

void f(){

	x=&b;
	y=&b;
    z=&b;
    y=&c;
}
int main(){
	y=&b;
	x=&a;
	f();
	z=&c;
}