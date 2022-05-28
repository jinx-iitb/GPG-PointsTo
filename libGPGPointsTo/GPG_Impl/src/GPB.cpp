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
#include "GPB.h"
#include "Util.h"
#include "llvm/Support/raw_ostream.h"
#define FOR_EACH_ELEMENT(s, itr) for (itr = s.begin(); itr != s.end(); itr++)

using namespace llvm;

bool GPBComp::operator()(GPB *lhs, GPB *rhs) const {

  const long x = lhs->getGPBNo();
  const long y = rhs->getGPBNo();
  return x < y;
}

long GPB::currentGpbNo = 0;
GPB::GPB() {
  currentGpbNo++;
  gpbNo = currentGpbNo;
  recursiveCallBlock = false;
  isInlined = false;
}

GPB::GPB(GPU* gpu){
    currentGpbNo++;
    gpbNo = currentGpbNo;
    //outs()<<gpbNo<<"  e\n";
    set<GPU*, GPUComp> gpuSet;
    gpuSet.insert(gpu);
    GPUSet = gpuSet;
    recursiveCallBlock = false;
    isInlined = false;
}

GPB::GPB(set<GPU *, GPUComp> s) {
   // outs()<<"called";

  currentGpbNo++;
  gpbNo = currentGpbNo;
  //outs()<<gpbNo<<"  e\n";
  GPUSet = s;
  recursiveCallBlock = false;
  isInlined = false;
}

//only called for deep copy
GPB::GPB(long bNo){
  gpbNo = bNo;
  recursiveCallBlock = false;
  isInlined = false;
}

bool GPB::getisInlined() { return isInlined; }

void GPB::setisInlined(bool status) { isInlined = status; }

bool GPB::isEmpty() { return GPUSet.empty(); }

string GPB::dumpString() {
    set<GPU *, GPUComp>::iterator itr;
    string s;
    s += "GPB Block:" + std::to_string(gpbNo) + " {";

    FOR_EACH_ELEMENT(GPUSet, itr) {

        s += (*itr)->dumpString();
        s += ",";
    }
    s += '}';
    return s.c_str();
}

void GPB::print() {

  set<GPU *, GPUComp>::iterator itr;

  outs() << "GPB Block:" << gpbNo << "\n";

  FOR_EACH_ELEMENT(GPUSet, itr) {

    (*itr)->print();
    outs() << "\n";
  }
}

//special Block having Top value
void GPB::setAsRecursiveCallBlock(bool rec){
   recursiveCallBlock = rec;
}

bool GPB::isItRecursiveCallBlock(){
  return recursiveCallBlock;
}

long GPB::getGPBNo() { return gpbNo; }

set<GPU *, GPUComp> GPB::getGPUSet() {
  return GPUSet; 
}

void GPB::setGPUSet(set<GPU *, GPUComp> sSet) {
  
  /*set<GPU*,GPUComp> tmpSet;
  for(auto sItr=sSet.begin();sItr!=sSet.end();sItr++)
       tmpSet.insert(*sItr);*/

  // GPUSet = tmpSet;
  GPUSet = sSet;
}

void GPB::addSuccessor(GPB *succ) { succs.insert(succ); }

void GPB::addPredecessor(GPB *pred) { preds.insert(pred); }

void GPB::removeSuccessor(GPB *s) {

  set<GPB *, GPBComp>::iterator itrSuccSet, itrPredSet;

  FOR_EACH_ELEMENT(succs, itrSuccSet) {

    if ((*itrSuccSet)->getGPBNo() == s->getGPBNo()) {
      succs.erase(*itrSuccSet);
      break;
    }
  }
}

void GPB::removePredecessor(GPB *p) {

  set<GPB *, GPBComp>::iterator itrPredSet;

  FOR_EACH_ELEMENT(preds, itrPredSet) {

    if ((*itrPredSet)->getGPBNo() == p->getGPBNo()) {
      preds.erase(*itrPredSet);
      break;
    }
  }
}

void GPB::removeAllSuccessors(){
    succs.clear();
}

void GPB::removeAllPredecessors(){
    preds.clear();
}

set<GPB *, GPBComp> GPB::getAllSuccessors() { return succs; }

set<GPB *, GPBComp> GPB::getAllPredecessors() { return preds; }

string GPB::toString() {

  string gpbString;
  set<GPU *, GPUComp>::iterator itr;

  FOR_EACH_ELEMENT(GPUSet, itr) {

    gpbString.append((*itr)->toString());
    gpbString.append("\n");
  }

  return gpbString;
}


//@brief Deprecated, AugmentGPUreduction defined
/*
// R is the set of GPUs reaching the block.
// The GPUs in block are simplified or reduced( strength reduction)
set<GPU *, GPUComp> GPB::computeGPUReduction(set<GPU *, GPUComp> R) {

  set<GPU *, GPUComp> tmpGPUSet;

  set<GPU *, GPUComp>::iterator rItr;

  set<GPU *, GPUComp>::iterator gpuItr;

  set<GPU *, GPUComp>::iterator tItr;

  bool changeInGPUSet;

  set<GPU *, GPUComp> originalGPUSet = GPUSet;

  set<GPU *, GPUComp> simplifiedGPUSet;

  do {

    changeInGPUSet = false;

    simplifiedGPUSet.clear();

    // gamma1
    for (gpuItr = GPUSet.begin(); gpuItr != GPUSet.end(); gpuItr++) {

      set<GPU *, GPUComp> tmpGPUSet;

      // gamma2
      for (rItr = R.begin(); rItr != R.end(); rItr++) {

        GPU *tsC = (*gpuItr)->composeTS(*rItr);
        if (tsC != NULL)
          tmpGPUSet.insert(tsC);
        else {
          GPU *ssC = (*gpuItr)->composeSS(*rItr);
          if (ssC != NULL)
            tmpGPUSet.insert(ssC);
        }
      }

      if (tmpGPUSet.empty())
        simplifiedGPUSet.insert(*gpuItr);

      else {

        for (tItr = tmpGPUSet.begin(); tItr != tmpGPUSet.end(); tItr++) {

          simplifiedGPUSet.insert(*tItr);
        }
        changeInGPUSet = true;
      }
    }

    GPUSet = simplifiedGPUSet;

  } while (changeInGPUSet);

  GPUSet = originalGPUSet;

  if (simplifiedGPUSet.size() > 1)
    checkAndAddElmntToMayDefSet(simplifiedGPUSet);

  return simplifiedGPUSet;
} */

set<GPU *, GPUComp> GPB::computeKillSet(set<GPU *, GPUComp> genSet,
                                        set<GPU *, GPUComp> inSet) {

  set<GPU *, GPUComp> killSet;
  bool xAndUpwardX;
  
//   for(auto it : genSet)
//   {
//       if(isa<UseNode>(it->getSourceOfGPU()) && isa<FPNode>(it->getTargetOfGPU()) && it->getTargetOfGPU()->getIndirectList()->getIndirectionLevel() == 1)
//       {
//           killSet = inSet;
//           return killSet;
//       }
//   }    

  for (auto genItr = genSet.begin(); genItr != genSet.end(); genItr++) {

     GPUNode  *genLeft = (*genItr)->getSourceOfGPU();
 

      // does not belong to May Def set
     if(mayDefSet.find(genLeft)==mayDefSet.end()){

       for (auto inItr = inSet.begin(); inItr != inSet.end(); inItr++) {
          xAndUpwardX = false;
          
          GPUNode *inLeft = (*inItr)->getSourceOfGPU();
          
          // gen is upward exposed.
         if(genLeft->getNameOfVariable().count('\'')==1) {

            StringRef tStr = genLeft->getNameOfVariable();
            StringRef sRef = tStr.take_front(tStr.size()-1);

            if(sRef.equals(inLeft->getNameOfVariable())){

               Indirection *inLeftIn = inLeft->getIndirectList();
               Indirection *genLeftIn = genLeft->getIndirectList();
               // Checking if either InGPU or GenGPU has a list.
               if(isa<IndirectionList>(inLeftIn) || isa<IndirectionList>(genLeftIn))
               {
                   long inLevel = inLeftIn->getIndirectionLevel();
                   long genLevel = genLeftIn->getIndirectionLevel();
                   //Comparing number of *'s.
                   if(inLevel == genLevel)
                   {
                       IndirectionList* inLeftIlist = dyn_cast<IndirectionList>(inLeftIn);
                       IndirectionList* genLeftIlist = dyn_cast<IndirectionList>(genLeftIn);
                       // If both are list then check if the genGPU list is a prefix of inGPU list.
                       if(genLeftIlist && inLeftIlist)
                       {
                           vector<int> genlist = genLeftIlist->getFieldList();
                           vector<int> inlist = inLeftIlist->getFieldList();
                           if(genlist.size() <= inlist.size())
                           {
                               for(int i=0;i<genlist.size();i++)
                               {
                                   if(genlist[i] == inlist[i])
                                   {
                                       if(i == genlist.size() - 1)
                                            killSet.insert(*inItr);
                                   }
                                   else
                                   {
                                       break;
                                   }
                               }
                           }
                       }                       
                       // If genGPU has a list then it should have a size 0.
                       else if(genLeftIlist && !inLeftIlist)
                       {
                           if(genLeftIlist->getNumberOfFields() == 0)
                                killSet.insert(*inItr);
                       }
                       // If genGPU doesn't have a list and inLeftIlist has a list.
                       else
                       {
                           killSet.insert(*inItr);
                       }
                   }
               }
               // If Both GenGPU and inGPU doesn't have a list.
               else
               {
                    long inLevel = inLeftIn->getIndirectionLevel();
                    long genLevel = genLeftIn->getIndirectionLevel();

                    if (genLevel<=inLevel)
                        killSet.insert(*inItr);
               }
            }
                         
          }
           //|| xAndUpwardX==true

          if (inLeft->getNameOfVariable().equals(genLeft->getNameOfVariable())) {

             // upward exposed In
            if(inLeft->getNameOfVariable().count('\'')!=1) {

               Indirection *inLeftIn = inLeft->getIndirectList();
               Indirection *genLeftIn = genLeft->getIndirectList();
               // Checking if either InGPU or GenGPU has a list.
               if(isa<IndirectionList>(inLeftIn) || isa<IndirectionList>(genLeftIn))
               {
                   long inLevel = inLeftIn->getIndirectionLevel();
                   long genLevel = genLeftIn->getIndirectionLevel();
                   //Comparing number of *'s.
                   if(inLevel == genLevel)
                   {
                       IndirectionList* inLeftIlist = dyn_cast<IndirectionList>(inLeftIn);
                       IndirectionList* genLeftIlist = dyn_cast<IndirectionList>(genLeftIn);
                       // If both are list then check if the genGPU list is a prefix of inGPU list.
                       if(genLeftIlist && inLeftIlist)
                       {
                           vector<int> genlist = genLeftIlist->getFieldList();
                           vector<int> inlist = inLeftIlist->getFieldList();
                           if(genlist.size() <= inlist.size())
                           {
                               for(int i=0;i<genlist.size();i++)
                               {
                                   if(genlist[i] == inlist[i])
                                   {
                                       if(i == genlist.size() - 1)
                                            killSet.insert(*inItr);
                                   }
                                   else
                                   {
                                       break;
                                   }
                               }
                           }
                       }       
                       // If genGPU has a list then it should have a size 0.                
                       else if(genLeftIlist && !inLeftIlist)
                       {
                           if(genLeftIlist->getNumberOfFields() == 0)
                                killSet.insert(*inItr);
                       }
                       // If genGPU doesn't have a list and inLeftIlist has a list.
                       else
                       {
                           killSet.insert(*inItr);
                       }
                   }
               }
               // If Both GenGPU and inGPU doesn't have a list.
               else
               {
                    long inLevel = inLeftIn->getIndirectionLevel();
                    long genLevel = genLeftIn->getIndirectionLevel();

                    if (genLevel<=inLevel)
                        killSet.insert(*inItr);
               }
            }
          
          }

        }
      }
  }

  return killSet;  
}

set<GPU *, GPUComp> GPB::computeInMinusKill(set<GPU *, GPUComp> inSet,
                                        set<GPU *, GPUComp> killSet) {

  set<GPU *, GPUComp> inMinusKillGPUSet;

  for (auto inItr = inSet.begin(); inItr != inSet.end(); inItr++) {
                 // not there in Kill set
                if(killSet.find(*inItr)==killSet.end())
                    inMinusKillGPUSet.insert(*inItr);

  }
  
  return inMinusKillGPUSet;
}

void GPB::checkAndAddElmntToMayDefSet(set<GPU *, GPUComp> genSet, set<GPU*,GPUComp> indirectDef) {

  set<GPUNode *, GPUNodeComp>::iterator nItr;

  map<long, set<GPUNode *, GPUNodeComp>> stmtIdtoSourceGPU;

  set<GPU *, GPUComp>::iterator gpuItr;

  map<long, set<GPUNode *, GPUNodeComp>>::iterator stmtToSGPUitr;

  set<long>  stmtIdsWithIndirectDefs;

  for(auto iItr= indirectDef.begin(); iItr!=indirectDef.end();iItr++)
         stmtIdsWithIndirectDefs.insert((*iItr)->getStmtNo());

  for (gpuItr = genSet.begin(); gpuItr != genSet.end(); gpuItr++) {

      long stmtNo = (*gpuItr)->getStmtNo();
      if(stmtIdsWithIndirectDefs.find(stmtNo)!=stmtIdsWithIndirectDefs.end())
    stmtIdtoSourceGPU[stmtNo].insert(
        (*gpuItr)->getSourceOfGPU());
  }

  for (stmtToSGPUitr = stmtIdtoSourceGPU.begin();
       stmtToSGPUitr != stmtIdtoSourceGPU.end(); stmtToSGPUitr++) {

    if ((*stmtToSGPUitr).second.size() > 1) {

      for (nItr = (*stmtToSGPUitr).second.begin();
           nItr != (*stmtToSGPUitr).second.end(); nItr++)
        addElmntToMayDefSet(*nItr);
    }
  }
}

void GPB::addElmntToMayDefSet(GPUNode *n) {

 /* outs() << "Added to " << gpbNo << " MayDef Set: (" << n->getNameOfVariable()
         << "," << n->getIndirectList()->getIndirectionLevel() << ") \n"; */

  mayDefSet.insert(n);
}


set<GPUNode*,GPUNodeComp> GPB::getMayDefSet(){
     return mayDefSet;
}

void GPB::setMayDefSet(set<GPUNode*,GPUNodeComp> mDef){
     mayDefSet = mDef;
}

set<GPU*,GPUComp> GPB::findGPUsHavingIndirectDefinitions(set<GPU*,GPUComp> genSet){

  set<GPU *, GPUComp>::iterator itr;
  set<GPU*,GPUComp>  gpusGiveInddefs;

  FOR_EACH_ELEMENT(genSet, itr) {
      
      if((*itr)->isGPUIndirectlyDefinesVariable()) 
              gpusGiveInddefs.insert((*itr));
  }

  return gpusGiveInddefs;
}

set<char*,StringComp> GPB::getTypesOfSetOfDefinitions(set<GPU*,GPUComp> genOrInSet){

  set<GPU *, GPUComp>::iterator itr;
  set<char*,StringComp>  typesSet;
  string type_str, result;

  FOR_EACH_ELEMENT(genOrInSet, itr) {

        Type *type = (*itr)->typeOfDefinedVariable();
      
        if(type!=NULL) {
          
            raw_string_ostream rso(type_str);
            type->print(rso);
            
            result = rso.str();

            //outs()<<"\n Type"<< result<<"\n";
            
            char *cType = new char[result.length()+1];

            int i;

            for(i=0;i<result.length();i++)
                   cType[i]= result.at(i);

            cType[i]='\0';

            typesSet.insert(cType);

           //(*itr)->print();
           // outs()<<"\n Type of DefinedVariable: "<< cType <<"\n";

            type_str.clear();
        }

  }

  return typesSet;
}

//@brief which includes both left, right side
set<char*,StringComp> GPB::getTypesOfSetOfReferences( set<GPU*,GPUComp> inSet){

  set<GPU *, GPUComp>::iterator itr;
  set<char*,StringComp>  typesSet;
  set<char*,StringComp>::iterator typeItr;


  FOR_EACH_ELEMENT(inSet, itr) {

      set<char*,StringComp> gpuTypeRefSet =(*itr)->unionTypesOfReferencesLeftRightOfGPU();

      FOR_EACH_ELEMENT(gpuTypeRefSet, typeItr){

            typesSet.insert(*typeItr);
     }

  }

  return typesSet;  
}

 bool  GPB::isNoDependenciesInDefRefTypesCommon(set<GPU*,GPUComp> barrierSet,set<GPU*,GPUComp> inSet){

    set<char*,StringComp>  typesDefBarrierSet;
    set<char*,StringComp>  typesRefDefInSet;
    set<char*,StringComp>  typesDefInSet;

    typesDefBarrierSet = getTypesOfSetOfDefinitions(barrierSet);

    // initially Def is empty
    typesRefDefInSet = getTypesOfSetOfReferences(inSet);

    typesDefInSet = getTypesOfSetOfDefinitions(inSet);

    // TDef(B) intersection (TRef(B) union TDef(I))

    // first Tref(B) union TDef(I)

    set<char*,StringComp>::iterator typeItr;
     
    FOR_EACH_ELEMENT(typesDefInSet, typeItr){

            typesRefDefInSet.insert(*typeItr);
    }

   /* outs()<<"\nBarrier Set \n";

    FOR_EACH_ELEMENT(typesDefBarrierSet, typeItr){
     outs()<<*typeItr;

    }

    outs()<<"\ntypesRefDefInSet \n";

    FOR_EACH_ELEMENT(typesDefBarrierSet, typeItr){

     outs()<<*typeItr;
    } */


   // TDef(B) intersection (TRef(B) union TDef(I)) empty or not

    FOR_EACH_ELEMENT(typesDefBarrierSet, typeItr){

            // not empty
            if(typesRefDefInSet.count(*typeItr)!=0)
                return false;
    }
    
     return true;
 }


 set<GPU*,GPUComp> GPB::getBlockedGPUs(set<GPU*,GPUComp> inSet,set<GPU*,GPUComp> genSet){

     set<GPU *, GPUComp>::iterator itr;

     set<GPU*,GPUComp> blockedGPUs;

     set<GPU*,GPUComp> gammaSet;   // singleton set gamma

     set<GPU*,GPUComp> genGPUsIndirectDef = findGPUsHavingIndirectDefinitions(genSet);

    if(genGPUsIndirectDef.size()>=1) {
     
      FOR_EACH_ELEMENT(inSet, itr) {

         gammaSet.insert(*itr);
         
         if(!isNoDependenciesInDefRefTypesCommon(genGPUsIndirectDef,gammaSet))
               blockedGPUs.insert(*itr);

         gammaSet.clear();
      }

    }
    else {
        // outs()<<"here \n";
      
      FOR_EACH_ELEMENT(inSet, itr) {

         if((*itr)->isGPUIndirectlyDefinesVariable()) {
           
              gammaSet.insert(*itr);
         
              if(!isNoDependenciesInDefRefTypesCommon(genSet,gammaSet))
                  blockedGPUs.insert(*itr);

              gammaSet.clear();
            }
      }
                 
    }

    return blockedGPUs;
 }

 
 pair<set<GPU*,GPUComp>,set<GPU*,GPUComp>> GPB::augmentedGPUReductionOverBlock(set<GPU*,GPUComp> inSet,set<GPU*,GPUComp> blockedSet){
      Util util;
      //util.print(inSet);
      //outs() << "\n";
      pair<set<GPU*,GPUComp>,set<GPU*,GPUComp>>  compResult;
      set<GPU*,GPUComp> simplifiedGPUSet;
      set<GPU*,GPUComp> undesriableSet;

      set<GPU*,GPUComp>  gpusMayProduceMayDefs = findGPUsHavingIndirectDefinitions(GPUSet);
      //util.print(gpusMayProduceMayDefs);
      for (auto gpuItr = GPUSet.begin(); gpuItr != GPUSet.end(); gpuItr++) {
        //  outs() << "inside Augmented GPU reduction over block function.\n";
             
         compResult = (*gpuItr)->augmentedGPUReduction(inSet,blockedSet);
        //util.print(compResult.first);
        //  outs() << "After Augmented GPU reduction.\n";
         for(auto Itr= compResult.first.begin(); Itr!=compResult.first.end();Itr++)
                simplifiedGPUSet.insert(*Itr);

         
              if (simplifiedGPUSet.size() > 1) {

                if(gpusMayProduceMayDefs.size()>=1)

                checkAndAddElmntToMayDefSet(simplifiedGPUSet,gpusMayProduceMayDefs);

              }

         for(auto Itr= compResult.second.begin(); Itr!=compResult.second.end();Itr++)
                  undesriableSet.insert(*Itr);

       }      


       return make_pair(simplifiedGPUSet,undesriableSet);

 }

 


  bool GPB::isDependent(set<GPU*,GPUComp> outM){

      bool isItOutDeref = isItHasDereferencingGPU(outM);
      bool isItdeltaDeref = isItHasDereferencingGPU(GPUSet);

      Util util; //debug printing

    // deref(X) V deref(Y) is true
     if(isItOutDeref || isItdeltaDeref) {

    // check Tdef(Y) U Tref(Y) intersection Tdef(X-Y) not empty
    //  util.print(outM);

     // outs()<<"......ee\n";
      set<GPU*,GPUComp> remGPUSet;

      for(auto itr= outM.begin(); itr!=outM.end();itr++){
               if(GPUSet.find(*itr)==GPUSet.end())
                    remGPUSet.insert(*itr);
      }

      //util.print(remGPUSet);
      //util.print(GPUSet);     
      // initially it contains only def types
      set<char*,StringComp> defAndRefTypes = getTypesOfSetOfDefinitions(GPUSet);
      
      set<char*,StringComp>::iterator typeItr;
     
      /*FOR_EACH_ELEMENT(defAndRefTypes, typeItr){
              outs()<<*typeItr<<"\n";
      }*/

      set<char*,StringComp> refTypes = getTypesOfSetOfReferences(GPUSet);

      for(auto itr = refTypes.begin(); itr!=refTypes.end();itr++)
                   defAndRefTypes.insert(*itr);

      /*FOR_EACH_ELEMENT(defAndRefTypes, typeItr){
              outs()<<*typeItr<<"\n";
      }*/

      set<char*,StringComp> defTypesRemaining = getTypesOfSetOfDefinitions(remGPUSet);

      /*FOR_EACH_ELEMENT(defTypesRemaining, typeItr){
              outs()<<*typeItr<<"\n";
      }*/
      
       for(auto itr = defAndRefTypes.begin(); itr!=defAndRefTypes.end();itr++)
                if(defTypesRemaining.find(*itr)!=defTypesRemaining.end())
                          return true;
      return false;
    }

    else return false;

}

bool GPB::isItHasDereferencingGPU(set<GPU*,GPUComp> outOrdeltaSet){

      for(auto itr = outOrdeltaSet.begin();itr!=outOrdeltaSet.end();itr++)
                if((*itr)->isItDereferencing()==true)
                    return true;
     //all are non-dereferencing
      return false;
}

set<GPU*,GPUComp> GPB::computeGPUFlow(set<GPU*,GPUComp> outM, bool coalesceInN){

    set<GPU*,GPUComp> empty;

   // if(isDependentByMehul(outM))
   //   outs()<<"There is dependency  "<<gpbNo << "\n";
     
    if (!coalesceInN || isDependent(outM))
         return empty;
    else
         return outM;
}

bool GPB::coalesceOrNot(bool coalesceOutM,bool coalesceInN,set<GPU*,GPUComp> outM){

       set<GPU*,GPUComp> resGPUflow = computeGPUFlow(outM,coalesceInN);
       
       if(coalesceOutM && (outM.empty() || !resGPUflow.empty()))
            return true;
       else
            return false;
}


bool GPB::isItPredOfNode(GPB *p){

    set<GPB *, GPBComp>::iterator itrPredSet;

  FOR_EACH_ELEMENT(preds, itrPredSet) {

    if ((*itrPredSet)->getGPBNo() == p->getGPBNo()) {
           return true;
    }
  }

  return false;

}


bool GPB::isItSuccOfNode(GPB *s){

  set<GPB *, GPBComp>::iterator itrSuccSet;

  FOR_EACH_ELEMENT(succs, itrSuccSet) {

    if ((*itrSuccSet)->getGPBNo() == s->getGPBNo()) {
           return true;
    }
  }

  return false;

}


 bool GPB::isDependentByMehul(set<GPU*,GPUComp> outM ){

    bool isItOutDeref = isItHasDereferencingGPU(outM);
      bool isItdeltaDeref = isItHasDereferencingGPU(GPUSet);

    // deref(X) V deref(Y) is true
     if(isItOutDeref || isItdeltaDeref) {
         // check Tdef(Y) U Tref(Y) intersection Tdef(X-Y) not empty

      set<GPU*,GPUComp> remGPUSet;

      for(auto itr= outM.begin(); itr!=outM.end();itr++){

               if(GPUSet.find(*itr)==GPUSet.end())
                    remGPUSet.insert(*itr);
      }


     pair<set<char*,StringComp>,set<char*,StringComp>> directIndirectDefsXminusY= getTypesOfSetOfDirectIndirectDefs(remGPUSet);
     set<char*,StringComp>  directDefsXminusY = directIndirectDefsXminusY.first;
     set<char*,StringComp>  indirectDefsXminusY = directIndirectDefsXminusY.second;
     

      // initially it contains only def types
      set<char*,StringComp> defAndRefTypes = getTypesOfSetOfDefinitions(GPUSet);
      
      set<char*,StringComp> refTypes = getTypesOfSetOfReferences(GPUSet);

      for(auto itr = refTypes.begin(); itr!=refTypes.end();itr++)
                   defAndRefTypes.insert(*itr);
      
       for(auto itr = defAndRefTypes.begin(); itr!=defAndRefTypes.end();itr++)
                if(indirectDefsXminusY.find(*itr)!=indirectDefsXminusY.end())
                          return true;


      pair<set<char*,StringComp>,set<char*,StringComp>> directIndirectDefsY = getTypesOfSetOfDirectIndirectDefs(GPUSet);

      pair<set<char*,StringComp>,set<char*,StringComp>> directIndirectRefsY = getTypesOfSetOfDirectIndirectRefs(GPUSet);
      
      // initially it contains only def types
      set<char*,StringComp> indirectDefsAndRefsY = directIndirectDefsY.second;

      set<char*,StringComp> indirectRefsY = directIndirectRefsY.second;

      for(auto itr = indirectRefsY.begin(); itr!=indirectRefsY.end();itr++)
                   indirectDefsAndRefsY.insert(*itr);
      
       for(auto itr = indirectDefsAndRefsY.begin(); itr!= indirectDefsAndRefsY.end();itr++)
                if(directDefsXminusY.find(*itr)!=directDefsXminusY.end())
                          return true;


      return false;

    }

    else return false;

 }


pair<set<char*,StringComp>,set<char*,StringComp>> GPB::getTypesOfSetOfDirectIndirectDefs(set<GPU*,GPUComp> genOrInSet){

  set<GPU *, GPUComp>::iterator itr;
  set<char*,StringComp>  typesDirectSet;
  set<char*,StringComp>  typesIndirectSet;

  string type_str, result;

  FOR_EACH_ELEMENT(genOrInSet, itr) {

        
        Type *type = (*itr)->typeOfDefinedVariable();
      
        if(type!=NULL) {
          
            raw_string_ostream rso(type_str);
            type->print(rso);
            
            result = rso.str();

            //outs()<<"\n Type"<< result<<"\n";
            
            char *cType = new char[result.length()+1];

            int i;

            for(i=0;i<result.length();i++)
                   cType[i]= result.at(i);

            cType[i]='\0';
            
            if((*itr)->isGPUIndirectlyDefinesVariable())
               typesIndirectSet.insert(cType);
            else
               typesDirectSet.insert(cType);     
           //(*itr)->print();
           // outs()<<"\n Type of DefinedVariable: "<< cType <<"\n";

            type_str.clear();
        }

  }

  return make_pair(typesDirectSet,typesIndirectSet);
}



//@brief which includes both left, right side
pair<set<char*,StringComp>,set<char*,StringComp>> GPB::getTypesOfSetOfDirectIndirectRefs( set<GPU*,GPUComp> inSet){

  set<GPU *, GPUComp>::iterator itr;
  set<char*,StringComp>  typesDirectSet,typesIndirectSet;
  set<char*,StringComp>::iterator typeItr;
  set<char*,StringComp>  typesTmpDirectSet,typesTmpIndirectSet;

  pair<set<char*,StringComp>,set<char*,StringComp>> typesDirectIndirectSet;

  FOR_EACH_ELEMENT(inSet, itr) {

      typesDirectIndirectSet =(*itr)->typesOfDirectIndirectReferences();
      typesTmpDirectSet     = typesDirectIndirectSet.first;
      typesTmpIndirectSet   = typesDirectIndirectSet.second;

      FOR_EACH_ELEMENT(typesTmpDirectSet, typeItr){

            typesDirectSet.insert(*typeItr);
     }

      FOR_EACH_ELEMENT(typesTmpIndirectSet, typeItr){

            typesIndirectSet.insert(*typeItr);
     }

  }

  return make_pair(typesDirectSet,typesIndirectSet);  
}


void GPB::setRGBlockingIn(set<GPU*,GPUComp> rIn){

   reachingGPUBlockingIn = rIn;

}

set<GPU*,GPUComp> GPB::getRGBlockingIn(){

   return reachingGPUBlockingIn;
}

void GPB::setRGBlockingOut(set<GPU*,GPUComp> rOut){

   reachingGPUBlockingOut = rOut;
}

set<GPU*,GPUComp> GPB::getRGBlockingOut(){

  return reachingGPUBlockingOut;
}

void GPB::setAllSuccessors(set<GPB*,GPBComp> newsucc){

    succs = newsucc;

}

void GPB::setAllPredecessors(set<GPB*,GPBComp> newpred){

   preds = newpred;
}

