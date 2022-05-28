#ifndef GPG_H_
#define GPG_H_
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
#include <stack>
#include <vector>
#include <queue>

class GPG {

  GPB *entryNode;

  GPB *exitNode;

  set<GPB *, GPBComp> GPBSet;

  /// GPBs map
  map<long, GPB *> GPBsMap;

  /// adjacency list
  map<long, set<long>> edgesOut;

  /// reverse adjacency list
  map<long, set<long>> edgesIn;

  ///set of blocks with recursive calls
  set<long> recursiveCallBlocks;

  /// @brief blocks with recursive calls to functions 
  map<long,StringRef> recursiveCallBlockFunction;

public:
  GPG();

  void setEntryNode(GPB *);

  // For starting forward analysis
  GPB *getEntryNode();

  // For starting backward analysis
  GPB *getExitNode();

  void setExitNode(GPB *);

  void insertGPB(GPB *);

  void removeGPB(GPB *);

  void addSuccessortoBB(long, GPB *);

  void addPredecessortoBB(long, GPB *);

  void removeSuccessorOfBB(long, GPB *);

  void removeAllSuccessorsOfBB(long);

  void removeAllPredecessorsOfBB(long);

  void removePredecessorOfBB(long, GPB *);

  // print
  void print();

  // dump for testing purposes
  void dump(string);

  // print to dot file
  void printToDot(string);

  // printing forward
  void printReversePostOrder();

  // printing backward
  void printPostOrder();

  vector<long> getReversePostOrder();

  vector<long> getPostOrder();

  ///@brief empty node analysis: finds empty nodes and removes them. Depricated
  // void emptyNodeAnalysis();

  /// adding edge from xNode to yNode

  void addEdge(long xNode, long yNode);

  /// remove edge xNode to yNode

  void removeEdge(long xNode, long yNode);

  /// print graph
  void printGraph();

  /// returns GPBMap for processing blocks
  map<long, GPB *> getGPBMap();

  void setGPBMap(map<long,GPB*> );
  /// returns edges goingout from every node

  void setGPBSet(set<GPB*, GPBComp>);

  map<long, set<long>> getEdgeOut();

  /// returns edges incident to every node

  map<long, set<long>> getEdgeIn();

  /// get GPBSet
  set<GPB *, GPBComp> getGPBSet();


  /// add recursive call block
  void addRecursiveCallBlock(long,StringRef);

  /// get all recursive call blocks
  set<long> getRecursiveCallBlocks(); 

  StringRef functionCalledAtRecursiveBlock(long);

  vector<long> getBFSTraversal();

  vector<long>  getDFSTraversal();

 //@brief use node at line number
  set<StringRef> getPointsToInfo(long);

  bool checkGPUsInSameBlockOrNot(long,long);


  set<long> ReachableNodesFromStratInRecursiveFunctions();

  set<long> ReachableNodesToEndInRecursiveFunctions();

  void DeepCopy(GPG *);

  map<long,StringRef> getRecursiveCallBlockFunction();

};

#endif