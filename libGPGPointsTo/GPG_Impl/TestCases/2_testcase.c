#include <stdio.h>

// Global variables
int *p, *q, n, b;

void f()
{
	p = &n;
	q = &b;
	n = 22;
}

void g()
{
	p = &b;
	q = &n;
	n = 67;
}

int main()
{
	b = 10;
	
	int **d;

	scanf("%d", &n);
	
	if (n % 2 == 0)
	{
		f();
	}
	else
	{
		g();
	}

	scanf("%d", &n);

	if (n % 2 == 0)
		d = &p;
	else
		d = &q;

	// relptp = {p -> n, p -> b, d -> p, d -> q, q -> n, q -> b}
	int q = *p + **d;

	printf("q = %d\n", q);

	return 0;
}
