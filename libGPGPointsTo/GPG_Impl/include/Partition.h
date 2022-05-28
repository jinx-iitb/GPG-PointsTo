#ifndef Partition_H_
#define Partition_H_
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

#include "GPG.h"


enum CoherentOrNonCoherentType{
   ONLYENTRYNONCOHERENT,
   ONLYEXITNONCOHERENT,
   BOTHNONCOHERENT,
   COHERENT
};

class Partition{
  
  long partitionId;
  set<GPB*,GPBComp> gpbs;
  set<GPB*,GPBComp> entryNodes;
  set<GPB*,GPBComp> exitNodes;
  

  static long currentPartitionId;
  CoherentOrNonCoherentType getCoherentOrNotCoherentType(GPG *gpg);
public:

  Partition(set<GPB*,GPBComp>,GPG*);

  long size();

  bool partitionHasEntryNodeOfGPG(GPG*);

  bool partitionHasExitNodeOfGPG(GPG*);

  void setEntryNodesOfPartition(GPG*);

  void setExitNodesOfPartition(GPG*);

  long getPartitionId();

  set<GPB*,GPBComp> getGPBs();

  set<GPB*,GPBComp> getEntryNodesOfPartition();

  set<GPB*,GPBComp> getExitNodesOfPartition();

  set<GPUNode *, GPUNodeComp> mayDefSetsOfPartition();

  bool coherentOrNot(GPG*);

  vector<Partition*> divideNonCoherentPartition(GPG *);

  // @brief  set of nodes which are predecessors of entry node
  // this should be called for coherent partitions only.
  set<long>  getPredecessorsOfPartition(GPG *);
  
  // @brief  set of nodes which are successors of exit node
  // this should be called for coherent partitions only.
  set<long>  getSuccessorsOfPartition(GPG *);

  vector<Partition*>  getCoherentPartitions(GPG *);

  void print();
  // ------------------------------------ My Implementation -----------------------------------//
  void addGPBtopart(GPB *gpb);
  set<GPB *, GPBComp> findEntryNodesOfPartition();
  set<GPB *, GPBComp> findExitNodesOfPartition();
  bool isCoherent(set<GPB *, GPBComp>, set<GPB *, GPBComp>);
  //------------------------------------------------------------------------------------------//
};

#endif