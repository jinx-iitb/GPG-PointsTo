/*
 * Alias due to lack of path-sensitivity.
 * Author: Sen Ye
 * Date: 06/09/2013
 */
//#include "aliascheck.h"
#include "../Test.h"
int main()
{
	int *p, *q;
	int a, b, c;
	if (c) {
		p = &a;
		q = &b;
	}
	else {
		p = &b;
		q = &c;
	}

	*p=20;
	*q=30;
	//MAYALIAS(p,q);
	POINTSTO(p,"a,b");
	POINTSTO(q,"c,b");
	return 0;
}
