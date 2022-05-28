#ifndef Util_H_
#define Util_H_
/*
    MIT License

Copyright (c) 2020 Venkatesh

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sub license, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "GPB.h"
#include "Partition.h"
#include "llvm/ADT/SCCIterator.h"
#include "llvm/Analysis/CallGraph.h"

#define TGRN  "\x1B[1;32m"
#define TRED  "\x1B[1;31m"
#define TNRM  "\x1B[1;0m"
#define TBLUE "\033[1;34m"

// utility class provides functions to print different analysis results
class Util {

  set<StringRef> libraryFunctions;
  vector<long>   callSites;
  set<StringRef>    testCaseFunctions;
  set<StringRef> sccFunctions;

public:
  Util();

  Util(bool);

  void print(long, set<GPU *, GPUComp>, int);

  void print(long, set<long>, int);

  void print(set<long>);

  void print(char c);

  void printSCCOrder(CallGraphNode *rootNode);

  map<StringRef, char *> createXdashForAllGlobalVariables(Module *);

  void findAllLibraryFunctionsInModule(Module *);

  bool libraryFunctionOrNot(StringRef);

  bool testCaseFunctionOrNot(StringRef);

  void print(set<StringRef>);

  void print(vector<Partition*>);

  void print(set<GPU*,GPUComp>);

  bool isEqualOrNot(set<GPU*,GPUComp>,set<GPU*,GPUComp>);

  //mayDefs sets
  void print(set<GPUNode *, GPUNodeComp>);

  void setSCCFunctions(set<StringRef>);

  set<StringRef> getSCCFunctions();

  void reSetSCCFunctions();

  bool isItPartOfSCC(StringRef fun);
  //@brief  credit to SVF::Util
  string succMsg(string);
  //@brief  credit to SVF::Util
  string failMsg(string);
  //@brief
  string needInfoMsg(string);
  //@brief 
  void debugInfoErrorMsg(Instruction &);
};

#endif