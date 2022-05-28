#ifndef GPB_H_
#define GPB_H_
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
#include "GPU.h"
#include <set>

using namespace std;

class GPB;

/// to store GPBs in sorted order, in GPG
struct GPBComp {
  bool operator()(GPB *lhs, GPB *rhs) const;
};


/// @brief class for representing Generalized Points-to Block
class GPB {



    long gpbNo;

  bool isInlined;

  set<GPU *, GPUComp> GPUSet;
  set<GPB *, GPBComp> succs;
  set<GPB *, GPBComp> preds;

  /// @brief to set the unique Generalized Points-to Block Number
  static long currentGpbNo;
  /// @brief used to represent mayDefSet
  set<GPUNode *, GPUNodeComp> mayDefSet;
 /// useful for recursion
  bool recursiveCallBlock;

 /// for coalescing
  set<GPU*,GPUComp>  reachingGPUBlockingIn;
  set<GPU*,GPUComp>  reachingGPUBlockingOut;
  
  // --------------------------------------- My Implementation ----------------------------------//
  map<GPB *, bool> Col;
  set<GPB *, GPBComp> descendants; // succ+
  set<GPB *, GPBComp> ancestors;   // pred+
  // -------------------------------------------------------------------------------------------//


public:
  GPB();
  GPB(set<GPU *, GPUComp>);
  GPB(GPU *gpu);
  GPB(long);

  //Only called from deep copy

  void addSuccessor(GPB *);

  void addPredecessor(GPB *);

  void removeSuccessor(GPB *);

  void removePredecessor(GPB *);

  void removeAllSuccessors();

  void removeAllPredecessors();

   //@brief Deprecated, AugmentGPUreduction defined
  //set<GPU *, GPUComp> computeGPUReduction(set<GPU *, GPUComp>);

  long getGPBNo();

  set<GPU *, GPUComp> getGPUSet();

  void setGPUSet(set<GPU *, GPUComp>);

  set<GPB *, GPBComp> getAllSuccessors();

  set<GPB *, GPBComp> getAllPredecessors();


  void setAllSuccessors(set<GPB*,GPBComp>);

  void setisInlined(bool);
  
  bool getisInlined();

  void setAllPredecessors(set<GPB*,GPBComp>);

  void print();

  string toString();

  void setAsRecursiveCallBlock(bool=true);
  
  bool isItRecursiveCallBlock();
  ///@brief to check whether GPB block is empty or not.
  bool isEmpty();
  ///@brief check empty and not a start or end node
  // bool  isEmptyAndCanbeRemoved();

  /// @brief check whether multiple sources are defined with same statement id.(and GPUs with indirect definitions)
  void checkAndAddElmntToMayDefSet(set<GPU *, GPUComp>, set<GPU*,GPUComp> );
  ///@brief add to maydefset, if multiple sources are there
  void addElmntToMayDefSet(GPUNode *);
  ///@brief getMaydef Set, 
  set<GPUNode*,GPUNodeComp> getMayDefSet();
  ///@brief copy to new block during inlining, coalesceing
  void setMayDefSet(set<GPUNode*,GPUNodeComp>);

  ///@brief kill set by differentating strong, weak update
  set<GPU*,GPUComp> computeKillSet(set<GPU *, GPUComp>, set<GPU *, GPUComp>);
  ///@brief In-Kill
  set<GPU *, GPUComp> computeInMinusKill(set<GPU *, GPUComp>, set<GPU *, GPUComp>);

  // @brief find the set of GPUs, which indirectly defines variables from the given GPUs at this block
  set<GPU*,GPUComp> findGPUsHavingIndirectDefinitions(set<GPU*,GPUComp>);
  
  // @brief get set of types in strings form, to allow union and intersection
  set<char*,StringComp> getTypesOfSetOfDefinitions(set<GPU*,GPUComp>);

  // @brief get set of references
  set<char*,StringComp> getTypesOfSetOfReferences(set<GPU*,GPUComp>);

  //@brief, is it no common dependencies in def,ref with same type? yes true
  bool  isNoDependenciesInDefRefTypesCommon(set<GPU*,GPUComp> ,set<GPU*,GPUComp>);

  //@brief, find all blocking gpus
  set<GPU*,GPUComp> getBlockedGPUs(set<GPU*,GPUComp> ,set<GPU*,GPUComp> );

  //@brief, compute augmented GPU reduction
  pair<set<GPU*,GPUComp>,set<GPU*,GPUComp>> augmentedGPUReductionOverBlock(set<GPU*,GPUComp>,set<GPU*,GPUComp>);

  //@brief, is it dependency between GPUs given and GPus in block, useful in coalsecing
  bool isDependent(set<GPU*,GPUComp>);

  //@brief, is it dependency between GPUs given and GPus in block, useful in coalsecing
  bool isDependentByMehul(set<GPU*,GPUComp>);


  //@brief, is it having GPU with dereferencing operation
  bool isItHasDereferencingGPU(set<GPU*,GPUComp>);

  //@brief, computegpuFlow

  set<GPU*,GPUComp> computeGPUFlow(set<GPU*,GPUComp>,bool);

 //@brief , coalesce

  bool coalesceOrNot(bool,bool,set<GPU*,GPUComp>);

//@brief, returns true if its predecessor contains startnode
 bool isItPredOfNode(GPB*);
//@brief, returns true if its successor contains End or Exit node
 bool isItSuccOfNode(GPB*);

 pair<set<char*,StringComp>,set<char*,StringComp>> getTypesOfSetOfDirectIndirectDefs(set<GPU*,GPUComp>);

 pair<set<char*,StringComp>,set<char*,StringComp>> getTypesOfSetOfDirectIndirectRefs(set<GPU*,GPUComp>);

 void setRGBlockingIn(set<GPU*,GPUComp>);

 set<GPU*,GPUComp> getRGBlockingIn();

 void setRGBlockingOut(set<GPU*,GPUComp>);

 set<GPU*,GPUComp> getRGBlockingOut();
 
 //------------------------------ My Implementation --------------------------------------------//
 void setColmap(GPB *, bool);
 map<GPB *, bool> &getColmap();
 void printColmap();
 bool DDep(GPB *);
 void setDescendants();
 void setAncestors();
 set<GPB*, GPBComp> getDescendants();
 set<GPB*, GPBComp> getAncestors();
 set<GPB*, GPBComp> findExternalPreds(set<GPB*, GPBComp>);
 set<GPB*, GPBComp> findExternalSuccs(set<GPB*, GPBComp>);
 //--------------------------------------------------------------------------------------------//



    string dumpString();
};

#endif
