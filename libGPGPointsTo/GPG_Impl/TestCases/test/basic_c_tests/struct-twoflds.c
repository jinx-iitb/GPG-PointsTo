/*
 * Struct with multiple fields.
 * Author: Sen Ye
 * Date: 28/04/2014
 */
//#include "aliascheck.h"
#include "../Test.h"
struct IntChar {
	int f1;
	char f2;
};

struct CharInt {
	char f1;
	int f2;
};

int main() {
	struct IntChar* pint1, *pint2;
	struct IntChar s;
	pint1 = &s;
	pint2 = &s;
	//MUSTALIAS(&pint1->f1, &pint2->f1);
	//MUSTALIAS(&pint1->f2, &pint2->f2);
	//NOALIAS(&pint1->f1, &pint2->f2);
	POINTSTO(pint1,"s");
	struct CharInt* qint1, *qint2;
	struct CharInt t;
	qint1 = &t;
	qint2 = &t;
	//MUSTALIAS(&qint1->f1, &qint2->f1);
	//MUSTALIAS(&qint1->f2, &qint2->f2);
	//NOALIAS(&qint1->f1, &qint2->f2);
    POINTSTO(qint1,"t");
	return 0;
}
