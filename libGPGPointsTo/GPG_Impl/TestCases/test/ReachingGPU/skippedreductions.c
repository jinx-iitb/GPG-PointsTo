int *x,*y,*z,a,b,c,d;
int **p;

void f(){

	y=&d;
	if(c)
     z=*p;
    else
     y=&c;
 
	x=z;
}

int main(){
	p=&y;
    y=&a;
    z=&b;
	f();
}