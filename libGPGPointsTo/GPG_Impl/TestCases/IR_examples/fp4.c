int **p, *x, *y ,a, b, c;
int (*f_ptr)();
int swap(){
	p = &y;
	*p = &b;
	x = &a;
	(*f_ptr)();
	return 0;
}
int main(){
	
	x = &b;
	y = &a;
	f_ptr = swap;
	swap();
	return 0;
}
