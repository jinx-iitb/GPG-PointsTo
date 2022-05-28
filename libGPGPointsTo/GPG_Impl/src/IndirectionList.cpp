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
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Casting.h"

using namespace llvm;

Indirection::Indirection(IndType tId) {
  indirectionLevel = 0;
  stackOrHeap = true;
  typeId = tId;
}

Indirection::Indirection(int ilevel, bool sh, IndType tId) {
  indirectionLevel = ilevel;
  stackOrHeap = sh;
  typeId = tId;
}
Indirection::~Indirection() {}

bool Indirection::isStackOrHeap() { return stackOrHeap; }

int Indirection::getIndirectionLevel() { return indirectionLevel; }

void Indirection::setIndirectionLevel(int l) { indirectionLevel = l; }

void Indirection::setStorageStackOrHeap(bool st) { stackOrHeap = st; }

void Indirection::print() { outs() << indirectionLevel; }

IndirectionList::IndirectionList() : Indirection(LIST) { maxFields = 0; }

IndirectionList::IndirectionList(int level, bool stackOrHeap, int m, vector<int> a)
    : Indirection(level, stackOrHeap, LIST) {

  maxFields = m;
  for (int i = 0; i < m; i++) {
    fieldList.push_back(a[i]);
  }
}

IndirectionList::IndirectionList(int level, bool stackOrHeap)
    : Indirection(level, stackOrHeap, LIST) {
  maxFields = 0;
}

IndirectionList::~IndirectionList() {}

void IndirectionList::print() {

  for (int i = 0; i < getIndirectionLevel(); i++)
    outs() << (i ? ",*" : "*");

  for (int i = 0; i < maxFields; i++) {
    outs() << (i ? "," : "");
    outs() << "f" << fieldList[i];
  }
}

int IndirectionList::getNumberOfFields() { return maxFields; }

std::vector<int> IndirectionList::getFieldList() { return fieldList; }

void IndirectionList::addFields(int n, vector<int> newF) {

  for (int i = 0; i < n; i++)
    fieldList.push_back(newF[i]);

  maxFields = maxFields + n;
}

string IndirectionList::toString() {

  string listA;

  /*for(int i=0;i<getIndirectionLevel();i++){

      if(i) listA = listA + ",*";
      else  listA = listA + "*";

  }*/

  for (int i = 0; i < maxFields; i++) {

    listA = listA + ".f" + std::to_string(fieldList[i]);
  }

  for(int i=0;i<getIndirectionLevel();i++){

      if(i) listA = listA + ",*";
      else  listA = listA + "*";

  }

  return listA;
}
// -------------------------------------------------------- My Implementation ------------------------------------------------------//
std::pair<int,vector<int>> Indirection::ListRemainder(Indirection* consumerpivotInd)
{
    Indirection* sourceInd = this;
    bool is_source_list = llvm::isa<IndirectionList>(sourceInd);
    bool is_consumerpivot_list = llvm::isa<IndirectionList>(consumerpivotInd);

    int derefs;
    vector<int> remList;
    
    int j = consumerpivotInd->getIndirectionLevel(); // *,*..... j times.        
    int k = sourceInd->getIndirectionLevel(); // *,*..... k times. 
    derefs = j - k;

    IndirectionList* sourceList = llvm::dyn_cast<IndirectionList>(sourceInd);
    IndirectionList* consumerpivotList = llvm::dyn_cast<IndirectionList>(consumerpivotInd);

    if(is_source_list && is_consumerpivot_list){
        vector<int> sourceFieldList = sourceList->getFieldList();
        int numFieldsofsource = sourceList->getNumberOfFields();

        vector<int> targetFieldList = consumerpivotList->getFieldList();
        int numFieldsoftarget = consumerpivotList->getNumberOfFields();

        for(int i = numFieldsofsource ; i < numFieldsoftarget; i++){
            remList.push_back(targetFieldList[i]);
        }
    }    
    else if(!is_source_list && is_consumerpivot_list){
        vector<int> targetFieldList = consumerpivotList->getFieldList();
        int numFieldsoftarget = consumerpivotList->getNumberOfFields();

        for(int i = 0 ; i < numFieldsoftarget; i++){
            remList.push_back(targetFieldList[i]);
        }
    }    
    return std::make_pair(derefs,remList);
}
// Computes this @ L2
Indirection* Indirection::ListAppend(Indirection* targetProducerInd)
{

    Indirection* RemInd = this;
    bool is_rem_list = llvm::isa<IndirectionList>(RemInd);
    bool is_target_producer_list = llvm::isa<IndirectionList>(targetProducerInd);

    int derefs;
    vector<int> finList;
    
    int j_k = RemInd->getIndirectionLevel(); // *,*..... j times.        
    int l = targetProducerInd->getIndirectionLevel(); // *,*..... k times. 
    derefs = l + j_k; // TS : l + j - k; SS : i + l -k

    IndirectionList* RemList = llvm::dyn_cast<IndirectionList>(RemInd);
    IndirectionList* targetProducerList = llvm::dyn_cast<IndirectionList>(targetProducerInd);

    if(is_rem_list && is_target_producer_list){
        vector<int> RemFieldList = RemList->getFieldList();
        int numFieldsofRem = RemList->getNumberOfFields();

        vector<int> targetProducerFieldList = targetProducerList->getFieldList();
        int numFieldsoftargetProducer = targetProducerList->getNumberOfFields();

        for(int i = 0 ; i < numFieldsofRem; i++){
            finList.push_back(RemFieldList[i]);
        }

        for(int i = 0 ; i < numFieldsoftargetProducer; i++){
            finList.push_back(targetProducerFieldList[i]);
        }
    }
    else if(is_rem_list && !is_target_producer_list){
        vector<int> RemFieldList = RemList->getFieldList();
        int numFieldsofRem = RemList->getNumberOfFields();

        for(int i = 0 ; i < numFieldsofRem; i++){
            finList.push_back(RemFieldList[i]);
        }
    }    
    else if(!is_rem_list && is_target_producer_list){
        vector<int> targetProducerFieldList = targetProducerList->getFieldList();
        int numFieldsoftargetProducer = targetProducerList->getNumberOfFields();

        for(int i = 0 ; i < numFieldsoftargetProducer; i++){
            finList.push_back(targetProducerFieldList[i]);
        }
    }   
    Indirection* res; 
    if(finList.empty()){
        res = new Indirection(derefs, 1, SINGLE);
    }
    else{
        res = new IndirectionList(derefs ,1, finList.size(), finList);
    }
    return res;    
}
// ----------------------------------------------------------------------------------------------------------------------------------//