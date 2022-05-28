int *x,*y,**p,a,b,c;


void f(){
	x=&a;
	if(a)
	  *p=&b;
	else
	   x=&c;
    y=&c;
}

int main(){

	p=&y;
	f();
}
