#include<stdio.h>

int ***x, **y, *z,*p, a, b;

void foo()
{
	int *m;

	**x = z;
	p = **x;

}

int main()
{
	//**x = z;
   foo();
}
