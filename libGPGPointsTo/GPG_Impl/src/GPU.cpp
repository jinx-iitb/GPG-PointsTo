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

#include "GPU.h"
#include "llvm/ADT/Twine.h"
#include "llvm/Support/raw_ostream.h"

bool GPUNodeComp::operator()(GPUNode *lhs, GPUNode *rhs) const {

  if (lhs->getNameOfVariable().compare(rhs->getNameOfVariable()) == -1)
    return true;
  else if (lhs->getNameOfVariable().compare(rhs->getNameOfVariable()) == 1)
    return false;
  else if (lhs->getIndirectList()->getIndirectionLevel() <
           rhs->getIndirectList()->getIndirectionLevel())
    return true;
  else if (lhs->getIndirectList()->getIndirectionLevel() >
           rhs->getIndirectList()->getIndirectionLevel())
    return false;
  else
    return false;
}

bool StringComp::operator()(char *lhs, char *rhs)const{

      int i;

      for( i=0;lhs[i]!='\0'&&rhs[i]!='\0';i++)
            if(lhs[i] < rhs[i]) return true;
            else if (lhs[i] > rhs[i]) return false;

      if(lhs[i]=='\0'&&rhs[i]=='\0') return false;

      if(lhs[i]=='\0') return true;

      if(rhs[i]=='\0') return false;

}



GlobalNode::GlobalNode(GlobalVariable *g, Indirection *il) : GPUNode(GLNODE) {
  gv = g;
  ilist = il;
}

StringRef GlobalNode::getNameOfVariable() { return gv->getName(); }

Indirection *GlobalNode::getIndirectList() { return ilist; }

GlobalVariable *GlobalNode::getGlobalVariable() { return gv; }

Type*  GlobalNode::getTypeofVariable() { return gv->getType()->getContainedType(0); }

//@brief int ***x then type of variable is int ***
// x at indirection level 1,  int ***
// x at indirection level 2, *x is of type int **
// x at indirection level 3, **x is of type int *
// x at indirection level 4, ***x is of type int (in Use nodes)
// x at indirection level 0, >4 not allowed
Type*  GlobalNode::getTypeOfVariableAtIndirection(int iLevel) {
   
   if(iLevel<=0)   return NULL;

   Type *tempType = getTypeofVariable();
   for(int i=1;i<iLevel;i++)    
       if(tempType->isPointerTy())
         tempType = tempType->getContainedType(0);
        else if(tempType->isStructTy())
            tempType = tempType->getContainedType(0);
       else return NULL;

    return tempType;
}

TmpNode::TmpNode(StringRef n, StringRef fName, Indirection *il,Type *t) : GPUNode(TNODE) {
  name = n;
  funName = fName;
  ilist = il;
  typeOfVariable=t;
}


Type*  TmpNode::getTypeofVariable() { return typeOfVariable; }

//@brief int ***x then type of variable is int ***
// x at indirection level 1,  int ***
// x at indirection level 2, *x is of type int **
// x at indirection level 3, **x is of type int *
// x at indirection level 4, ***x is of type int (in Use nodes)
// x at indirection level 0, >4 not allowed
Type*  TmpNode::getTypeOfVariableAtIndirection(int iLevel) {
   
   if(iLevel<=0)   return NULL;


   Type *tempType = getTypeofVariable();
  // outs()<<getNameOfVariable()<<"\n";
  // outs()<<"Temp contained type\t" << *tempType<<"\n";
   for(int i=1;i<iLevel;i++)    
       if(tempType->isPointerTy()) {
         tempType = tempType->getContainedType(0);
         //outs()<<"Temp contained type\t" << *tempType<<"\n";
       }
       else if(tempType->isStructTy())
            tempType = tempType->getContainedType(0);
       else return NULL;

    return tempType;
}


StringRef TmpNode::getNameOfVariable() { return name; }

Indirection *TmpNode::getIndirectList() { return ilist; }

UseNode::UseNode(StringRef n,long stNo,StringRef fname, Indirection *u) : GPUNode(UNODE) {
  // string u = "use";
  // string Nstr= std::to_string(insNo);
  // string n = u + Nstr;

  name = n;
  ilist = u;
  typeOfVariable=NULL;
  setUniqueName(n,stNo,fname);
}


Type*  UseNode::getTypeofVariable() { return typeOfVariable; }

Type*  UseNode::getTypeOfVariableAtIndirection(int iLevel) {
   
     if(iLevel == 1)  return typeOfVariable;
     else  return NULL;
}

void  UseNode::setUniqueName(StringRef name,long stmtNo,StringRef fileName){

     string lineNoStr    = std::to_string(stmtNo);
     string fName        = fileName;
     string  useName     = name;

     string useNodeString = useName + lineNoStr + fName;

     //outs()<<useNodeString<<" "<<useNodeString.length()<<" eee\n";

     char *useString = new char[useNodeString.length()+1];

     for (int i=0;i<useNodeString.length();i++)
           useString[i]= useNodeString.at(i);

         useString[useNodeString.length()]='\0';

     uniqueName = useString;

     //outs()<<uniqueName<<" \n";
}

StringRef UseNode::getNameOfVariable() { 

  return uniqueName;
}




Indirection *UseNode::getIndirectList() { return ilist; }

AllocationSiteNode::AllocationSiteNode(StringRef n, long site,
                                       StringRef fname, Indirection *a)
    : GPUNode(ANODE) {

  name = n;
  ilist = a;
  typeOfVariable = NULL;
  lineNo = site;
  setUniqueName(n,site,fname);
}


void AllocationSiteNode::setTypeofVariable(Type *t){
  
     typeOfVariable = t;
}


Type*  AllocationSiteNode::getTypeofVariable() { 

  return typeOfVariable;
}

Type*  AllocationSiteNode::getTypeOfVariableAtIndirection(int iLevel) {
   
    if(iLevel<=0)   return NULL;

   Type *tempType = getTypeofVariable();
   for(int i=1;i<iLevel;i++)    
       if(tempType->isPointerTy())
         tempType = tempType->getContainedType(0);
        else if(tempType->isStructTy())
            tempType = tempType->getContainedType(0);
       else return NULL;

    return tempType;
}

void  AllocationSiteNode::setUniqueName(StringRef name,long stmtNo,StringRef fileName){

     string lineNoStr    = std::to_string(stmtNo);
     string fName        = fileName;
     string  useName     = name;

     string useNodeString = useName + lineNoStr + fName;

     char *useString = new char[useNodeString.length()+1];

     for (int i=0;i<useNodeString.length();i++)
           useString[i]= useNodeString.at(i);

         useString[useNodeString.length()]='\0';

     uniqueName = useString;

  //   outs()<<uniqueName<<" \n";
}


StringRef AllocationSiteNode::getNameOfVariable() { return uniqueName; }

Indirection *AllocationSiteNode::getIndirectList() { return ilist; }

FPNode::FPNode(Value* val, Indirection *il) : GPUNode(FPNODE)
{
    variable = val;
    ilist = il;
}

StringRef FPNode::getNameOfVariable() { return variable->getName(); }

Indirection *FPNode::getIndirectList() { return ilist; }

Type* FPNode::getTypeofVariable() { return variable->getType();}

Type* FPNode::getTypeOfVariableAtIndirection(int i) { return NULL;}

Value* FPNode::getVariable() { return variable; }

bool GPUComp::operator()(GPU *lhs, GPU *rhs) const {
  if (lhs->isLessThan(rhs)) {
    // outs()<<"less \n";
    return true;
  } else {
    // outs()<<"not less \n";
    return false;
  }
}

GPU::GPU(GPUNode *l, GPUNode *r, long sNo, StringRef fname) {
  left = l;
  right = r;
  stmtNo = sNo;
  fileName = fname;
}

GPU::GPU(const GPU &copy) {

  // outs()<<"executed";
  left = copy.left;
  right = copy.right;
  stmtNo = copy.stmtNo;
  fileName = copy.fileName;
}

string GPU::dumpString(){
    string s;
        s += "(" + left->getNameOfVariable().str() + ";";

        s += std::to_string(left->getIndirectList()->getIndirectionLevel());

        //outs() << ")"
        s += ")-->(";
        s +=  right->getNameOfVariable().str() + ";";

        s +=  std::to_string(right->getIndirectList()->getIndirectionLevel()) + ")";
        return s.c_str();
}

void GPU::print(bool stmtIdInBracket) {

  if(left==NULL && right==NULL)
    outs()<< "Delta^{Top}";

  else {
   outs() << "( " << left->getNameOfVariable() << " , ";

   left->getIndirectList()->print();

   outs() << ")"
         << "-->"
         << "(" << right->getNameOfVariable() << " , ";

   right->getIndirectList()->print();

   outs() << ")";

   if(!stmtIdInBracket)
     outs() << " Stmt_Id: " << stmtNo;
   else
     outs()<<"["<<stmtNo<<"]";

  // outs()<<" Type: "<< *dataType;
  }

}

GPUNode *GPU::getSourceOfGPU() { return left; }

GPUNode *GPU::getTargetOfGPU() { return right; }

/// @brief sets data type of GPU, deprecated
//void GPU::setDataType(Type *t) { dataType = t; }
/// @brief get data type of GPU, deprecated
//Type *GPU::getDataType() { return dataType; }

/// @brief producer o consumer allowed or not
///  Indirection Levels of consumer,producer GPUs are (i,j),(k,l)
///  to allow TS composition l<=k<=j
bool GPU::isTSComp(GPU *producer) {

  GPUNode *sourceOfProducer = producer->getSourceOfGPU();
    GPUNode *targetOfConsumer = right;

    if (!sourceOfProducer->getNameOfVariable().equals(targetOfConsumer->getNameOfVariable()))
    {
        return false;
    }
    else
    {        
        int j = targetOfConsumer->getIndirectList()->getIndirectionLevel();
        int k = sourceOfProducer->getIndirectList()->getIndirectionLevel();
        int l = producer->getTargetOfGPU()->getIndirectList()->getIndirectionLevel();

        IndirectionList *target_consumer_list = dyn_cast<IndirectionList>(targetOfConsumer->getIndirectList());
        IndirectionList *source_producer_list = dyn_cast<IndirectionList>(sourceOfProducer->getIndirectList());
        IndirectionList *target_producer_list = dyn_cast<IndirectionList>(producer->getTargetOfGPU()->getIndirectList());

        vector<int> p;
        vector<int> target_consumer_field_list = (target_consumer_list == NULL) ? p : target_consumer_list->getFieldList();
        vector<int> source_producer_field_list = (source_producer_list == NULL) ? p : source_producer_list->getFieldList();
        vector<int> target_producer_field_list = (target_producer_list == NULL) ? p : target_producer_list->getFieldList();

        int len1 = (target_consumer_list == NULL) ? 0 : target_consumer_list->getNumberOfFields();
        int len2 = (source_producer_list == NULL) ? 0 : source_producer_list->getNumberOfFields();
        int len3 = (target_producer_list == NULL) ? 0 : target_producer_list->getNumberOfFields();

        if (target_consumer_list && source_producer_list)
        {            
            if (j != k)
            {
                return false; //[*,*] [*,n]
            }
            else
            {
                // [*,*] [*,*,n]
                if (len2 <= len1) // j + len1 + l + len3 - (k + len2) <= l + len3 and j == k
                {
                    for (int i = 0; i < len2; i++)
                    {
                        if (source_producer_field_list[i] != target_consumer_field_list[i])
                        {
                            return false;
                        }
                    }
                }
                else
                {
                    return false;
                }
            }
        }
        else if (!target_consumer_list && source_producer_list)
        {
            //source: [*] , target: [*]
            // struct node n1 *y,*x;
            // x = &a;
            // y = x;            
            if (len2 == 0)
            {
                if (k <= j && l + len3 <= k) // j - k + l + len3 <= j
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }            
        }
        else if (target_consumer_list && !source_producer_list)
        {   
            // int *z; struct node n1 **x, *y;            
            // *x = y;
            // z = x->n
            // source : [*,*], target : [*,n]                        
            if ( k <= j + len1 && l + len3 <= k) // j + len1 + l + len3 - k <= j + len1           
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (!target_consumer_list && !source_producer_list)
        {            
            if (k <= j && l + len3 <= k)
                return true; // j - k + l + len3 <= j
            return false;
        }        
        return true;        
    }
}

/// @brief producer o consumer allowed or not
///  Indirection Levels of consumer,producer GPUs are (i,j),(k,l)
///  to allow SS composition l<=k<i
bool GPU::isSSComp(GPU *producer) {

   GPUNode *sourceOfProducer = producer->getSourceOfGPU();
    GPUNode *targetOfProducer = producer->getTargetOfGPU();

    if (!sourceOfProducer->getNameOfVariable().equals(left->getNameOfVariable()))
    {
        return false;
    }
    else
    {
        int i = left->getIndirectList()->getIndirectionLevel();
        int k = sourceOfProducer->getIndirectList()->getIndirectionLevel();
        int l = targetOfProducer->getIndirectList()->getIndirectionLevel();

        IndirectionList* source_consumer_list = dyn_cast<IndirectionList>(left->getIndirectList());
        IndirectionList* source_producer_list = dyn_cast<IndirectionList>(sourceOfProducer->getIndirectList());
        IndirectionList* target_producer_list = dyn_cast<IndirectionList>(targetOfProducer->getIndirectList());

        vector<int> p;
        vector<int> target_consumer_field_list = (source_consumer_list == NULL) ? p : source_consumer_list->getFieldList();
        vector<int> source_producer_field_list = (source_producer_list == NULL) ? p : source_producer_list->getFieldList();
        vector<int> target_producer_field_list = (target_producer_list == NULL) ? p : target_producer_list->getFieldList();

        int len1 = (source_consumer_list == NULL) ? 0 : source_consumer_list->getNumberOfFields();
        int len2 = (source_producer_list == NULL) ? 0 : source_producer_list->getNumberOfFields();
        int len3 = (target_producer_list == NULL) ? 0 : target_producer_list->getNumberOfFields();

        if(source_consumer_list && source_producer_list)
        {            
            if(i != k){
                return false;
            }
            else{
                if(len2 < len1) // j + len1 + l + len3 - (k + len2) <= l + len3 and j == k
                {                    
                    for(int i = 0;i < len2 ;i++){
                        if(source_producer_field_list[i] != target_consumer_field_list[i]){
                            return false;
                        }
                    }
                } 
                else{
                    return false;
                }
            }

        }
        else if(!source_consumer_list && source_producer_list)
        {
            if(len2 == 0)
            {
                if(k < i && l + len3 <= k)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else{
                return false;
            }                        
        }
        else if(source_consumer_list && !source_producer_list)
        {            
            if(k < i + len1 && l + len3 <= k) // i + len1 <= k
            { 
                return true;
            }
            else
            {
                return false;
            }
        }
        else if(!source_consumer_list && !source_producer_list)
        {            
            if(k < i && l + len3 <= k) return true; // i - k + l + len3 <= i 
            return false;
        }        
        return true;
    }
}

/// @brief producer o consumer, TS composition
///  Indirection Levels of consumer,producer GPUs are (i,j),(k,l)
///  Indirection Levels of result is (i,l+j-k)

GPU *GPU::composeTS(GPU *producer) {

  if (!isTSComp(producer))
    return NULL;

  GPUNode *sourceOfProducer = producer->getSourceOfGPU();
  GPUNode *targetOfConsumer = right;
  GPUNode *targetOfProducer = producer->getTargetOfGPU();

  int j = targetOfConsumer->getIndirectList()->getIndirectionLevel();
  int k = sourceOfProducer->getIndirectList()->getIndirectionLevel();
  int l = producer->getTargetOfGPU()->getIndirectList()->getIndirectionLevel();

  Indirection* indlist_source_of_Producer = sourceOfProducer->getIndirectList();
  Indirection* indlist_target_of_Producer = targetOfProducer->getIndirectList();
  Indirection* indlist_target_of_Consumer = targetOfConsumer->getIndirectList();

  std::pair<int, vector<int>> derefsAndList = indlist_source_of_Producer->ListRemainder(indlist_target_of_Consumer);
  Indirection* listAfterRemainder;
  if(derefsAndList.second.empty()){
    listAfterRemainder = new Indirection(derefsAndList.first, 1, SINGLE);
  }
  else{
    listAfterRemainder = new IndirectionList(derefsAndList.first, 1, derefsAndList.second.size(), derefsAndList.second);
  }    

  Indirection* rList = listAfterRemainder->ListAppend(indlist_target_of_Producer);

  // outs()<< l << "  "<<k <<"  "<<j << "\n";

  // Indirection *rList = new Indirection(l + j - k, true, SINGLE);

  GPU *result;

  if (isa<GlobalNode>(targetOfProducer)) {

    GlobalVariable *gv = ((GlobalNode *)targetOfProducer)->getGlobalVariable();
    GPUNode *rightResult = new GlobalNode(gv, rList);
    result = new GPU(left, rightResult, getStmtNo(), getFileName());
  }

  //  boundary def reduction
  else if (isa<TmpNode>(targetOfProducer)) {

    /*  if(isa<GlobalNode>(sourceOfProducer)) {

        GlobalVariable *gv = ((GlobalNode *)
   sourceOfProducer)->getGlobalVariable();
        GPUNode *rightResult = new GlobalNode(gv,rList);
        result = new GPU(left,rightResult,getStmtNo(),getFileName());
   }*/

    GPUNode *rightResult =
        new TmpNode(targetOfProducer->getNameOfVariable(), getFileName(), rList, targetOfProducer->getTypeofVariable());
    result = new GPU(left, rightResult, getStmtNo(), getFileName());
      //outs() << "\n";
      //result->print();
    //if(result->left->getNameOfVariable().equals(result->right->getNameOfVariable())){
    //    result = NULL;
    //}

  }

  else if(isa<AllocationSiteNode>(targetOfProducer))
    {
        GPUNode *rightResult = new AllocationSiteNode("allocsite@",dyn_cast<AllocationSiteNode>(targetOfProducer)->getLineNo(), getFileName(), rList);
        dyn_cast<AllocationSiteNode>(rightResult)->setTypeofVariable(dyn_cast<AllocationSiteNode>(targetOfProducer)->getTypeofVariable());
        result = new GPU(left, rightResult, getStmtNo(), getFileName());        
    }
    else if(isa<FPNode>(targetOfProducer))
    {
        GPUNode* rightResult = new FPNode(dyn_cast<FPNode>(targetOfProducer)->getVariable(), rList);
        result = new GPU(left, rightResult, getStmtNo(), getFileName());
    }

  // test
 /* outs() << " TS composition\n";
  print();
  outs() << " Reduced to \t";
  result->print();
  outs() << "\n";*/

  return result;
}

/// @brief producer o consumer, SS composition
///  Indirection Levels of consumer,producer GPUs are (i,j),(k,l)
///  Indirection Levels of result is (l+i-k,j)

GPU *GPU::composeSS(GPU *producer) {

  if (!isSSComp(producer))
    return NULL;

  GPUNode *sourceOfProducer = producer->getSourceOfGPU();
  GPUNode *targetOfProducer = producer->getTargetOfGPU();
  GPUNode *sourceOfConsumer = left; 

  int i = left->getIndirectList()->getIndirectionLevel();
  int k = sourceOfProducer->getIndirectList()->getIndirectionLevel();
  int l = targetOfProducer->getIndirectList()->getIndirectionLevel();

  Indirection* indlist_source_of_Producer = sourceOfProducer->getIndirectList();
  Indirection* indlist_target_of_Producer = targetOfProducer->getIndirectList();
  Indirection* indlist_source_of_Consumer = sourceOfConsumer->getIndirectList();

  std::pair<int, vector<int>> derefsAndList = indlist_source_of_Producer->ListRemainder(indlist_source_of_Consumer);
  Indirection* listAfterRemainder;
  if(derefsAndList.second.empty()){
    listAfterRemainder = new Indirection(derefsAndList.first, 1, SINGLE);
  }
  else{
    listAfterRemainder = new IndirectionList(derefsAndList.first, 1, derefsAndList.second.size(), derefsAndList.second);
  }    

  Indirection* rList = listAfterRemainder->ListAppend(indlist_target_of_Producer);


    // Indirection *rList = new Indirection(l + i - k, true, SINGLE);

  GPU *result;

  if (isa<GlobalNode>(targetOfProducer)) {

    GlobalVariable *gv = ((GlobalNode *)targetOfProducer)->getGlobalVariable();
    GPUNode *leftResult = new GlobalNode(gv, rList);
    result = new GPU(leftResult, right, getStmtNo(), getFileName());
  }

  //  boundary def reduction
  else if (isa<TmpNode>(targetOfProducer)) {

    GPUNode *leftResult =
        new TmpNode(targetOfProducer->getNameOfVariable(), getFileName(), rList, targetOfProducer->getTypeofVariable());
    result = new GPU(leftResult, right, getStmtNo(), getFileName());
  }

  else if(isa<AllocationSiteNode>(targetOfProducer))
  {
    GPUNode *leftresult = new AllocationSiteNode("allocsite@",dyn_cast<AllocationSiteNode>(targetOfProducer)->getLineNo(), getFileName(), rList);
    dyn_cast<AllocationSiteNode>(leftresult)->setTypeofVariable(dyn_cast<AllocationSiteNode>(targetOfProducer)->getTypeofVariable());
    result = new GPU(leftresult, right, getStmtNo(), getFileName());
    // outs() << "\nnot handled in TS composition \n";
    // exit(0);
  }
  else if(isa<FPNode>(targetOfProducer))
  {
    GPUNode* leftResult = new FPNode(dyn_cast<FPNode>(targetOfProducer)->getVariable(), rList);
    result = new GPU(leftResult, right, getStmtNo(), getFileName());
  }

  // test print

 /* outs() << " SS composition\n";

  print();

  outs() << " Reduced to \t";

  result->print();

  outs() << "\n"; */

  return result;
}

string GPU::toString() {

//left, right NULL is a dummy GPU created for Top
  if(left==NULL && right==NULL)
     return "&#916;<SUB>T</SUB>";

  string leftName = left->getNameOfVariable();
  Indirection *tLeft = left->getIndirectList();
  string leftPart, rightPart;

  if (isa<IndirectionList>(tLeft)) {
    IndirectionList *ctLeft = (IndirectionList *)tLeft;
    string  indL = ctLeft->toString();
    leftPart = leftName + indL;
  } else
    leftPart = leftName + "," +
               std::to_string(left->getIndirectList()->getIndirectionLevel());

  // outs()<<leftPart<<"\n";

  string middlePart = "-->";
  string rightName = right->getNameOfVariable();

  Indirection *tRight = right->getIndirectList();

  if (isa<IndirectionList>(tRight)) {
    IndirectionList *ctRight = (IndirectionList *)tRight;
    rightPart = rightName + ctRight->toString();
  } else
    rightPart = rightName + "," +
                std::to_string(right->getIndirectList()->getIndirectionLevel());

  string endPart = " [" + std::to_string(stmtNo) + "]";

  string strGPU = leftPart + middlePart + rightPart + endPart;

  return strGPU;
}

long GPU::getStmtNo() { return stmtNo; }

StringRef GPU::getFileName() { return fileName; }

bool GPU::isLessThan(GPU *y) {

  /* outs()<<"GPUs isLessThan test \n";

   print();

   y->print();*/  

  GPUNode *leftOfY = y->getSourceOfGPU();
  GPUNode *rightOfY = y->getTargetOfGPU();

  if(!leftOfY && !rightOfY) return 0;

  Indirection *yLeftIndirection = leftOfY->getIndirectList();
  Indirection *yRightIndirection = rightOfY->getIndirectList();
 
  long stmtNoY = y->getStmtNo();
  StringRef fileNameY = y->getFileName();

  /// for structs we need add indirection level also

  if (stmtNo < stmtNoY)
    return true;
  else if (stmtNo > stmtNoY)
    return false;

  // compare returns -1 if it is lexographically less
  if (left->getNameOfVariable().compare(leftOfY->getNameOfVariable()) == -1)
    return true;
  else if (left->getNameOfVariable().compare(leftOfY->getNameOfVariable()) == 1)
    return false;

  if (right->getNameOfVariable().compare(rightOfY->getNameOfVariable()) == -1)
    return true;
  else if (right->getNameOfVariable().compare(rightOfY->getNameOfVariable()) ==
           1)
    return false;

  if (fileName.compare(fileNameY) == -1)
    return true;
  else if (fileName.compare(fileName) == 1)
    return false;
  else if(left->getIndirectList()->getIndirectionLevel() < yLeftIndirection->getIndirectionLevel())
    return true;
  else if (left->getIndirectList()->getIndirectionLevel() > yLeftIndirection->getIndirectionLevel())
    return false;    
  else if(right->getIndirectList()->getIndirectionLevel() < yRightIndirection->getIndirectionLevel())
    return false;
  else
    return false;
}

// @brief  Indirection Levels of GPU are (i,j)  where i>1 defines variable indirectly
bool GPU::isGPUIndirectlyDefinesVariable(){

    int i = left->getIndirectList()->getIndirectionLevel();
    if(i>1)  return true;
    else     return false;

}


//@brief type of variable this GPU defines
Type* GPU::typeOfDefinedVariable(){

    int i = left->getIndirectList()->getIndirectionLevel();
    int lenlist = llvm::isa<IndirectionList>(left->getIndirectList()) ? dyn_cast<IndirectionList>(left->getIndirectList())->getNumberOfFields() : 0;
    Type *type = left->getTypeOfVariableAtIndirection(i + lenlist);

    if(type!=NULL)  return type;
    else  {

     // outs()<<"typeOfDefinedVariable is called on Wrong GPU\n";
     // exit(0);
      return NULL;
    }
}


pair<set<char*,StringComp>,set<char*,StringComp>> GPU::typesOfDirectIndirectReferences(){

     int levelLeft = left->getIndirectList()->getIndirectionLevel();
     int lenlistLeft = llvm::isa<IndirectionList>(left->getIndirectList()) ? dyn_cast<IndirectionList>(left->getIndirectList())->getNumberOfFields() : 0;
     int levelRight = right->getIndirectList()->getIndirectionLevel();
     int lenlistRight = llvm::isa<IndirectionList>(right->getIndirectList()) ? dyn_cast<IndirectionList>(right->getIndirectList())->getNumberOfFields() : 0;
     set<char*,StringComp>  typesDirectRefSet,typesIndirectRefSet;
     string type_str,result;
     raw_string_ostream rso(type_str);


     for(int i=1;i<levelLeft + lenlistLeft;i++){

       Type *type = left->getTypeOfVariableAtIndirection(i);
       if(type!=NULL){
          
          type->print(rso);

          result = rso.str();
            
            char *cType = new char[result.length()+1];
            int j;

            for( j=0;j<result.length();j++)
                   cType[j]= result.at(j);

            cType[j]='\0';
            
            if(i>1)
              typesIndirectRefSet.insert(cType);
            else
              typesDirectRefSet.insert(cType);

            type_str.clear();
        }

     }

     for(int i=1;i<=levelRight+lenlistRight;i++){

       Type *type = right->getTypeOfVariableAtIndirection(i);
       if(type!=NULL){
          
          type->print(rso);

          result = rso.str();
            
            char *cType = new char[result.length()+1];
            int j;

            for( j=0;j<result.length();j++)
                   cType[j]= result.at(j);

            cType[j]='\0';
            
            if(i>1)
              typesIndirectRefSet.insert(cType);
            else
              typesDirectRefSet.insert(cType);

            type_str.clear();
        }

     }

     


     return make_pair(typesDirectRefSet,typesIndirectRefSet);

  }


//@brief types of set of References by left side of GPU
  set<char*,StringComp> GPU::typesOfReferencesLeft(){

     int level = left->getIndirectList()->getIndirectionLevel();
     int lenlistLeft = llvm::isa<IndirectionList>(left->getIndirectList()) ? dyn_cast<IndirectionList>(left->getIndirectList())->getNumberOfFields() : 0;

     set<char *, StringComp> typesSet;
     string type_str, result;
     raw_string_ostream rso(type_str);

     for (int i = 1; i < level + lenlistLeft; i++)
     {

       Type *type = left->getTypeOfVariableAtIndirection(i);
       if(type != NULL)
       {
       
          type->print(rso);

          result = rso.str();
            
            char *cType = new char[result.length()+1];
            int j;

            for( j=0;j<result.length();j++)
                   cType[j]= result.at(j);

            cType[j]='\0';

            typesSet.insert(cType);
            type_str.clear();
        }

     }

     return typesSet;

  }

 //@brief types of set of References by right side of GPU
  set<char*,StringComp> GPU::typesOfReferencesRight(){

     int level = right->getIndirectList()->getIndirectionLevel();
     int lenlistRight = llvm::isa<IndirectionList>(right->getIndirectList()) ? dyn_cast<IndirectionList>(right->getIndirectList())->getNumberOfFields() : 0;
     set<char*,StringComp>  typesSet;
     string type_str, result;
     raw_string_ostream rso(type_str);


     for(int i=1;i<=level+lenlistRight;i++){

       Type *type = right->getTypeOfVariableAtIndirection(i);
       if(type!=NULL){
          
          type->print(rso);
          
          result = rso.str();
            
            char *cType = new char[result.length()+1];
            int j;

            for(j=0;j<result.length();j++)
                   cType[j]= result.at(j);

            cType[j]='\0';

            typesSet.insert(cType);
            type_str.clear();
        }

     }

     return typesSet;

  }

//@brief union types of references left, right

set<char*,StringComp> GPU::unionTypesOfReferencesLeftRightOfGPU(){

 set<char*,StringComp>  leftRef = typesOfReferencesLeft();
 set<char*,StringComp>  rightRef = typesOfReferencesRight();

 set<char*,StringComp>  allRef;

 set<char*,StringComp>::iterator leftItr,rightItr;

 for(leftItr = leftRef.begin(); leftItr!=leftRef.end(); leftItr++)
          allRef.insert(*leftItr);

 for(rightItr = rightRef.begin(); rightItr!=rightRef.end(); rightItr++)
          allRef.insert(*rightItr);

    return allRef;
}



 bool GPU::isItDereferencing(){

 int i = left->getIndirectList()->getIndirectionLevel();
 int j = right->getIndirectList()->getIndirectionLevel();

    if( i>1 || j>1 )  return true;
    else     return false;
}



ComposeResult::ComposeResult(GPU *r,bool cOrNot,bool pOrNot){

    gpuResult  = r;
    composed = cOrNot;
    postponed  = pOrNot;

}


GPU* ComposeResult::getGPUResult(){
    return gpuResult;
}
bool ComposeResult::isComposed(){
    return composed;
}
bool ComposeResult::isPostponed(){
    return postponed; 
}

bool GPU::undesirableComposition(bool tsOrss,GPU *producer){

     GPUNode *sourceOfProducer = producer->getSourceOfGPU();
     GPUNode *targetOfProducer = producer->getTargetOfGPU();

     int k = sourceOfProducer->getIndirectList()->getIndirectionLevel();
     int l = targetOfProducer->getIndirectList()->getIndirectionLevel();
 
     //TScomposition
    if(tsOrss == true){

        if (sourceOfProducer->getNameOfVariable().equals(right->getNameOfVariable())) {

           if(l>k)  return true;
           else     return false;
           
        }
       else return false;
    }
    //SScomposition
    else  {

       if (sourceOfProducer->getNameOfVariable().equals(left->getNameOfVariable()))  {

           if(l>k)   return true;
           else      return false;
       }
       else return false;
    } 

}

ComposeResult* GPU::composeGPUs(bool tsOrss,GPU* producer,set<GPU*,GPUComp> blocked){

  bool composed, postponed;
  composed = false;
  postponed = false;
  GPU *result;
   
  // TScomposition 
  if(tsOrss == true)
     result = composeTS(producer);
  else
 // SScomposition
     result = composeSS(producer);

  // composition is successful
  if(result!=NULL){

      if(blocked.find(producer)==blocked.end())
          composed = true;
      else
          postponed = true; 
  }

  else if (undesirableComposition(tsOrss,producer))
      postponed = true;

  ComposeResult *cResult = new ComposeResult(result,composed,postponed);

  return cResult;
}

// c o In using blockedSet
pair<set<GPU*,GPUComp>,set<GPU*,GPUComp>> GPU::augmentedGPUReduction(set<GPU*,GPUComp> inSet,set<GPU*,GPUComp> blockedSet){

       set<GPU*,GPUComp>  wSet;

       set<GPU*,GPUComp>::iterator elem;
      
       set<GPU*,GPUComp> queuedSet, simplifiedGPUSet;

       wSet.insert(this);
       //print();
       while(!wSet.empty()) {

              elem = wSet.begin();
              GPU *first = *elem;
              wSet.erase(*elem);

              ComposeResult *resultTS, *resultSS;
              set<GPU*,GPUComp> tmpGPUSet;

              for(auto inElem = inSet.begin();inElem!=inSet.end();inElem++){
                
                  //(*inElem)->print();
                  resultTS = first->composeGPUs(true,*inElem,blockedSet);
                  resultSS = first->composeGPUs(false,*inElem,blockedSet);
                  //res

                  if(resultTS->isPostponed()||resultSS->isPostponed())
                      queuedSet.insert(*inElem);

                  if(resultTS->getGPUResult()!=NULL)
                      tmpGPUSet.insert(resultTS->getGPUResult());
                  else if(resultSS->getGPUResult()!=NULL)
                      tmpGPUSet.insert(resultSS->getGPUResult());
              }
              // reduced set
              if(tmpGPUSet.empty())
                 simplifiedGPUSet.insert(first);
              else{

                 for(auto itrT= tmpGPUSet.begin();itrT!=tmpGPUSet.end();itrT++)
                           wSet.insert(*itrT);
              }
        }
        return make_pair(simplifiedGPUSet,queuedSet);
 }

bool GPU::isDeltaTop()
{
    if(!left && !right)
    {
        if(stmtNo == -11 || stmtNo == -12)
        {
            return 1;
        }
    }
    return 0;
}

SpatialNode::SpatialNode(spatial::Token* token, Indirection* indirection) : GPUNode(BASENODE) {
    this->Node = token;
    this->indirection = indirection;
}

StringRef SpatialNode::getNameOfVariable() {
    if(this->Node->getValue() == NULL) return "";
    return this->Node->getName();
}

Indirection * SpatialNode::getIndirectList() {
    return this->indirection;
}

Type * SpatialNode::getTypeofVariable() {
    return this->Node->getValue()->getType();
}

Type * SpatialNode::getTypeOfVariableAtIndirection(int) {
    return this->getTypeofVariable();
}
