/*
 * Simple alias check
 * Author: Sen Ye
 * Date: 06/09/2013
 */
//#include "aliascheck.h"
#include "../Test.h"
int main()
{
	int a,b,*c,*d;
	c = &a;
	d = &a;
	//MUSTALIAS(c,d);
	POINTSTO(c,"a");
	POINTSTO(d,"b");
	*c=30;
	c = &b;
	POINTSTO(c,"b");
	POINTSTO(d,"a");
	// In LLVM, every declared variable is address-taken 
	// accessed via pointers through loads/stores
	// c here is loaded from the same memory on LLVM's partial SSA form
	//MAYALIAS(c,d);
	//NOALIAS(&b,d);
	return 0;
}
