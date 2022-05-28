/// @brief
/// @file FunctionWithGPG.h
/// @author Venkatesh

#ifndef FunctionWithGPG_H_
#define FunctionWithGPG_H_
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

#include "GPG.h"
#include "GPU.h"
#include "Util.h"
#include "Partition.h"
#include "TestCase.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/SymbolTableListTraits.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/MemorySSA.h"
#include <map>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "slim/TransformIR.h"
using namespace std;
using namespace llvm;

/// @brief class for computing and storing Generalized-Points-to-Graph(GPG) for
/// every function
class FunctionWithGPG {

  Module *m;

  Function *fun;

  set<GPU *, GPUComp> boundaryDef;

  GPG *summary;

  Transform *slim_transform;

  GPG *optimized_summary;
  /// Used in preprocessing, to reduce the number of GPUs
  map<string, vector<GPUNode *>> tempToVariableSet;

  // Used to map variables in IR to source if possible
  map<Value*, string> tempToSourceSet;

  //@brief (x,x'),(y,y'),(z,z')... soon
   map<StringRef,StringRef> globalToUpwardExposedVersion;
  
   map<StringRef,GlobalVariable*> upwardExposedToGlobalVariable;

   set<GPU*,GPUComp> queuedSet;

   set<GPU*,GPUComp> endRGWithOutBlocking;

   set<GPU*,GPUComp> endRGWithBlocking;

   map<long, list<TestCase*>> testCases;

  //@brief names of the pointers formal arguments
   vector<StringRef> formalArguments;

  //@brief Dump point-to
   bool dumpPointsTo;

  //@brief initial summary with recursive call block
   GPG *initialSummaryWithCallBlock;
   
  // -------------------------------------------- My Implementation ----------------------------//
   GPG *summary_after_updated_coalescing;
   GPG *initial_summary_with_rec_calls;
  //--------------------------------------------------------------------------------------------//

  //@brief used for maintaining return nodes
  set<GPUNode *, GPUNodeComp> returnNodes;  
  

  set<Function*> Callers;

public:
  FunctionWithGPG();

  /// @brief Construct object with Function argument
  /// @param f llvm::Function object
  FunctionWithGPG(Function *f);

  void setBoundrayDef(SymbolTableList<GlobalVariable> &,
                      map<StringRef, char *>);

  void setDumpPointsTo(bool);

  void setModule(Module *);

  void addVariableToTempMap(string, GPUNode *);

  vector<GPUNode *> getListOfNodesMappedToTemp(string);

  void preProcessFunction();

  void preProcessMallocCallocCalls(Instruction &);

  void preProcessBitCastInstruction(Instruction &);

  void preProcessLoadInstruction(Instruction &);

  void preProcessGEPInstruction(Instruction &);

  GPB *processPointerStoreInstruction(Instruction &, map<StringRef, FunctionWithGPG*> &);

  GPB *processNonPointerStoreInstruction(Instruction &);

  GPB *processNonPointerLoadInstruction(Instruction &);

  GPB *processPointsToTestFunctions(Instruction &);

  GPB *processFPCallInst(Instruction &);

  set<GPUNode*,GPUNodeComp> getReturnNodes();

  //@brief, Process Debug Value Instruction for local pointers
  GPB *processDebugValueInstruction(DbgValueInst*);

  //@brief, preprocess debug declare Instructions for local pointers
  void preProcessDebugDeclareInstruction(DbgDeclareInst*);
  //@brief, preprocess PHI instruction
  void preProcessPHIInstruction(Instruction&);
  //@brief, preprocess debug value Instruction
  void preProcessDebugValueInstruction(DbgValueInst *);
  
  set<GPU *, GPUComp> getBoundaryDef();

  void printTempToVariableSet();

  void preprocessGPUSet(map<long, GPB *>);
  
  set<GPU*, GPUComp> removeUseGPUs(set<GPU*, GPUComp>);

  //@brief summaries of callees and library functions etc info needed
  void constructGPG(map<StringRef, FunctionWithGPG *>&, Util *);

  void removeEmptyNodesInGPG();

  //@brief Deprecated
  // void performEmptyNodeAnalysisOnGPG();

  //@brief find the live  pointers at the begining of the procedure
  // Those pointers will have upwardexposed versions
 // void livenessAnalysis();

  void reachingGPUAnalysisWithOutBlocking();

  void reachingGPUAnalysisWithBlocking();

  GPG *getSummary();

  Function* getFunction();

  bool isUpwardExposed(StringRef);
  
  void setupwardExposedVersionOfGlobalVar(SymbolTableList<GlobalVariable> &,map<StringRef,char*>);

  set<GPU*,GPUComp> addingBoundaryGPUsDueToBlocking(set<GPU*,GPUComp>,set<GPU*,GPUComp>);

  void deadGPUElimination();

  void addToQueuedSet(GPU *);

  set<GPU*,GPUComp> getQueuedSet();

  //@brief sets RGOUT of RGWithblocking if withblocking_or_not is true
  //       sets RGOUT of RGWithoutBlocking if withblocking_or_not is false
  void setRGOutOfEnd(bool withblocking_or_not, set<GPU*,GPUComp>);
  //@brief get RGOUT of RGWithblocking if withblocking_or_not is true
  //       get RGOUT of RGWithoutBlocking if withblocking_or_not is false
  set<GPU*,GPUComp> getRGOutOfEnd(bool withblocking_or_not);

  //@brief Coalescing analysis
  void coalescingAnalysisInPaper();

  //@brief Coalescing analysis in Pritam Thesis

  void coalescingAnalysisInThesis();
  // ------------------------------------My implementation ----------------------------------//
  void UpdatedCoalescingAnalysis();
  vector<GPB *> get_bfs_order();
  vector<Partition *> create_partition(vector<GPB *>);
  GPG *getSummaryAfterUpdatedCoalescing();
  void ConnectParts(vector<Partition *>, map<GPB *, Partition *>);
 //----------------------------------------------------------------------------------------//

  //@brief, replace all upwardexposed by globalvariable for inlining
  set<GPU*,GPUComp> getGPUSetWithOutUpWardExposed(set<GPU*,GPUComp>);

  //@brief, perform coalescing using the partitions
  void performCoalescing(vector<Partition*>);

  //@brief, for handling recursive functions
  void handleDirectRecursion();

  //@brief, inline summary at recursive block
  void inlineAtRecursiveBlock(GPG*);

  //@brief, add points to test case
  void addPointsToTestCase(StringRef,long,StringRef,StringRef,bool);
  //@brief, add SSA points-to test case
  void addSSAPointsToTestCase(StringRef,long,bool,bool);
  //@brief, process GPU Test cases
  void processGPUTestCaseFunctions(Instruction&);
 //@brief, process Coalesce Test case
  void processCoalesceTestCaseFunctions(Instruction &I);
  //@brief, add initial GPU Test case
  void addInitialGPUTestCase(StringRef,long,StringRef,long);
  //@brief, add intermediate GPUs Test case
  void addInterGPUTestCase(StringRef,long,StringRef,long);
  //@brief, add Coalesce Test case
  void addCoalesceTestCase(StringRef,long,long,long,bool);
  //@brief, Validate Initial GPG Testcases
  void ValidateInitialGPUTests();
  //@brief, Validate PointsTo Testcases
  void ValidatePointsToTests();
  //@brief, Validate Coalesce Testcases
  void ValidateCoalesceTests();    

  void findPointsToPairs(map<long, std::pair<set<GPU*, GPUComp>,std::string>>&);

  //@brief,get Names of pointer formal arguments
  vector<StringRef> getFormalArgumentNames();

  GPB* processPointerArgumentsInFunctionCall(Instruction&,vector<StringRef>);

  void preprocessPointerReturnInstruction(ReturnInst*);
  void processCallReturn(Instruction&,set<GPUNode*,GPUNodeComp>);

  GPB* handleTestCaseFunctions(Instruction &);

  void ConstructGPGForFPCall(StringRef, map<StringRef, FunctionWithGPG *> &);
  
  void ReplaceFPUseNodeWithSummary(map<StringRef, FunctionWithGPG *> &);

  void handleRecursion(int, bool);

  void findCallers();

  set<Function*> getCallers();

  void inliningCallsInSCC(map<StringRef, FunctionWithGPG*>&);

  void removeUnreachableNodes();

  void setInitialSummary();

    GPB *processPointerLoadInstruction(Instruction &instruction);

    void preprocessCallInstruction(Instruction &I);

    GPB *processAllocaInstruction(Instruction &I);

    GPB *generateGPBforDebugDeclareInstruction(DbgDeclareInst &pInst);

    GPB *generateGPBforDebugValueInstruction(DbgValueInst &inst);

    GPB *processPointerPhiInstruction(PHINode &node);
};
#endif
