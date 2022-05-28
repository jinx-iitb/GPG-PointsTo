/*
 * Context-insensitive.
 * Author: Sen Ye
 * Date: 10/10/2013
 */

//#include "aliascheck.h"

#include "../Test.h"
int global,t;
int *p_global;

void foo() {
	p_global = &global;
}

int main() {
	int *p_local,*q,t;
	p_local = &global;
	*p_local = 40;
	foo();
	POINTSTO(p_global,"global");
	//MAYALIAS(p_local, p_global);
	//p_local = p_global;
	*p_local = 30;
	POINTSTO(p_local,"global");
	p_local = &t;
    q = &t;
	POINTSTO(p_local,"t");
	POINTSTO(p_local,"global");
	POINTSTO(q,"global");
	return 0;
}
