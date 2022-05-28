#include <set>
#include <map>
#include <iostream>
#include <vector>

// Macros Defined

#define FOR_EACH_ELEMENT(s) for (itr = s.begin(); itr != s.end(); itr++)
#define FOR_EACH_ELEMENT(s, itr) for (itr = s.begin(); itr != s.end(); itr++)
#define FOR_EACH_BASICBLOCK(function) for (auto &BB : function)
#define FOR_EACH_INSTRUCTION(basicblock) for (auto &I : basicblock)
#define FOR_EACH_ELEMENT_MAP(m, itr) for (itr = m.begin(); itr != m.end(); itr++)
#define FOR_EACH_ELEMENT_WITHITR(s, itr) for (itr = s.begin(); itr != s.end(); itr++)
#define FOR_EACH_ELEMENT_OF_VECTOR(v) for (int i = 0; i < v.size(); i++)