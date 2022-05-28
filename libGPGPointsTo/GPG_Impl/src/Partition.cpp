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
#include "Partition.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

long Partition::currentPartitionId =0;

Partition::Partition(set<GPB*,GPBComp> part,GPG* gpg){
   currentPartitionId++;
   partitionId = currentPartitionId;
   gpbs = part;
   setEntryNodesOfPartition(gpg);
   setExitNodesOfPartition(gpg);   
}

long Partition::size(){
    return gpbs.size();
}

void Partition::setEntryNodesOfPartition(GPG *gpg){

   set<long> partGPBNos;
   
   for(auto elem=gpbs.begin();elem!=gpbs.end();elem++){
        partGPBNos.insert((*elem)->getGPBNo());
   }

   for(auto elem=gpbs.begin();elem!=gpbs.end();elem++){
        set<long> preds = gpg->getEdgeIn()[(*elem)->getGPBNo()];
        
        bool predsNotBelongs = false;   
        for(auto p = preds.begin();p!=preds.end();p++){

            if(partGPBNos.find(*p)==partGPBNos.end()){
                predsNotBelongs = true;
                break;
            }
        }
        
        if(predsNotBelongs==true || preds.empty())        
           entryNodes.insert(*elem);
   }

}

set<GPB*,GPBComp> Partition::getEntryNodesOfPartition(){
       return entryNodes;
}


void Partition::setExitNodesOfPartition(GPG *gpg){

   set<long> partGPBNos;
   
   for(auto elem=gpbs.begin();elem!=gpbs.end();elem++){
        partGPBNos.insert((*elem)->getGPBNo());
   }

   for(auto elem=gpbs.begin();elem!=gpbs.end();elem++){
        set<long> succs = gpg->getEdgeOut()[(*elem)->getGPBNo()];
        
        bool succsNotBelongs = false;   
        for(auto s = succs.begin();s!=succs.end();s++){

            if(partGPBNos.find(*s)==partGPBNos.end()){
                succsNotBelongs = true;
                break;
            }
        }
        
        if(succsNotBelongs==true || succs.empty())        
           exitNodes.insert(*elem);
   }

}

set<GPB*,GPBComp> Partition::getExitNodesOfPartition(){
       return exitNodes;
}

set<GPUNode *, GPUNodeComp> Partition::mayDefSetsOfPartition(){

    set<GPU*,GPUComp> deltaN;
     
    set<GPU*,GPUComp> gpuSet, inGPUSet, outGPUSet,rIn,rOut, preservedGPUSet;

    set<GPUNode*,GPUNodeComp> definedSources, preservedSources, mayDefSet;

    for (auto gpb=gpbs.begin();gpb!=gpbs.end();gpb++){
          
          gpuSet = (*gpb)->getGPUSet();

          for(auto elem = gpuSet.begin();elem!=gpuSet.end();elem++){

             deltaN.insert(*elem);
             definedSources.insert((*elem)->getSourceOfGPU());
          }
    }
    
    for (auto entryN = entryNodes.begin(); entryN!=entryNodes.end();entryN++){
         rIn = (*entryN)->getRGBlockingIn();

         for(auto elem = rIn.begin();elem!=rIn.end();elem++)
                 inGPUSet.insert(*elem);
    }

    for (auto exitN = exitNodes.begin(); exitN!=exitNodes.end();exitN++){
         rOut = (*exitN)->getRGBlockingOut();

         for(auto elem = rOut.begin();elem!=rOut.end();elem++)
                 outGPUSet.insert(*elem);
    }

    // preserved = (inGPUSet intersection outSet) - deltaN
    for( auto elem = inGPUSet.begin();elem!=inGPUSet.end();elem++){
         // also belongs tp outGPUSet
         if(outGPUSet.find(*elem)!=outGPUSet.end()){
            // should not belongs to deltaN
            if(deltaN.find(*elem)==deltaN.end()) {
                 preservedGPUSet.insert(*elem);
                 preservedSources.insert((*elem)->getSourceOfGPU());
            }
         }
    }

    // MayDef set = presrved sources intersection defined sources

    for(auto gpuN = definedSources.begin(); gpuN!=definedSources.end();gpuN++){
       // it also belongs to presrved sources
         if(preservedSources.find(*gpuN)!=preservedSources.end())
                mayDefSet.insert(*gpuN);
    }

    return mayDefSet;
}

bool Partition::coherentOrNot(GPG *gpg){

   if(gpbs.size()==1)  return true;


   CoherentOrNonCoherentType chType = getCoherentOrNotCoherentType(gpg);

   if(chType==COHERENT)
      return true;
   else 
      return false;
}


CoherentOrNonCoherentType Partition::getCoherentOrNotCoherentType(GPG *gpg){

   set<long> partGPBNos, entryGPBNos, exitGPBNos;

   set<long> preds, succs,xPreds,xSuccs,newXPreds,newXSuccs;

    
   if(gpbs.size()==1)   return COHERENT;

   for(auto elem=gpbs.begin();elem!=gpbs.end();elem++)
        partGPBNos.insert((*elem)->getGPBNo());

   for(auto elem=entryNodes.begin();elem!=entryNodes.end();elem++)
        entryGPBNos.insert((*elem)->getGPBNo());

   for(auto elem=exitNodes.begin();elem!=exitNodes.end();elem++)
        exitGPBNos.insert((*elem)->getGPBNo());

   // for all entrynodes, external predecessor must be same
       
    bool sameXPreds = true;

    set<long>::iterator sItr = entryGPBNos.begin();

    preds = gpg->getEdgeIn()[*sItr];
    
    // nodes not in partition
    for(auto n=preds.begin();n!=preds.end();n++)
             xPreds.insert(*n);
    // remaining entry nodes
      sItr++; 
     for(;sItr!=entryGPBNos.end();sItr++){      
         preds = gpg->getEdgeIn()[*sItr];

         // nodes not in partition
     for(auto n=preds.begin();n!=preds.end();n++)
            newXPreds.insert(*n);

     for(auto n=newXPreds.begin();n!=newXPreds.end();n++)
            if(xPreds.find(*n)==xPreds.end()){
                 sameXPreds = false;
                 break;
            }

      if(sameXPreds){      
        for(auto n=xPreds.begin();n!=xPreds.end();n++)
            if(newXPreds.find(*n)==newXPreds.end()){
                 sameXPreds = false;
                 break;
            }
        }

      if(!sameXPreds) break;                 

       newXPreds.clear();
     }
    
// for all exitnodes, external successors must be same
    bool sameXSuccs = true;
    sItr = exitGPBNos.begin();

    succs = gpg->getEdgeOut()[*sItr];

     // nodes not in partition
    for(auto n=succs.begin();n!=succs.end();n++)
             xSuccs.insert(*n);

  // remaining exit nodes
      sItr++; 
     for(;sItr!=exitGPBNos.end();sItr++){             
         succs = gpg->getEdgeOut()[*sItr];

         for(auto n=succs.begin();n!=succs.end();n++)
                newXSuccs.insert(*n);

         for(auto n=newXSuccs.begin();n!=newXSuccs.end();n++)
            if(xSuccs.find(*n)==xSuccs.end()){
                 sameXSuccs=false;
                 break;
            }

         if(sameXSuccs){  
           for(auto n=xSuccs.begin();n!=xSuccs.end();n++)
              if(newXSuccs.find(*n)==newXSuccs.end()){
                   sameXSuccs=false;
                   break;
              }
          }

          if(!sameXSuccs) break;

        newXSuccs.clear();
     }

    if(!sameXPreds && !sameXSuccs)  return BOTHNONCOHERENT;
    else if(!sameXPreds) return ONLYENTRYNONCOHERENT;
    else if(!sameXSuccs) return ONLYEXITNONCOHERENT;
    else return COHERENT; 
}

vector<Partition*> Partition::divideNonCoherentPartition(GPG *gpg){

    vector<Partition*> partitions;
    map<long,bool>     isPartOfPartition;
    CoherentOrNonCoherentType chType = getCoherentOrNotCoherentType(gpg);
    
    if(chType == COHERENT){
      partitions.push_back(this);
      return partitions;
    }  


    for(auto gpb=gpbs.begin();gpb!=gpbs.end();gpb++){
      isPartOfPartition[(*gpb)->getGPBNo()]=false;
    }
    
    // singleton entry nodes
    if(chType==ONLYENTRYNONCOHERENT || chType==BOTHNONCOHERENT){

       for(auto elem=entryNodes.begin();elem!=entryNodes.end();elem++){

               if(isPartOfPartition[(*elem)->getGPBNo()]==false){
                    
                    set<GPB*,GPBComp> sPart;
                    sPart.insert(*elem);
                    Partition *part = new Partition(sPart,gpg);
                    partitions.push_back(part);
                    isPartOfPartition[(*elem)->getGPBNo()] = true;
               }

       }

    }

    //singleton exit nodes
    if(chType==ONLYEXITNONCOHERENT || chType==BOTHNONCOHERENT){

      //outs()<<"   eee\n";
       for(auto elem=exitNodes.begin();elem!=exitNodes.end();elem++){

               if(isPartOfPartition[(*elem)->getGPBNo()]==false){
                    
                    set<GPB*,GPBComp> sPart;
                    sPart.insert(*elem);
                    Partition *part = new Partition(sPart,gpg);
                    partitions.push_back(part);
                    isPartOfPartition[(*elem)->getGPBNo()] = true;
               }

       }

    }

    set<GPB*,GPBComp> sPart;
    // all other nodes
    for(auto gpb=gpbs.begin();gpb!=gpbs.end();gpb++){
         if(isPartOfPartition[(*gpb)->getGPBNo()]==false)
              sPart.insert(*gpb);
    }

    if(!sPart.empty()) {
      Partition *part = new Partition(sPart,gpg);
      partitions.push_back(part);
    }

    return partitions;
}

vector<Partition*>  Partition::getCoherentPartitions(GPG *gpg){

   vector<Partition*> tpartitions, partitions,temp;
   bool nonCoherent = true;

   tpartitions = divideNonCoherentPartition(gpg);

   /*for(auto tPart = tpartitions.begin();tPart!=tpartitions.end();tPart++){
        (*tPart)->print();
   }*/
   while(nonCoherent){

     nonCoherent = false;
     for(auto pItr = tpartitions.begin(); pItr!=tpartitions.end();pItr++) {
            if((*pItr)->coherentOrNot(gpg))
              partitions.push_back((*pItr));
            else {
              temp = (*pItr)->divideNonCoherentPartition(gpg);
              nonCoherent = true;
            }
     }
     tpartitions.clear();
     
     tpartitions = temp;
   }

   return partitions;
}

void Partition::print(){

  outs() <<"\n Partition \n{";
          for(auto sItr = gpbs.begin(); sItr!=gpbs.end();sItr++){
              long gpbNo = (*sItr)->getGPBNo();
              outs() << (sItr==gpbs.begin() ? "": ", ");
              outs() <<gpbNo;
            }
  outs() <<" } \n";

  outs()<<"Entry nodes: ";
  outs() <<" {";
          for(auto sItr = entryNodes.begin(); sItr!=entryNodes.end();sItr++){
              long gpbNo = (*sItr)->getGPBNo();
              outs() << (sItr==entryNodes.begin() ? "": ", ");
              outs() <<gpbNo;
            }
  outs() <<" } \n";
  
  outs()<<"Exit nodes: ";
  outs() <<"{";
          for(auto sItr = exitNodes.begin(); sItr!=exitNodes.end();sItr++){
              long gpbNo = (*sItr)->getGPBNo();
              outs() << (sItr==exitNodes.begin() ? "": ", ");
              outs() <<gpbNo;
            }
  outs() <<" } \n";
}

long Partition::getPartitionId(){
     return partitionId;
}

set<GPB*,GPBComp> Partition::getGPBs(){
      return gpbs;
}

// @brief, for a coherent partition, all predecessors of any entry node of partition
set<long> Partition::getPredecessorsOfPartition(GPG *gpg){

    set<GPB*,GPBComp>::iterator sItr = entryNodes.begin();            

    set<long> preds = gpg->getEdgeIn()[(*sItr)->getGPBNo()];
    
    return preds;
}
//@brief, for a coherent partition, all successors of any exit node of partition
set<long> Partition::getSuccessorsOfPartition(GPG *gpg){

    set<GPB*,GPBComp>::iterator sItr = exitNodes.begin();

    set<long> succs = gpg->getEdgeOut()[(*sItr)->getGPBNo()];

    return succs;
}


bool Partition::partitionHasEntryNodeOfGPG(GPG *gpg){

    if(size()==1){

       set<long> preds = getPredecessorsOfPartition(gpg);
      
       if(preds.empty())
           return true;
       else
           return false;
    }
    else return false;
}

bool Partition::partitionHasExitNodeOfGPG(GPG *gpg){

   if(size()==1){
    
      set<long> succs = getSuccessorsOfPartition(gpg);

      if(succs.empty())
           return true;
        else
           return false;
   }
   else return false;
}