#include <stdio.h>
int *x,*y,*w,**p,**q,a,b,c;
void f(){
	x = &a;
	switch(a){
		case 1:
			x = &b;
			break;
		case 2:
			x = &c;
			break;
		case 3:
			y = &a;
			break;
		case 5:
			break;
		default :
			y = &b;
			break;
	}
	*p = w;
    // **p = 10;	
}
int main(){
	p = &y;
	w = &c;
	
	f();
	int aa =*x;
	return 0;
}
