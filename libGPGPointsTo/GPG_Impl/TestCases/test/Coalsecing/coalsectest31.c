int *x,*y,*w,*z,**p,***q,a,b,c,**r;

void f(){
	x=&a;
	if(a) {
	  *p=w;
	   if(b)
	   	q=&r;
	}

    y=&b;
}


int main(){
	p=&y;
	w=&c;
	f();
}