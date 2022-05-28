#include "../Test.h"
int *x,*y,a,b;


main(){
	x=&a;
	y=&b;
	*x=20;
    COALESCE(6,7);
    NOCOALESCE(6,7);
}