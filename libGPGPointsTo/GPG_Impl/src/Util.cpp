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
#include "Util.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Support/raw_ostream.h"

#define FOR_EACH_ELEMENT(s, itr) for (itr = s.begin(); itr != s.end(); itr++)

Util::Util(bool testCase) {
  testCaseFunctions.insert("INITIALGPU");
  testCaseFunctions.insert("INTERMEDIATEGPU");
  testCaseFunctions.insert("POINTSTO");
  testCaseFunctions.insert("NOTPOINTSTO");
  testCaseFunctions.insert("COALESCE");
  testCaseFunctions.insert("NOCOALESCE");
}

Util::Util(){
  testCaseFunctions.insert("INITIALGPU");
  testCaseFunctions.insert("INTERMEDIATEGPU");
  testCaseFunctions.insert("POINTSTO");
  testCaseFunctions.insert("NOTPOINTSTO");
  testCaseFunctions.insert("COALESCE");
  testCaseFunctions.insert("NOCOALESCE");
}

//  in_gen_kill_out = 1 for in
//  in_gen_kill_out = 2 for gen
//  in_gen_kill_out = 3 for in-kill
//  in_gen_kill_out = 4 for out
//  in_gen_kill_out = 5 for blocked
//  in_gen_kill_out = 6 for kill
//  in_gen_kill_out = 7 for boundayAddedduetoBlocked   
//  in_gen_kill_out = 8 for killedunionBlocked            

void Util::print(long gpbNo, set<GPU *, GPUComp> GPUSet, int in_gen_kill_out_blocked) {

  set<GPU *, GPUComp>::iterator itr,itr1;

  if (in_gen_kill_out_blocked == 1)
    outs() << "In ";
  else if (in_gen_kill_out_blocked== 2)
    outs() << "Gen ";
  else if (in_gen_kill_out_blocked== 3)
    outs() << " In-Kill ";
  else if (in_gen_kill_out_blocked== 4)
    outs() << "Out ";
  else if (in_gen_kill_out_blocked==5)
    outs()<<"Blocked ";
  else if (in_gen_kill_out_blocked==6)
    outs()<<"Killed ";
  else if (in_gen_kill_out_blocked==7)
    outs()<<"BoundarySetduetoBlocking ";
  else if(in_gen_kill_out_blocked==8)
    outs()<<"Killed U Blocked ";

  if(in_gen_kill_out_blocked > 0)
    outs() << " GPB Block: " << gpbNo << "\n";

  int k=1, numElem;

  numElem = GPUSet.size();

  FOR_EACH_ELEMENT(GPUSet, itr) {
      (*itr)->print(true);
    if(in_gen_kill_out_blocked > 0)
      outs() << "\n";
    else if(in_gen_kill_out_blocked==-1 && (k<numElem))
      outs()<<"\n\t\t\t";
    else if(in_gen_kill_out_blocked==-4 && (k<numElem))
      outs()<<"\n\t\t\t\t\t\t";
    k++;
  }
}

void Util::print(long gpbNo, set<long> gpbNoSet, int in_gen_kill_out) {

  set<long>::iterator itr;

  if (in_gen_kill_out == 1)
    outs() << "In ";
  else if (in_gen_kill_out == 2)
    outs() << "Gen ";
  else if (in_gen_kill_out == 3)
    outs() << " Out-Kill ";
  else if (in_gen_kill_out == 4)
    outs() << "Out ";

  if(in_gen_kill_out > 0)
  outs() << " GPB Block: " << gpbNo << "\n";

   int k=1, numElem;

  numElem = gpbNoSet.size();


  FOR_EACH_ELEMENT(gpbNoSet, itr) {

    outs() << ((k==1)?" ":",")<<*itr;
    //       outs()<<"\n";

    k++;
  }
 // outs() << "\n";
}

void Util::print(set<long> s) {

  for (long elem : s)
    outs() << elem << " ";

  outs() << "\n";
}

void Util::printSCCOrder(CallGraphNode *rootNode) {

  unsigned sccNum = 0;

  outs() << "SCCs, Call graph of the program in Bottom-up order(Postorder):";

  for (scc_iterator<CallGraphNode *> SCCI = scc_begin(rootNode);
       SCCI != scc_end(rootNode); ++SCCI) {

    const std::vector<CallGraphNode *> &nextSCC = *SCCI;

    outs() << "\nSCC #" << ++sccNum << " : ";

    int i = 0;

    std::vector<CallGraphNode *>::const_iterator I;

    for (I = nextSCC.begin(); I != nextSCC.end(); ++I, i++)

      if ((*I)->getFunction()) {
        outs() << (i ? "->" : "");
        outs() << (*I)->getFunction()->getName();
      } else
        outs() << "Indirect CallGraph node ";

    if (nextSCC.size() == 1 && SCCI.hasLoop())
      outs() << " Direct recursion";
    else if (nextSCC.size() > 1 && SCCI.hasLoop())
      outs() << " Indirect recursion. ";
  }

  outs() << "\n";
}

map<StringRef, char *> Util::createXdashForAllGlobalVariables(Module *module) {

  map<StringRef, char *> gToB;

  for (auto &Global : module->getGlobalList()) {

    StringRef sR = Global.getName();

    char *p = new char[sR.size() + 2];

    int i = 0;

    for (; i < sR.size(); i++)
      p[i] = sR[i];

    p[i] = '\'';

    p[i + 1] = '\0';

    gToB[sR] = p;

    // outs()<<"test:"<<gToB[sR]<<"\n";
  }

  return gToB;
}

void Util::findAllLibraryFunctionsInModule(Module *module) {

  TargetLibraryInfo *TLI;
  LibFunc inbuilt_func;

  for (auto &function : *module) {
    // If it is one of the known library functions, return true
    if (TLI->getLibFunc(function, inbuilt_func))
      libraryFunctions.insert(function.getFunction().getName());
  }
}

bool Util::libraryFunctionOrNot(StringRef funName) {

  if (libraryFunctions.count(funName) == 0)
    return false;
  else
    return true;
}

bool Util::testCaseFunctionOrNot(StringRef funName){

  if(testCaseFunctions.count(funName) == 0)
     return false;
  else
     return true;
}

void Util::print(set<StringRef> setNames) {

    set<StringRef>::iterator sItr;
    outs()<<"Types set: ";

    for(sItr = setNames.begin(); sItr!=setNames.end();sItr++)
           outs()<<*sItr << " ";
         outs()<<"\n";
}

void Util::print(char c){

   for(int i=0;i<100;i++)
       outs()<<c;
  
}

void Util::print(vector<Partition*> partitions){

   for(auto vItr=partitions.begin();vItr!=partitions.end();vItr++) 
             (*vItr)->print();
}


void Util::print(set<GPU*,GPUComp> gpuSet){

    for(auto gpuItr = gpuSet.begin();gpuItr!=gpuSet.end();gpuItr++)
                (*gpuItr)->print();

}


void Util::print(set<GPUNode *, GPUNodeComp> mayDefs){

    for(auto mItr= mayDefs.begin();mItr!=mayDefs.end();mItr++)
              
               if(isa<GlobalNode>(*mItr)){
                
                 outs() << "( " << (*mItr)->getNameOfVariable() << " , ";

                 (*mItr)->getIndirectList()->print();

                 outs() << ") \n";

               }

}

string Util::succMsg(string msg){

  return TGRN + msg + TNRM;
}

string Util::failMsg(string msg){

  return TRED + msg + TNRM;
}

string Util::needInfoMsg(string msg){
   return TBLUE + msg + TNRM;
}

bool Util::isEqualOrNot(set<GPU*,GPUComp> s1,set<GPU*,GPUComp> s2){

   for(auto fSetItr=s1.begin();fSetItr!=s1.end();fSetItr++){
         if(s2.find(*fSetItr)==s2.end())
               return false;
   }
   
   for(auto sSetItr=s2.begin();sSetItr!=s2.end();sSetItr++){
         if(s1.find(*sSetItr)==s1.end())
               return false;
   }
    
   return true; 
}

void Util::setSCCFunctions(set<StringRef> scc){

  sccFunctions = scc;
}

set<StringRef> Util::getSCCFunctions()
{
    return sccFunctions;
}

void Util::reSetSCCFunctions(){

  sccFunctions.clear();
}

bool Util::isItPartOfSCC(StringRef fun){

   if(sccFunctions.count(fun)==0)
      return false;
   else
      return true;
}

void Util::debugInfoErrorMsg(Instruction &inst){

   BasicBlock *bb = inst.getParent();
   
   if(bb!=NULL){
      Function *f = bb->getParent();
      if(f!=NULL)
        errs()<<"Debug information is not available for instruction "<<inst<<"in function"<<f->getName()<<"\n";
   }

}