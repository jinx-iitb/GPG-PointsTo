int *x,*y,**p,a,b,c;

void f(){
	x=&a;
	*p=&c;
	y=&b;
}


main(){
	p=&x;
	f();
}