#ifndef GPU_H_
#define GPU_H_
/*
    MIT License

Copyright (c) 2020 Venkatesh, Mehul

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
#include "IndirectionList.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Twine.h"
#include "llvm/IR/GlobalVariable.h"
#include <set>
#include <string>
#include "spatial/Token/Token.h"
#include "slim/TransformIR.h"

using namespace std;
using namespace llvm;
//GLNODE  global variable
//TNODE   temporaries, local variables
//ANODE   allocation site
//UNODE   use node
enum NodeType { BASENODE, GLNODE, TNODE, ANODE, UNODE, FPNODE };

class GPUNode;

/// to store GPUNodes in order, in MayDefSets
struct GPUNodeComp {
  bool operator()(GPUNode *lhs, GPUNode *rhs) const;
};

/// to store types (in strings) in orders
struct StringComp{
  bool operator()(char*,char*) const;
};

/// @brief GPUNode abstarct class
class GPUNode {

  NodeType type;

public:
  GPUNode(NodeType t) { type = t; }

  virtual StringRef getNameOfVariable() = 0;

  virtual Indirection *getIndirectList() = 0;

  virtual Type*  getTypeofVariable()=0;

  virtual Type*  getTypeOfVariableAtIndirection(int)=0;

  static inline bool classof(GPUNode const *g) { return true; }

  NodeType getTypeID() const { return type; }

  virtual bool isItUpWardExposedVersionOfSomeVariable() { return false; }

  // virtual bool equal()=0;
};

class SpatialNode : public GPUNode {
private:
    Token* Node;
    Indirection* indirection;
    // std::pair<spatial::Token*, int> Node;

public :
    SpatialNode(spatial::Token *, Indirection *);

    StringRef getNameOfVariable();

     Indirection *getIndirectList();

     Type*  getTypeofVariable();

     Type*  getTypeOfVariableAtIndirection(int);

};

/// @brief class for Global variable GPU Node
class GlobalNode : public GPUNode {

  GlobalVariable *gv;
  Indirection *ilist;

public:
  GlobalNode(GlobalVariable *, Indirection *);

  GlobalNode(const GlobalNode &);

  StringRef getNameOfVariable();

  GlobalVariable *getGlobalVariable();

  Indirection *getIndirectList();

  static inline bool classof(GlobalNode const *gN) { return true; }

  static inline bool classof(GPUNode const *g) {

    if (g->getTypeID() == GLNODE)
      return true;
    else
      return false;
  }

  Type*  getTypeofVariable();

  Type*  getTypeOfVariableAtIndirection(int);
};

class TmpNode : public GPUNode {

    llvm::Value *value;
  StringRef name;
  StringRef funName;
  Indirection *ilist;
  bool upWardExposedVersionOfSomeVariable;
  Type *typeOfVariable;
public:
  TmpNode(StringRef, StringRef, Indirection *,Type*);

  StringRef getNameOfVariable();

  Indirection *getIndirectList();

  static inline bool classof(TmpNode const *gN) { return true; }

  static inline bool classof(GPUNode const *g) {

    if (g->getTypeID() == TNODE)
      return true;
    else
      return false;
  }

  bool isItUpWardExposedVersionOfSomeVariable() {
    return upWardExposedVersionOfSomeVariable;
  }

  Type*  getTypeofVariable();

  Type*  getTypeOfVariableAtIndirection(int);
};

class AllocationSiteNode : public GPUNode {

  StringRef name;
  Indirection *ilist;
  Type *typeOfVariable;
  StringRef uniqueName;
  int lineNo;
public:
  // brief : creates allocationsite node: allocationsite@stmtNo,fileName
  AllocationSiteNode(StringRef, long, StringRef, Indirection *);

  void  setUniqueName(StringRef,long,StringRef);

  StringRef getNameOfVariable();

  
  Indirection *getIndirectList();

  static inline bool classof(AllocationSiteNode const *gN) { return true; }

  static inline bool classof(GPUNode const *g) {

    if (g->getTypeID() == ANODE)
      return true;
    else
      return false;
  }

  void setTypeofVariable(Type*);

  Type*  getTypeofVariable();

  Type*  getTypeOfVariableAtIndirection(int);

  int getLineNo()
  {
        return lineNo;
  }
};

class UseNode : public GPUNode {

  StringRef name;
  Indirection *ilist;
  Type *typeOfVariable;
  StringRef uniqueName;

public:
  // brief : creates use node: use@
  UseNode(StringRef,long,StringRef,Indirection*);

  StringRef getNameOfVariable();

  void  setUniqueName(StringRef,long,StringRef);

  Indirection *getIndirectList();

  static inline bool classof(AllocationSiteNode const *gN) { return true; }

  static inline bool classof(GPUNode const *g) {

    if (g->getTypeID() == UNODE)
      return true;
    else
      return false;
  }

  Type*  getTypeofVariable();

  Type*  getTypeOfVariableAtIndirection(int);
};

class FPNode : public GPUNode 
{    
    llvm::Value* variable;
    Indirection *ilist;

public:
    FPNode(llvm::Value*, Indirection*);

    Value* getVariable();
    
    StringRef getNameOfVariable();

    Indirection *getIndirectList();

    Type*  getTypeofVariable();

    Type*  getTypeOfVariableAtIndirection(int);

};

class GPU;
/// to store GPUs in statement order, in GPB
struct GPUComp {
  bool operator()(GPU *lhs, GPU *rhs) const;
};

class ComposeResult{
   GPU *gpuResult;
   bool composed;
   bool postponed;
public:

  ComposeResult(GPU*,bool,bool);

  GPU* getGPUResult();
  bool isComposed();
  bool isPostponed();

};

class GPU {

  GPUNode *left;
  GPUNode *right;
  long stmtNo;
  StringRef fileName;

  //@brief deprecated
  //Type *dataType;

public:
  GPU(GPUNode *, GPUNode *, long, StringRef);

  GPU(const GPU &x);

  void print(bool=false);

  GPUNode *getSourceOfGPU();

  GPUNode *getTargetOfGPU();

  long getStmtNo();

  StringRef getFileName();

   //@brief deprecated
  //void setDataType(Type *);

   //@brief deprecated
  //Type *getDataType();

  bool isTSComp(GPU *);

  bool isSSComp(GPU *);

  GPU *composeTS(GPU *);

  GPU *composeSS(GPU *);

  string toString();

  bool isLessThan(GPU *);

  //@brief GPU (x,i)->(y,j)  returns true for i>1
  bool isGPUIndirectlyDefinesVariable();
 //@brief GPU (x,i)->(y,j),   Datatype of of Defined variable (x,i)
  Type* typeOfDefinedVariable();

 //@brief types of set of References by left side of GPU
  set<char*,StringComp> typesOfReferencesLeft();

 //@brief types of set of References by right side of GPU
  set<char*,StringComp> typesOfReferencesRight();

 //@brief union types of references left, right

  set<char*,StringComp> unionTypesOfReferencesLeftRightOfGPU();

//@brief GPU (x,i)->(y,j)  returns true for i>1 or j>1
  bool isItDereferencing();

  ComposeResult* composeGPUs(bool,GPU*,set<GPU*,GPUComp>);
//@brief is it an undesirable composition
  bool undesirableComposition(bool ,GPU *);
//@brief, c o In until fixedpoint using In and BlockedSet  
  pair<set<GPU*,GPUComp>,set<GPU*,GPUComp>> augmentedGPUReduction(set<GPU*,GPUComp> ,set<GPU*,GPUComp>);

  //@brief, types of Direct and Indirect refrences
  pair<set<char*,StringComp>,set<char*,StringComp>> typesOfDirectIndirectReferences();

  bool isDeltaTop();


    string dumpString();
};

#endif