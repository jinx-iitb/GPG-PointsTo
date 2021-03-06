/*
 * Alias due to lack of context-sensitivity.
 * Author: Sen Ye
 * Date: 06/09/2013
 */
//#include "aliascheck.h"

#include "../Test.h"
void foo(int *m, int *n)
{
	//MAYALIAS(m,n);
	int x, y;
	x = *n;
	y = *m;
	*m = x;
	*n = y;
}

int main()
{
	int *p, *q;
	int a, b, c;
	if (c) {
		p = &a;
		q = &b;
		foo(p,q);
		//POINTSTO(p,"a");
	}
	else {
		p = &b;
		q = &c;
		foo(p,q);
	}
	POINTSTO(p,"a,b");
	POINTSTO(p,"b");
	POINTSTO(q,"b,c");
	return 0;
}
