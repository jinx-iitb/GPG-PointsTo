/*
 * Alias due to context-insensitive
 * Author: Sen Ye
 * Date: 06/09/2013
 */
//#include "aliascheck.h"
#include "../Test.h"
void foo(int *m, int *n)
{
	//MAYALIAS(m,n);
}

int main()
{
	int *p, *q;
	int a,b,c,d;
	if (a) {
		p = &a;
		q = &b;
		//a=20;
		c=40;
		//POINTSTO(p,"a");
		//POINTSTO(q,"a");
		//foo(p,q);
	}
	else {
		p = &b;
		q = &a;
		//a=30;
		c=*q;
		//foo(p,q);
	}

	POINTSTO(p,"a,b");
	POINTSTO(q,"a,b");
	*q=a+c;
   /* if (a) {
		p = &d;
		a=20;
		c=40;
		POINTSTO(p,"a");
		POINTSTO(q,"a");
		foo(p,q);
	}
	else {
		q = &d;
		a=30;
		c=*q;
		foo(p,q);
	}

    *p=c;
    *q=a;*/
	return 0;
}
