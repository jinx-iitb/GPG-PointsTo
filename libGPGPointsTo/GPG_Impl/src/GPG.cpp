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
#include "llvm/Support/raw_ostream.h"
#include <fstream>

using namespace llvm;
using namespace std;

#define FOR_EACH_ELEMENT(s, itr) for (itr = s.begin(); itr != s.end(); itr++)

GPG::GPG() {

  entryNode = NULL;
  exitNode = NULL;
}


void GPG::setEntryNode(GPB *entry) {

  entryNode = entry;
  GPBsMap[entryNode->getGPBNo()] = entryNode;
}

void GPG::setExitNode(GPB *exit) {

  exitNode = exit;
  GPBsMap[exitNode->getGPBNo()] = exitNode;
}

void GPG::insertGPB(GPB *gpb) {

  GPBSet.insert(gpb);
  GPBsMap[gpb->getGPBNo()] = gpb;
}

void GPG::removeGPB(GPB *gpb) {

  GPBSet.erase(gpb);
  GPBsMap.erase(gpb->getGPBNo());
  edgesOut.erase(gpb->getGPBNo());
  edgesIn.erase(gpb->getGPBNo());
}

set<GPB *, GPBComp> GPG::getGPBSet() { return GPBSet; }
void GPG::setGPBSet(set<GPB *, GPBComp> GPBSet) {
    this->GPBSet = GPBSet;
}

void GPG::addSuccessortoBB(long bbNo, GPB *succ) {

  set<GPB *, GPBComp>::iterator itr;

  FOR_EACH_ELEMENT(GPBSet, itr) {

    if ((*itr)->getGPBNo() == bbNo) {

      (*itr)->addSuccessor(succ);

      addEdge(bbNo, succ->getGPBNo());
    }
  }
}
void GPG::addPredecessortoBB(long bbNo, GPB *pred) {

  set<GPB *, GPBComp>::iterator itr;

  FOR_EACH_ELEMENT(GPBSet, itr) {

    if ((*itr)->getGPBNo() == bbNo) {

      (*itr)->addPredecessor(pred);
      addEdge(pred->getGPBNo(), bbNo);
    }
  }
}

void GPG::removeSuccessorOfBB(long bbNo, GPB *succ) {

  set<GPB *, GPBComp>::iterator itr;

  FOR_EACH_ELEMENT(GPBSet, itr) {

    if ((*itr)->getGPBNo() == bbNo) {

      (*itr)->removeSuccessor(succ);

      removeEdge(bbNo, succ->getGPBNo());
    }
  }
}
void GPG::removePredecessorOfBB(long bbNo, GPB *pred) {

  set<GPB *, GPBComp>::iterator itr;

  FOR_EACH_ELEMENT(GPBSet, itr) {

    if ((*itr)->getGPBNo() == bbNo) {

      (*itr)->removePredecessor(pred);

      removeEdge(pred->getGPBNo(), bbNo);
    }
  }
}

void GPG::removeAllSuccessorsOfBB(long bbNo){

 set<GPB *, GPBComp>::iterator itr;

  FOR_EACH_ELEMENT(GPBSet, itr) {

    if ((*itr)->getGPBNo() == bbNo) {

      (*itr)->removeAllSuccessors();
      edgesOut.erase(bbNo);
    }
  }

}

void GPG::removeAllPredecessorsOfBB(long bbNo){
 
 set<GPB *, GPBComp>::iterator itr;

  FOR_EACH_ELEMENT(GPBSet, itr) {

    if ((*itr)->getGPBNo() == bbNo) {

      (*itr)->removeAllPredecessors();
      edgesIn.erase(bbNo);
    }
  }


}


/* void GPG::emptyNodeAnalysis(){

   set<GPB*,GPBComp>::iterator itrSet,itrSuccSet,itrPredSet;

   FOR_EACH_ELEMENT(GPBSet,itrSet){

      /// skip entry and exit nodes
     if((*itrSet)->getGPBNo() == entryNode->getGPBNo()) continue;
     else if ((*itrSet)->getGPBNo() == exitNode->getGPBNo()) continue;


     if((*itrSet)->isEmpty()){

        set<GPB*,GPBComp> succSet = (*itrSet)->getAllSuccessors();

        FOR_EACH_ELEMENT(succSet,itrSuccSet){

           set<GPB*,GPBComp> predSet = (*itrSet)->getAllPredecessors();

           FOR_EACH_ELEMENT(predSet,itrPredSet){

              addSuccessortoBB((*itrPredSet)->getGPBNo(), *itrSuccSet);
              addPredecessortoBB((*itrSuccSet)->getGPBNo(), *itrPredSet);


              removeSuccessorOfBB((*itrSet)->getGPBNo(),*itrSuccSet);
              removePredecessorOfBB((*itrSuccSet)->getGPBNo(),*itrSet);

              removePredecessorOfBB((*itrSet)->getGPBNo(),*itrPredSet);
              removeSuccessorOfBB((*itrPredSet)->getGPBNo(),*itrSet);
           }

        }

          GPBSet.erase(*itrSet);
          GPBsMap.erase((*itrSet)->getGPBNo());
      }


    }

    //print();

 }*/

/// print

void GPG::print() {

  set<GPB *, GPBComp>::iterator itrSet, itrSuccSet, itrPredSet;

  FOR_EACH_ELEMENT(GPBSet, itrSet) {

    (*itrSet)->print();

    outs() << "Successors are:\n";

    set<GPB *, GPBComp> succSet = (*itrSet)->getAllSuccessors();

    FOR_EACH_ELEMENT(succSet, itrSuccSet) { (*itrSuccSet)->print(); }

    outs() << "Predecessors are:\n";

    set<GPB *, GPBComp> predSet = (*itrSet)->getAllPredecessors();

    FOR_EACH_ELEMENT(predSet, itrPredSet) { (*itrPredSet)->print(); }

    outs() << "\n";
  }
}

/// printToDot file

void GPG::printToDot(string fileName) {

  set<GPB *, GPBComp>::iterator itrSet, itrSuccSet;  

  ofstream dotFile;
  dotFile.open("../../analysis/" + fileName);

  dotFile << "digraph GPG{"
          << "\n";

  dotFile << "node [shape=box]; \n";
  int cnt = 0;   
  FOR_EACH_ELEMENT(GPBSet, itrSet) {

    dotFile << (*itrSet)->getGPBNo();
    dotFile << "[label=";
    if((*itrSet)->isItRecursiveCallBlock())
        dotFile << "<" << (*itrSet)->toString() << ">";
    else if(*itrSet == this->getEntryNode())
        dotFile << "<<I>Start" << "</I>>";
    else if(*itrSet == this->getExitNode())
        dotFile << "<<I>End" << "</I>>";
    else
        dotFile << "\"" << (*itrSet)->toString() << "\"";
    dotFile << ","<< "xlabel="<<"\""<<(*itrSet)->getGPBNo()<<"\"";
    dotFile << ", color=";
    if((*itrSet)->getisInlined())
    {
        dotFile << "lightblue, fontcolor=black, style=filled"  << "]\n;";
    }
    else
    {
        dotFile << "lightgray, fontcolor=black" << "];\n";
    }
    set<GPB *, GPBComp> succSet = (*itrSet)->getAllSuccessors();

    FOR_EACH_ELEMENT(succSet, itrSuccSet) {

      dotFile << (*itrSet)->getGPBNo() << "->" << (*itrSuccSet)->getGPBNo()
              << ";\n";
    }
    cnt++;
  }

  dotFile << "}";
}

void GPG::dump(string filename) {
    ofstream dotFile;
    dotFile.open("../../analysis/" + filename + "-dump.txt");
    set<GPB *, GPBComp>::iterator itrSet;
    string s;
    FOR_EACH_ELEMENT(GPBSet, itrSet) {
        //dotFile << (*itrSet)->getGPBNo() << " {";
        //(*itrSet)->print();
        //continue;
        dotFile << (*itrSet)->dumpString().c_str() << "\n";
        /*set<GPU *, GPUComp>::iterator itr;

        FOR_EACH_ELEMENT((*itrSet)->getGPUSet(), itr) {
            (*itr)->print();
            if((*itr) == nullptr){
                continue;
            }
            GPUNode *left = (*itr)->getSourceOfGPU();
            GPUNode *right = (*itr)->getTargetOfGPU();
            if(left==NULL && right==NULL)
                outs()<< "Delta^{Top}";

            else {
                dotFile << left->getNameOfVariable().str() << " , ";

                dotFile << left->getIndirectList()->getIndirectionLevel();

                //outs() << ")"
                //       << "-->"
                dotFile << right->getNameOfVariable().str() << " , ";

                dotFile << right->getIndirectList()->getIndirectionLevel();

                dotFile << ";";
            }

            dotFile << "}\n";
        }*/
    }
    int totalGPBs = 0;
    int totalGPUs = 0;
    FOR_EACH_ELEMENT(GPBSet, itrSet) {
        totalGPBs++;
        totalGPUs += (*itrSet)->getGPUSet().size();
    }
    dotFile << "------------------------\n";
    dotFile << "Total GPBs : " << totalGPBs << "\n";
    dotFile << "Total GPUs : " << totalGPUs << "\n";
    dotFile.close();
}

/// print graph

void GPG::printGraph() {

  map<long, set<long>>::iterator nItr;
  set<long>::iterator edgesNItr;

  for (nItr = edgesOut.begin(); nItr != edgesOut.end(); nItr++) {

    outs() << nItr->first << "\t";

    for (edgesNItr = nItr->second.begin(); edgesNItr != nItr->second.end();
         edgesNItr++) {

      outs() << *edgesNItr << " ";
    }

    outs() << "\n";
  }

  for (nItr = edgesIn.begin(); nItr != edgesIn.end(); nItr++) {

    outs() << nItr->first << "\t";

    for (edgesNItr = nItr->second.begin(); edgesNItr != nItr->second.end();
         edgesNItr++) {

      outs() << *edgesNItr << " ";
    }

    outs() << "\n";
  }
}

/// printing forward
void GPG::printReversePostOrder() {

}

/// printing backward
void GPG::printPostOrder() {}

// visit parent before its children
vector<long> GPG::getReversePostOrder(){

    vector<long>  revPostOrder= getPostOrder();

    /*outs()<<" Post Order traversal \n";
    for(auto vItr = revPostOrder.begin();vItr!=revPostOrder.end();vItr++)
            outs()<<*vItr<<"  ";
    outs()<<"   \n";*/
    reverse(revPostOrder.begin(),revPostOrder.end());
    /*outs()<<" Reverse Post Order traversal \n";
    for(auto vItr = revPostOrder.begin();vItr!=revPostOrder.end();vItr++)
            outs()<<*vItr<<"  ";
    outs()<<"   \n";*/
    return revPostOrder;
}
//visit children before its parent
vector<long> GPG::getPostOrder(){

     map<long,bool> visited;
     long curGPB;
     stack<pair<long,int>> nodeStack;
     vector<long>  orderPostOrder;
     pair<long,int>  nodeAndNeighbors;

     map<long,vector<long>> outEdges;

     set<long> out;

     long entry = entryNode->getGPBNo();

     for(auto gpbNode=GPBsMap.begin();gpbNode!=GPBsMap.end();gpbNode++){
           curGPB = (*gpbNode).first;
           visited[curGPB] = false;
           out = edgesOut[curGPB];
           vector<long> neighbors;
           for(auto outItr=out.begin();outItr!=out.end();outItr++){
                 neighbors.push_back(*outItr);
           }
           outEdges[curGPB]=neighbors;
     }

     nodeStack.push(make_pair(entry,0));

     while(!nodeStack.empty()){

         nodeAndNeighbors = nodeStack.top();
         nodeStack.pop();
         curGPB = nodeAndNeighbors.first;

         if(!visited[curGPB]){
              visited[curGPB]=true;
         }

         if(nodeAndNeighbors.second < outEdges[curGPB].size()){
              int n = nodeAndNeighbors.second + 1;
              nodeStack.push(make_pair(curGPB,n));
              long nextNeighbor = outEdges[curGPB].at(n-1);
              if(!visited[nextNeighbor])
                  nodeStack.push(make_pair(nextNeighbor,0));
         }
         else  orderPostOrder.push_back(nodeAndNeighbors.first);

     }

    return orderPostOrder; 

}

/// add edge from node x to node y

void GPG::addEdge(long xNode, long yNode) {

  set<long> adjToX = edgesOut[xNode];

  adjToX.insert(yNode);

  // outs()<<"test: "<<xNode<<"\n";

  edgesOut[xNode] = adjToX;

  set<long> adjToY = edgesIn[yNode];

  adjToY.insert(xNode);

  // outs()<<"test: "<<xNode<<"\n";

  edgesIn[yNode] = adjToY;
}

/// remove edge xNode to yNode

void GPG::removeEdge(long xNode, long yNode) {

  set<long> adjToX = edgesOut[xNode];

  adjToX.erase(yNode);

  if (!adjToX.empty())
    edgesOut[xNode] = adjToX;
  else
    edgesOut.erase(xNode);

  set<long> adjToY = edgesIn[yNode];

  adjToY.erase(xNode);

  if (!adjToY.empty())
    edgesIn[yNode] = adjToY;
  else
    edgesIn.erase(yNode);
}

GPB *GPG::getEntryNode() { return entryNode; }

GPB *GPG::getExitNode() { return exitNode; }

map<long, GPB *> GPG::getGPBMap() { return GPBsMap; }

map<long, set<long>> GPG::getEdgeOut() { return edgesOut; }

map<long, set<long>> GPG::getEdgeIn() { return edgesIn; }

void GPG::setGPBMap(map<long,GPB*> gpbM){

   for(auto gpbItr= gpbM.begin();gpbItr!=gpbM.end();gpbItr++){

       GPBsMap[(*gpbItr).first] = (*gpbItr).second;
   }


}

vector<long> GPG::getBFSTraversal(){

     map<long,bool> visited;
     long curGPB;
     queue<long> nodeQueue;
     vector<long>  bfsOrder;
     set<long> outEdges;
     set<long> emptySet;

     long entry = entryNode->getGPBNo();

     long exitN  = exitNode->getGPBNo();

     for(auto gpbNode=GPBsMap.begin();gpbNode!=GPBsMap.end();gpbNode++){
           curGPB = (*gpbNode).first;
           visited[curGPB] = false;
     }

     nodeQueue.push(entry);

     while(!nodeQueue.empty()){

        curGPB = nodeQueue.front();
        nodeQueue.pop();

        if(!visited[curGPB]){
               bfsOrder.push_back(curGPB);
               visited[curGPB]=true;
        }
        
        if(curGPB != exitN)
          outEdges = edgesOut[curGPB];
        else 
          outEdges = emptySet;

        for(auto n=outEdges.begin();n!=outEdges.end();n++){
                if(!visited[*n])
                  nodeQueue.push(*n);
         } 

     }

   /* outs()<<" BFS Order traversal \n";
    for(auto vItr = bfsOrder.begin();vItr!=bfsOrder.end();vItr++)
            outs()<<*vItr<<"  ";
    outs()<<"   \n";*/

     return bfsOrder;
}

vector<long>  GPG::getDFSTraversal(){

     map<long,bool> visited;
     long curGPB;
     stack<long> nodeStack;
     vector<long>  orderOfTraversalList;
     set<long> outEdges;

     long entry = entryNode->getGPBNo();

     for(auto gpbNode=GPBsMap.begin();gpbNode!=GPBsMap.end();gpbNode++){
           curGPB = (*gpbNode).first;
           visited[curGPB] = false;
     }

     nodeStack.push(entry);

     while(!nodeStack.empty()){

         curGPB = nodeStack.top();
         nodeStack.pop();

         if(!visited[curGPB]){
               orderOfTraversalList.push_back(curGPB);
               visited[curGPB]=true;
         }

         outEdges = edgesOut[curGPB];

         for(auto n=outEdges.begin();n!=outEdges.end();n++){
                if(!visited[*n])
                  nodeStack.push(*n);
         }

     }

    return orderOfTraversalList; 
}

set<StringRef> GPG::getPointsToInfo(long lineNo){

   set<StringRef> pointsToSet;

   set<StringRef> emptySet;

   bool firstOne=true;

   for(auto gItr= GPBsMap.begin(); gItr!=GPBsMap.end();gItr++){

       set<GPU*,GPUComp> gpuSet = (*gItr).second->getGPUSet();

       for(auto gpuItr= gpuSet.begin();gpuItr!=gpuSet.end();gpuItr++){
              
              if((*gpuItr)->getStmtNo()==lineNo) {

                GPUNode *right = (*gpuItr)->getTargetOfGPU();
                StringRef name = right->getNameOfVariable();

                int indirectionLevel = right->getIndirectList()->getIndirectionLevel();

                if(indirectionLevel!=0) return emptySet;
                 
                pointsToSet.insert(name);
              }

       }
    }
    return pointsToSet;
}


bool GPG::checkGPUsInSameBlockOrNot(long  firstLineNo,long secondLineNo){

   bool firstInGPB, secondInGPB;

   if(firstLineNo==secondLineNo) return true;

   for(auto gItr= GPBsMap.begin(); gItr!=GPBsMap.end();gItr++){

       set<GPU*,GPUComp> gpuSet = (*gItr).second->getGPUSet();
       firstInGPB = false;
       secondInGPB = false; 
       for(auto gpuItr= gpuSet.begin();gpuItr!=gpuSet.end();gpuItr++){
              
              if((*gpuItr)->getStmtNo()==firstLineNo) firstInGPB =true;
              else if((*gpuItr)->getStmtNo()==secondLineNo) secondInGPB=true;
       }
       if(firstInGPB && secondInGPB) return true;
       else if(firstInGPB || secondInGPB) return false;
    }   

    return false;
}


void GPG::addRecursiveCallBlock(long rB,StringRef callee){
    recursiveCallBlocks.insert(rB);
    recursiveCallBlockFunction[rB] = callee;
}

set<long> GPG::getRecursiveCallBlocks(){
   return recursiveCallBlocks;
}

set<long> GPG::ReachableNodesFromStratInRecursiveFunctions(){     
     map<long,bool> visited;
     long curGPB;
     queue<long> nodeQueue;
     set<long>  reachableNodes;
     set<long> outEdges;
     set<long> emptySet;

     long entry = entryNode->getGPBNo();

     long exitN  = exitNode->getGPBNo();

     for(auto gpbNode=GPBsMap.begin();gpbNode!=GPBsMap.end();gpbNode++){
           curGPB = (*gpbNode).first;
           visited[curGPB] = false;
     }

     nodeQueue.push(entry);

     while(!nodeQueue.empty()){

        curGPB = nodeQueue.front();
        nodeQueue.pop();

        if(!visited[curGPB]){

            if(!GPBsMap[curGPB]->isItRecursiveCallBlock())
                  reachableNodes.insert(curGPB);
          
               visited[curGPB]=true;
        }
        
        if(curGPB != exitN && !GPBsMap[curGPB]->isItRecursiveCallBlock())
          outEdges = edgesOut[curGPB];
        else 
          outEdges = emptySet;

        for(auto n=outEdges.begin();n!=outEdges.end();n++){
                if(!visited[*n])
                  nodeQueue.push(*n);
         } 

     }

    /*outs()<<" Reachable Nodes From Strat In Recursive Functions \n";
    for(auto vItr = reachableNodes.begin();vItr!=reachableNodes.end();vItr++)
            outs()<<*vItr<<"  ";
    outs()<<"   \n";*/

     return reachableNodes;     

}


set<long> GPG::ReachableNodesToEndInRecursiveFunctions(){
   
     map<long,bool> visited;
     long curGPB;
     queue<long> nodeQueue;
     set<long>  reachableNodes;
     set<long> inEdges;
     set<long> emptySet;

     long entry = entryNode->getGPBNo();

     long exitN  = exitNode->getGPBNo();

     for(auto gpbNode=GPBsMap.begin();gpbNode!=GPBsMap.end();gpbNode++){
           curGPB = (*gpbNode).first;
           visited[curGPB] = false;
     }

     nodeQueue.push(exitN);

     while(!nodeQueue.empty()){

        curGPB = nodeQueue.front();
        nodeQueue.pop();

        if(!visited[curGPB]){

            if(!GPBsMap[curGPB]->isItRecursiveCallBlock())
                  reachableNodes.insert(curGPB);
          
               visited[curGPB]=true;
        }
        
        if(curGPB != entry && !GPBsMap[curGPB]->isItRecursiveCallBlock())
          inEdges = edgesIn[curGPB];
        else 
          inEdges = emptySet;

        for(auto n=inEdges.begin();n!=inEdges.end();n++){
                if(!visited[*n])
                  nodeQueue.push(*n);
         } 

     }

    /*outs()<<" Reachable Nodes From Strat In Recursive Functions \n";
    for(auto vItr = reachableNodes.begin();vItr!=reachableNodes.end();vItr++)
            outs()<<*vItr<<"  ";
    outs()<<"   \n";*/

     return reachableNodes;     

}

// call only in handling recursive calls
void GPG::DeepCopy(GPG *gpg){

  set<GPB*, GPBComp> gpbSet = gpg->getGPBSet();

   for(auto gItr= gpbSet.begin(); gItr!=gpbSet.end(); gItr++)
   {
      GPB *gpb = new GPB((*gItr)->getGPBNo());
      GPBSet.insert(gpb);
      if((*gItr) == gpg->getEntryNode())
        entryNode = gpb;
      else if((*gItr) == gpg->getExitNode())
        exitNode = gpb;        
      GPBsMap[(*gItr)->getGPBNo()] = gpb;

      if( (*gItr)->isItRecursiveCallBlock())
         gpb->setAsRecursiveCallBlock();

      gpb->setGPUSet((*gItr)->getGPUSet());
   }

   edgesOut = gpg->getEdgeOut();
   edgesIn  = gpg->getEdgeIn();

  for(auto oItr=edgesOut.begin();oItr!=edgesOut.end();oItr++){
      
      long bNo = (*oItr).first;
      set<long> succs = edgesOut[bNo];

      for(auto s=succs.begin(); s!=succs.end();s++){
              // outs()<<"Node:  "<<*s<<"\n";
               addSuccessortoBB(bNo, GPBsMap[*s]);
      }
      
  }

  for(auto iItr=edgesIn.begin();iItr!=edgesIn.end();iItr++){

     long bNo = (*iItr).first;
     set<long> preds = edgesIn[bNo];

     for(auto p=preds.begin();p!=preds.end();p++){
              //  outs()<<"Node:  "<<*p<<"\n";
              addPredecessortoBB(bNo,GPBsMap[*p]);
      }        
  }    
 recursiveCallBlocks = gpg->getRecursiveCallBlocks();
 recursiveCallBlockFunction = gpg->getRecursiveCallBlockFunction();
}

map<long,StringRef> GPG::getRecursiveCallBlockFunction(){
     return recursiveCallBlockFunction;
}

StringRef GPG::functionCalledAtRecursiveBlock(long blockNo){
   StringRef blank;

   if(recursiveCallBlockFunction.find(blockNo)!=recursiveCallBlockFunction.end())
      return recursiveCallBlockFunction[blockNo];
   else return blank;
}
