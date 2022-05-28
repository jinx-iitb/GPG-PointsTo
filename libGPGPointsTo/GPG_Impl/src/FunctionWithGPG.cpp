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
#include "FunctionWithGPG.h"
#include "GPB.h"
#include "GPU.h"
#include "IndirectionList.h"
#include "llvm/Support/Casting.h"
#include "Util.h"
#include "llvm/ADT/Twine.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/CallSite.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/Operator.h"
#include "llvm/IR/Instruction.h"

#define FOR_EACH_ELEMENT(s) for (itr = s.begin(); itr != s.end(); itr++)
#define FOR_EACH_ELEMENT_MAP(m, itr) \
    for (itr = m.begin(); itr != m.end(); itr++)
#define FOR_EACH_ELEMENT_OF_VECTOR(v) for (int i = 0; i < v.size(); i++)
#define FOR_EACH_BASICBLOCK(function) for (auto &BB : function)
#define FOR_EACH_INSTRUCTION(basicblock) for (auto &I : basicblock)

#define FOR_EACH_ELEMENT_WITHITR(s, itr) \
    for (itr = s.begin(); itr != s.end(); itr++)

FunctionWithGPG::FunctionWithGPG(Function *f) { fun = f; }

void FunctionWithGPG::setDumpPointsTo(bool dump)
{
    dumpPointsTo = dump;
}

void FunctionWithGPG::setBoundrayDef(SymbolTableList<GlobalVariable> &gl,
                                     map<StringRef, char *> gToB)
{
    set<GPU *, GPUComp> gpuSet;
    for (auto &Global : gl)
    {

        Type *typeOfVarInSourceProgram = Global.getType()->getContainedType(0);
        Type *type = Global.getType()->getContainedType(0);
        int level = 1;
        StringRef upExposedGlobal = gToB[Global.getName()];

        if (fun->getName().equals("main"))
        {
            if (type->isPointerTy() && Global.hasInitializer())
            {
                if (Value *v = dyn_cast<Value>(Global.getInitializer()))
                {
                    if (GlobalVariable *gv = dyn_cast<GlobalVariable>(v))
                    {

                        Indirection *gil = new Indirection(1, true, SINGLE);
                        GPUNode *left = new GlobalNode(&Global, gil);
                        Indirection *til = new Indirection(0, true, SINGLE);
                        GPUNode *right = new GlobalNode(gv, til);
                        StringRef blank;
                        GPU *gpu = new GPU(left, right, 0, blank);
                        gpuSet.insert(gpu);
                        continue;
                    }
                }
            }
        }
        while (type->isPointerTy())
        {
            // outs()<<"setting Boundary Definitions \t:"<<Global.getName()<<"\n";
            Indirection *gil = new Indirection(level, true, SINGLE);
            GPUNode *left = new GlobalNode(&Global, gil);
            Indirection *til = new Indirection(level, true, SINGLE);
            StringRef blank;
            GPUNode *right = new TmpNode(upExposedGlobal, blank, til, typeOfVarInSourceProgram);
            GPU *gpu = new GPU(left, right, 0, blank);
            // deprecated
            //gpu->setDataType(Global.getType()->getContainedType(0));
            // outs() << Global.getName() << "\t" << *(gpu->getDataType()) << "\n";
            // gpu->print();
            gpuSet.insert(gpu);
            type = type->getContainedType(0);
            // below line need to removed later
            // if(level==1)  break;
            level++;
        }
    }
    boundaryDef = gpuSet;
}

set<GPU *, GPUComp> FunctionWithGPG::getBoundaryDef() { return boundaryDef; }

void FunctionWithGPG::addVariableToTempMap(string tempName, GPUNode *n)
{
    // outs()<< tempname <<"  test:\n" ;
    // outs()<< n->get_name_of_variable() <<"  test:\n" ;
    vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(tempName);
    listOfNodes.push_back(n);
    tempToVariableSet[tempName] = listOfNodes;
}

vector<GPUNode *> FunctionWithGPG::getListOfNodesMappedToTemp(string tempName)
{
    vector<GPUNode *> vNodes;
    if (tempToVariableSet.find(tempName) != tempToVariableSet.end())
        return tempToVariableSet[tempName];
    else
        return vNodes;
}

/* this needs to be changed to optimized later */
GPG *FunctionWithGPG::getSummary() { return summary; }

/**
 *
 * @param I
 */

void FunctionWithGPG::preProcessMallocCallocCalls(Instruction &I)
{

    CallSite cs = CallSite(cast<CallInst>(&I));
    string tempName = I.getName();
    long lineNo;
    StringRef fileName;
    Util util;
    /*get line number and file name */
    if (I.hasMetadata())
    {
        MDNode *node = I.getMetadata("dbg");
        if (DILocation *loc = dyn_cast<DILocation>(node))
        {
            lineNo = loc->getLine();
            fileName = loc->getFilename();
        }
    }
    else
        util.debugInfoErrorMsg(I);
    if (!cs.isIndirectCall())
    {
        StringRef funMalloc("malloc");
        StringRef funCalloc("calloc");
        if (!cs.getCalledFunction())
        {
            return;
        }
        StringRef funName = cs.getCalledFunction()->getName();
        if (funName.equals(funMalloc) || funName.equals(funCalloc))
        {

            Indirection *til = new IndirectionList(0, false);
            GPUNode *tn = new AllocationSiteNode("allocsite@", lineNo,
                                                 fileName, til);
            addVariableToTempMap(tempName, tn);
        }
    }
}
/* for processing instruction like
  %tmp8 = bitcast i8* %tmp7 to %struct.node*
*/
void FunctionWithGPG::preProcessBitCastInstruction(Instruction &I)
{

    string tempName = I.getName();
    Value *sourceOpr = I.getOperand(0);
    //  outs() << sourceOpr->getName()<<"\n";
    if (GlobalVariable *gv = dyn_cast<GlobalVariable>(sourceOpr))
    {
        Indirection *til = new Indirection(0, true, SINGLE);
        GPUNode *tn = new GlobalNode(gv, til);
        addVariableToTempMap(tempName, tn);
        return;
    }
    vector<GPUNode *> listOfNodes =
        getListOfNodesMappedToTemp(sourceOpr->getName());

    FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
    {
        //outs() << sourceOpr->getName()<<" \n";
        if (isa<AllocationSiteNode>(listOfNodes[i]))
        {
            ((AllocationSiteNode *)listOfNodes[i])->setTypeofVariable(I.getType());
            addVariableToTempMap(tempName, listOfNodes[i]);
        }
        else if (isa<GlobalNode>(listOfNodes[i]))
        {
            addVariableToTempMap(tempName, listOfNodes[i]);
        }
        else if (isa<TmpNode>(listOfNodes[i]))
        {
            addVariableToTempMap(tempName, listOfNodes[i]);
        }
    }
}

bool FunctionWithGPG::isUpwardExposed(StringRef var)
{
    if (upwardExposedToGlobalVariable.find(var) != upwardExposedToGlobalVariable.end())
        return true;
    else
        return false;
}

void FunctionWithGPG::setupwardExposedVersionOfGlobalVar(SymbolTableList<GlobalVariable> &gl, map<StringRef, char *> gToB)
{
    for (auto &Global : gl)
    {
        Type *type = Global.getType()->getContainedType(0);
        StringRef upExposedGlobal = gToB[Global.getName()];
        if (type->isPointerTy())
        {
            globalToUpwardExposedVersion.insert(make_pair(Global.getName(), upExposedGlobal));
            upwardExposedToGlobalVariable.insert(make_pair(upExposedGlobal, &Global));
        }
    }
}

/* pre-processing to remove unwanted temporaries
find the relation between temporaries and global variables */
void FunctionWithGPG::preProcessFunction()
{
    //llvm::MemorySSA somename(*fun, NULL, NULL);
    FOR_EACH_BASICBLOCK(*fun)
    {

        FOR_EACH_INSTRUCTION(BB)
        {
            //somename.getMemoryAccess(&I);
            outs() << I << "\n";
            //outs() << I.getOpcodeName() << "--" <<
            //    I.getOpcode() << " " << I.getValueID() << " " << Intrinsic::dbg_declare << "\n";
            switch (I.getOpcode())
            {
            case Instruction::Load:
            { // resultant operand
                Value *ropr = dyn_cast<Value>(&I);
                // filter pointer operations only
                // if required add ropr->getType()->getContainedType(0)->isPointerTy()
                if (ropr->getType()->isPointerTy())
                {
                    // outs()<<ropr->getName()<<"\n";
                    preProcessLoadInstruction(I);
                }
                break;
            }
            case Instruction::GetElementPtr:
                preProcessGEPInstruction(I);
                break;
            case Instruction::Ret:
            {
                ReturnInst *rI = dyn_cast<ReturnInst>(&I);
                if (Value *v = rI->getReturnValue())
                    if (v->getType()->isPointerTy())
                        preprocessPointerReturnInstruction(rI);
                break;
            }

            case Instruction::PHI:
                if (I.getType()->isPointerTy())
                    preProcessPHIInstruction(I);
                break;
            case Instruction::BitCast:
                preProcessBitCastInstruction(I);
                break;
            case Instruction::Call:
                preprocessCallInstruction(I);
                break;
            }
        } // end of Instruction block
    }     // end of basic block
} // end function

void FunctionWithGPG::preprocessCallInstruction(Instruction &I){
    preProcessMallocCallocCalls(I);
    if (DbgDeclareInst *dbgDeclare = dyn_cast<DbgDeclareInst>(&I))
        preProcessDebugDeclareInstruction(dbgDeclare);
    else if (DbgValueInst *dbgValue = dyn_cast<DbgValueInst>(&I))
        if (Value *v = dbgValue->getValue())
            if (v->getType()->isPointerTy())
                preProcessDebugValueInstruction(dbgValue);

}

void FunctionWithGPG::preprocessPointerReturnInstruction(ReturnInst *rI)
{

    if (Value *rv = rI->getReturnValue())
    {
        vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(rv->getName());
        // outs()<<sourceOpr->getName()<<"\n";
        FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
        {
            Indirection *t8il = listOfNodes[i]->getIndirectList();
            if (isa<GlobalNode>(listOfNodes[i]))
            {
                GlobalNode *gN = (GlobalNode *)listOfNodes[i];
                GlobalVariable *gv = gN->getGlobalVariable();
                GPUNode *t9n = new GlobalNode(gv, t8il);
                returnNodes.insert(t9n);
            }
            else if (isa<TmpNode>(listOfNodes[i]))
            {
                GPUNode *tempNode = new TmpNode(listOfNodes[i]->getNameOfVariable(), fun->getName(), t8il, listOfNodes[i]->getTypeofVariable());
                returnNodes.insert(tempNode);
            }
        }
    }
}

/* need to tested on more cases */
void FunctionWithGPG::preProcessPHIInstruction(Instruction &I)
{

    if (PHINode *pN = dyn_cast<PHINode>(&I))
        for (unsigned i = 0; i < pN->getNumIncomingValues(); i++)
            if (Value *v = pN->getIncomingValue(i))
            {
                vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(v->getName());
                FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
                {
                    int iLevel = listOfNodes[i]->getIndirectList()->getIndirectionLevel();
                    if (iLevel > 0 && isa<GlobalNode>(listOfNodes[i]))
                    {
                        addVariableToTempMap(pN->getName(), listOfNodes[i]);
                    }
                }
            }
}

void FunctionWithGPG::preProcessDebugValueInstruction(DbgValueInst *dbgValue)
{

    if (Value *v = dbgValue->getValue())
    {
        StringRef name = dbgValue->getVariable()->getName();
        StringRef fileName = dbgValue->getVariable()->getFile()->getName();
        if (PHINode *node = dyn_cast<PHINode>(v))
        {
            // outs()<<node->getName()<<"  le\n";
            Indirection *til = new Indirection(1, true, SINGLE);
            GPUNode *tn = new TmpNode(name, fileName, til, v->getType());
            addVariableToTempMap(node->getName(), tn);
        }
        if (Argument *argument = dyn_cast<Argument>(v))
        {
            // outs()<<name<<"  \t"<<fileName<< "  ee\n";
            //outs()<<argument->getName()<<"  \n";
            Indirection *til = new Indirection(1, true, SINGLE);
            GPUNode *tn = new TmpNode(name, fileName, til, v->getType());
            //outs() <<  << '\n';
            addVariableToTempMap(argument->getName(), tn);
            formalArguments.push_back(name);
        }
    }
}

void FunctionWithGPG::preProcessDebugDeclareInstruction(DbgDeclareInst *dbgDeclare)
{
    if (Value *v = dbgDeclare->getAddress())
    {
        tempToSourceSet[v] = dbgDeclare->getVariable()->getName();
        StringRef name = dbgDeclare->getVariable()->getName();
        StringRef file = dbgDeclare->getVariable()->getFile()->getName();
        if (v->hasName())
        {
            Indirection *til = new Indirection(0, true, SINGLE);
            GPUNode *tn = new TmpNode(name, file, til, v->getType());
            addVariableToTempMap(v->getName(), tn);
        }
    }
}

/* for processing instruction like
  %tmp4 = getelementptr inbounds %struct.node, %struct.node* %tmp3, i32 0, i32 2
 */
void FunctionWithGPG::preProcessGEPInstruction(Instruction &I)
{

    int numIndices;
    GetElementPtrInst *gEPI = dyn_cast<GetElementPtrInst>(&I);
    Value *baseOpr = gEPI->getPointerOperand();
    numIndices = gEPI->getNumIndices();
    vector<int> p;
    if (gEPI->hasAllConstantIndices())
    {
        // outs()<<"xyz\n";
        string tempName = I.getName();
        vector<GPUNode *> listOfNodes =
            getListOfNodesMappedToTemp(baseOpr->getName());
        FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
        {

            Indirection *t3il = listOfNodes[i]->getIndirectList();
            IndirectionList *t4il;
            if (isa<IndirectionList>(t3il))
            {
                IndirectionList *ct3il = (IndirectionList *)t3il;
                t4il = new IndirectionList(1, true, ct3il->getNumberOfFields(),
                                           ct3il->getFieldList());
            }
            int j = 0;
            for (User::op_iterator I = gEPI->idx_begin() + 1, E = gEPI->idx_end();
                 I != E; ++I)
            {
                if (Constant *c = dyn_cast<Constant>(I))
                    p.push_back(c->getUniqueInteger().getLimitedValue() + 1);
            }

            if (isa<IndirectionList>(t3il))
                t4il->addFields(numIndices - 1, p);
            else
                t4il = new IndirectionList(1, true, numIndices - 1, p);

            if (isa<GlobalNode>(listOfNodes[i]))
            {
                GlobalNode *gN = (GlobalNode *)listOfNodes[i];
                GlobalVariable *gv = gN->getGlobalVariable();
                GPUNode *t9n = new GlobalNode(gv, t4il);
                // t4il->print();
                addVariableToTempMap(tempName, t9n);
            }
            else if (isa<TmpNode>(listOfNodes[i]))
            {
                GPUNode *tempNode = new TmpNode(listOfNodes[i]->getNameOfVariable(), fun->getName(), t4il, listOfNodes[i]->getTypeofVariable());
                addVariableToTempMap(tempName, tempNode);
            }
        }
    }
}

void FunctionWithGPG::preProcessLoadInstruction(Instruction &I)
{

    Value *sourceOpr = I.getOperand(0);
    string tempName = I.getName();
    /* To process the Instructions like below
     %tmp1 = load i32**, i32*** @p, align 8
     where p is global pointer */
    if (isa<GlobalVariable>(sourceOpr))
    {
        Indirection *til = new Indirection(1, true, SINGLE);
        GPUNode *tn = new GlobalNode(cast<GlobalVariable>(sourceOpr), til);
        addVariableToTempMap(tempName, tn);
        // outs()<< tn->get_name_of_variable() <<"  test:\n" ;
    }
    /* To process the Instructions like below
     %tmp9 = load i32**, i32*** %tmp8, align 8
     where temp8 may be refering global variable */

    else
    {

        if (tempToVariableSet.count(sourceOpr->getName()) == 1)
        {
            vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(sourceOpr->getName());
            // outs()<<sourceOpr->getName()<<"\n";
            FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
            {
                Indirection *t8il = listOfNodes[i]->getIndirectList();
                Indirection *t9il;
                if (isa<IndirectionList>(t8il))
                    t9il = t8il;
                else
                    t9il = new Indirection(t8il->getIndirectionLevel() + 1, true, SINGLE);
                if (isa<GlobalNode>(listOfNodes[i]))
                {
                    GlobalNode *gN = (GlobalNode *)listOfNodes[i];
                    GlobalVariable *gv = gN->getGlobalVariable();
                    GPUNode *t9n = new GlobalNode(gv, t9il);
                    addVariableToTempMap(tempName, t9n);
                }
                else if (isa<TmpNode>(listOfNodes[i]))
                {
                    GPUNode *tempNode = new TmpNode(listOfNodes[i]->getNameOfVariable(), fun->getName(), t9il, listOfNodes[i]->getTypeofVariable());
                    addVariableToTempMap(tempName, tempNode);
                }
            }
        }
        else if (GEPOperator *gOp = dyn_cast<GEPOperator>(sourceOpr))
        {
            //outs()<<I <<"...........................ee\n";
            Value *pOpr = gOp->getPointerOperand();
            int numIndices = gOp->getNumIndices();
            vector<int> p;
            if (gOp->hasAllConstantIndices())
            {

                int j = 0;
                for (User::op_iterator I = gOp->idx_begin() + 1, E = gOp->idx_end(); I != E; ++I)
                {

                    if (Constant *c = dyn_cast<Constant>(I))
                        p.push_back(c->getUniqueInteger().getLimitedValue() + 1);
                }
                IndirectionList *t4il = new IndirectionList(0, true, numIndices - 1, p);
                GPUNode *tempNode = new TmpNode(pOpr->getName(), fun->getName(), t4il, gOp->getResultElementType());
                addVariableToTempMap(tempName, tempNode);
            }
        }
    }


    /*
     * Pointer Load instructions def-use
     */
    for(User *user : I.users()){
        if (Instruction *Inst = dyn_cast<Instruction>(user)) {
            outs() << *Inst << "\n";
        }
    }

}
/// @brief print map of temp to global variables.
/// Used in debugging the preprocessing of Load Instructions

void FunctionWithGPG::printTempToVariableSet()
{
    map<string, vector<GPUNode *>>::iterator itMap;
    FOR_EACH_ELEMENT_MAP(tempToVariableSet, itMap)
    {
        outs() << itMap->first << "--->";
        // if(it_map->second.empty()) continue;
        vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(itMap->first);
        // outs() << listofnodes.size() <<" test:\n";
        FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
        {
            outs() << "( " << listOfNodes[i]->getNameOfVariable() << " , ";
            listOfNodes[i]->getIndirectList()->print();
            outs() << ")";
        }
        outs() << "\n";
    }
}

///  @brief process non-pointer loads for creating use nodes
///  The following statements are covered *x = 30, **p=40, *x=*y, **p=**q, a=*x,
///  b=**y

GPB *FunctionWithGPG::processNonPointerLoadInstruction(Instruction &I)
{

    set<GPU *, GPUComp> gpuSet;
    Value *sourceOpr = I.getOperand(0);
    long lineNo;
    StringRef fileName;
    Util util;
    //outs()<<I<<"  "<<" e\n";
    if (!isa<GlobalVariable>(sourceOpr))
    {
        // string nodeName = "use@"+ to_string(insNo);
        // StringRef* nName = new StringRef("use@"+ to_string(insNo));
        Indirection *u = new Indirection(1, true, SINGLE);
        /*get line number and file name */
        if (I.hasMetadata())
        {
            MDNode *node = I.getMetadata("dbg");
            if (DILocation *loc = dyn_cast<DILocation>(node))
            {
                lineNo = loc->getLine();
                fileName = loc->getFilename();
            }
        }
        else
            util.debugInfoErrorMsg(I);
        GPUNode *leftNode = new UseNode("use@", lineNo, fileName, u);
        if (tempToVariableSet.count(sourceOpr->getName()) == 1)
        {

            vector<GPUNode *> listOfNodes =
                getListOfNodesMappedToTemp(sourceOpr->getName());
            FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
            {
                if (isa<GlobalNode>(listOfNodes[i]))
                {
                    Indirection *sList = listOfNodes[i]->getIndirectList();
                    Indirection *sOprList = new Indirection(sList->getIndirectionLevel() + 1, true, SINGLE);
                    GlobalVariable *gv = ((GlobalNode *)listOfNodes[i])->getGlobalVariable();
                    GPUNode *rightNode = new GlobalNode(gv, sOprList);
                    GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
                    // deprecated
                    // gpu->setDataType(gv->getType()->getContainedType(0));
                    gpuSet.insert(gpu);
                }
                //TODO what happens if its not a global variable ?
            }
        }
        //else outs()<<I<<"  "<<" e\n";
    }
    GPB *gpBlock = new GPB(gpuSet);
    // gpBlock->print();
    return gpBlock;
}

///  @brief process non-pointer stores for creating use nodes
///  The following statements are covered *x = 30, **p=40, *x=*y, **p=**q, a=*x,
///  b=**y

GPB *FunctionWithGPG::processNonPointerStoreInstruction(Instruction &I)
{

    set<GPU *, GPUComp> gpuSet;
    Value *sourceOpr = I.getOperand(0);
    Value *rOpr = I.getOperand(1);
    outs()<<rOpr->getName()<<" " << I << "    eee\n";
    long lineNo;
    StringRef fileName;
    Util util;
    // outs() << I << "\n";
    //outs()<<rOpr->getName()<<"  e\n";
    /// To process the instruction like
    /// store i32 30, i32* %tmp2, align 4, !dbg !36
    /// where temp2 is refering to global variable

    if (!isa<GlobalVariable>(rOpr))
    {
        if (tempToVariableSet.count(rOpr->getName()) == 1)
        {

            outs()<<rOpr->getName()<<" " << I << "    eee\n";
            vector<GPUNode *> listOfNodes =
                getListOfNodesMappedToTemp(rOpr->getName());
            FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
            {
                // string nodeName = "use@"+ to_string(insNo);
                // StringRef* nName = new StringRef("use@"+ to_string(insNo));
                Indirection *u = new Indirection(1, true, SINGLE);
                // get line number and file name
                if (I.hasMetadata())
                {
                    MDNode *node = I.getMetadata("dbg");
                    if (DILocation *loc = dyn_cast<DILocation>(node))
                    {
                        lineNo = loc->getLine();
                        fileName = loc->getFilename();
                    }
                }
                else
                    util.debugInfoErrorMsg(I);
                //outs()<<lineNo<<" "<<fileName<<"  ee\n";

                GPUNode *leftNode = new UseNode("use@", lineNo, fileName, u);

                if (isa<GlobalNode>(listOfNodes[i]))
                {
                    Indirection *rList = listOfNodes[i]->getIndirectList();
                    int iL = rList->getIndirectionLevel() + 1;
                    Indirection *rOprList = new Indirection(iL, true, SINGLE);
                    GlobalVariable *gv = ((GlobalNode *)listOfNodes[i])->getGlobalVariable();
                    GPUNode *rightNode = new GlobalNode(gv, rOprList);
                    GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
                    // deprecated
                    //gpu->setDataType(rOpr->getType()->getContainedType(0));
                    gpuSet.insert(gpu);
                }
                else if (isa<TmpNode>(listOfNodes[i]))
                {
                    GPU *gpu = new GPU(leftNode, listOfNodes[i], lineNo, fileName);
                    //gpuSet.insert(gpu);
                }
            }

            if (!isa<ConstantData>(sourceOpr))
            {
            }
        }
    }

    /// To process the instruction like
    /// store i32 %tmp10, i32* @d, align 4
    /// where temp10 is refering to global variable
    else
    {
        if (tempToVariableSet.count(sourceOpr->getName()) == 1)
        {

            vector<GPUNode *> listOfNodes =
                getListOfNodesMappedToTemp(sourceOpr->getName());
            FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
            {
                // string nodeName = "use@"+ to_string(insNo);
                // StringRef* nName = new StringRef("use@"+ to_string(insNo));
                Indirection *u = new Indirection(1, true, SINGLE);
                // get line number and file name
                if (I.hasMetadata())
                {
                    MDNode *node = I.getMetadata("dbg");
                    if (DILocation *loc = dyn_cast<DILocation>(node))
                    {
                        lineNo = loc->getLine();
                        fileName = loc->getFilename();
                    }
                }
                else
                    util.debugInfoErrorMsg(I);
                GPUNode *leftNode = new UseNode("use@", lineNo, fileName, u);
                Indirection *rList = listOfNodes[i]->getIndirectList();
                Indirection *rOprList =
                    new Indirection(rList->getIndirectionLevel() + 1, true, SINGLE);
                if (isa<GlobalNode>(listOfNodes[i]))
                {
                    GlobalVariable *gv =
                        ((GlobalNode *)listOfNodes[i])->getGlobalVariable();
                    GPUNode *rightNode = new GlobalNode(gv, rOprList);
                    GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
                    // deprecated
                    // gpu->setDataType(gv->getType()->getContainedType(0));
                    gpuSet.insert(gpu);
                }
                else if (isa<TmpNode>(listOfNodes[i]))
                {
                    outs() << I << "      eee\n";
                }
            }
        }
    }
    //outs()<<"here block created \n";
    GPB *gpBlock = new GPB(gpuSet);
    //outs()<<"here block created111 \n";
    // gpBlock->print();
    return gpBlock;
}

GPB *FunctionWithGPG::processPointsToTestFunctions(Instruction &I)
{

    set<GPU *, GPUComp> gpuSet;
    CallSite cs = CallSite(cast<CallInst>(&I));
    string tempName = I.getName();
    StringRef fileName;
    long lineNo;
    Util util;
    /*get line number and file name */
    if (I.hasMetadata())
    {
        MDNode *node = I.getMetadata("dbg");
        if (DILocation *loc = dyn_cast<DILocation>(node))
        {
            lineNo = loc->getLine();
            fileName = loc->getFilename();
        }
    }
    else
        util.debugInfoErrorMsg(I);

    if (!cs.isIndirectCall())
    {

        StringRef funPointsTo("POINTSTO");
        StringRef funNotPointsTo("NOTPOINTSTO");
        Function *function = cs.getCalledFunction();
        StringRef funName = function->getName();

        if (funName.equals(funPointsTo) || funName.equals(funNotPointsTo))
        {

            if (cs.getNumArgOperands() == 2)
            {
                Value *arg = cs.getArgument(0);
                Value *v = cs.getArgument(1);
                StringRef pointsSetStr;
                // for processing points-to list supplied by the user
                if (Constant *cv = dyn_cast<Constant>(v))
                    if (ConstantExpr *cexpr = dyn_cast<ConstantExpr>(cv))
                    {
                        Instruction *inst = cexpr->getAsInstruction();
                        if (GetElementPtrInst *gEPI = dyn_cast<GetElementPtrInst>(inst))
                        {
                            Value *baseOpr = gEPI->getPointerOperand();
                            if (GlobalVariable *gv = dyn_cast<GlobalVariable>(baseOpr))
                            {
                                if (ConstantDataArray *ar = dyn_cast<ConstantDataArray>(gv->getInitializer()))
                                {
                                    pointsSetStr = ar->getAsCString();
                                }
                            }
                        }
                    }

                if (arg->hasName())
                {
                    //outs()<<arg->getName()<<"\n";
                    if (tempToVariableSet.count(arg->getName()) == 1)
                    {
                        vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(arg->getName());
                        FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
                        {
                            Indirection *rList = listOfNodes[i]->getIndirectList();
                            if (rList->getIndirectionLevel() == 0)
                            {
                                //pointer is replaced with pointee during SSA conversion
                                if (pointsSetStr.equals(listOfNodes[i]->getNameOfVariable()))
                                {
                                    if (funName.equals(funPointsTo))
                                        addSSAPointsToTestCase(fileName, lineNo, true, true);
                                    else
                                        addSSAPointsToTestCase(fileName, lineNo, false, true);
                                }
                                else
                                {
                                    if (funName.equals(funPointsTo))
                                        addSSAPointsToTestCase(fileName, lineNo, true, false);
                                    else
                                        addSSAPointsToTestCase(fileName, lineNo, false, false);
                                }
                                continue;
                            }
                            Indirection *u = new Indirection(1, true, SINGLE);
                            GPUNode *leftNode = new UseNode("use@", lineNo, fileName, u);
                            Indirection *rOprList = new Indirection(1, true, SINGLE);
                            if (isa<GlobalNode>(listOfNodes[i]))
                            {
                                GlobalVariable *gv = ((GlobalNode *)listOfNodes[i])->getGlobalVariable();
                                GPUNode *rightNode = new GlobalNode(gv, rOprList);
                                GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
                                gpuSet.insert(gpu);
                                if (funName.equals(funPointsTo))
                                    addPointsToTestCase(fileName, lineNo, rightNode->getNameOfVariable(), pointsSetStr, true);
                                else
                                    addPointsToTestCase(fileName, lineNo, rightNode->getNameOfVariable(), pointsSetStr, false);
                            }
                            else if (isa<TmpNode>(listOfNodes[i]))
                            {
                                GPU *gpu = new GPU(leftNode, listOfNodes[i], lineNo, fileName);
                                gpuSet.insert(gpu);
                                if (funName.equals(funPointsTo))
                                    addPointsToTestCase(fileName, lineNo, listOfNodes[i]->getNameOfVariable(), pointsSetStr, true);
                                else
                                    addPointsToTestCase(fileName, lineNo, listOfNodes[i]->getNameOfVariable(), pointsSetStr, false);
                            }
                        }
                    }
                }
            }

            else
            {

                outs() << "Wrong call to POINTSTO test functions \n";
                outs() << "The number of arguments must be 2 \n";
                outs() << "Usage: POINTSTO(pointer,\"commasepeartedpointstolist\") \n";
                exit(-1);
            }
        }
        else
            return NULL;
        GPB *gpBlock = new GPB(gpuSet);
        //gpBlock->print();
        return gpBlock;
    }
    else
        return NULL;
}

GPB *FunctionWithGPG::processPointerStoreInstruction(Instruction &I, map<StringRef, FunctionWithGPG *> &functionToGPG)
{

    set<GPU *, GPUComp> gpuSet;
    Value *sourceOpr = I.getOperand(0);
    Value *rOpr = I.getOperand(1);
    GPUNode *leftNode = NULL;
    StringRef fileName;
    long lineNo;
    Util util;
    /*get line number and file name */
    if (I.hasMetadata())
    {
        MDNode *node = I.getMetadata("dbg");
        if (DILocation *loc = dyn_cast<DILocation>(node))
        {
            lineNo = loc->getLine();
            fileName = loc->getFilename();
        }
    }
    else
        util.debugInfoErrorMsg(I);

    outs() << sourceOpr->getName() << " " << rOpr->getName() << "\n";
    // To process instruction like
    // store i32* @a, i32** getelementptr inbounds (%struct.s1, %struct.s1* @y, i32 0, i32 0), align 8, !dbg !42
    if (GEPOperator *gOp = dyn_cast<GEPOperator>(rOpr))
    {
        //outs()<<I <<"...........................ee\n";
        Value *pOpr = gOp->getPointerOperand();
        int numIndices = gOp->getNumIndices();
        vector<int> p;
        if (gOp->hasAllConstantIndices())
        {
            int j = 0;
            for (User::op_iterator I = gOp->idx_begin() + 1, E = gOp->idx_end(); I != E; ++I)
            {

                if (Constant *c = dyn_cast<Constant>(I))
                    p.push_back(c->getUniqueInteger().getLimitedValue() + 1);
            }

            IndirectionList *t4il = new IndirectionList(0, true, numIndices - 1, p);
            leftNode = new TmpNode(pOpr->getName(), fun->getName(), t4il, gOp->getResultElementType());
        }
    }
    /// To process the instruction like
    /// store i32 (...)* bitcast (i32 ()* @f to i32 (...)*), i32 (...)** @f_ptr, align 8,
    /// where f_ptr is a global function pointer.
    // else if (isa<BitCastOperator>(sourceOpr) && !sourceOpr->getType()->getPointerElementType()->isAggregateType())
    // {
    //     BitCastOperator *bCastOp = dyn_cast<BitCastOperator>(sourceOpr);
    //     //   llvm::outs() << bCastOp->getOperand(0)->getName() << "\n";
    //     Indirection *sList = new Indirection(0, true, SINGLE);
    //     Indirection *rOprList = new Indirection(1, true, SINGLE);

    //     GPUNode *rightNode = new FPNode(bCastOp->getOperand(0), sList);
    //     GPUNode *leftNode = new GlobalNode(cast<GlobalVariable>(rOpr), rOprList);

    //     GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
    //     gpuSet.insert(gpu);
    //     ConstructGPGForFPCall(bCastOp->getOperand(0)->getName(), functionToGPG);
    // }
    /// To process the instruction like
    /// store i32** @x, i32*** @p, align 8
    /// where p and x are global varaibles
    /// It is refereing p=&x Instruction
    else if (isa<GlobalVariable>(sourceOpr) && isa<GlobalVariable>(rOpr))
    {

        Indirection *sList = new Indirection(0, true, SINGLE);
        Indirection *rOprList = new Indirection(1, true, SINGLE);

        GPUNode *rightNode = new GlobalNode(cast<GlobalVariable>(sourceOpr), sList);
        GPUNode *leftNode = new GlobalNode(cast<GlobalVariable>(rOpr), rOprList);

        GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
        gpuSet.insert(gpu);
    }

    /// To process the instruction like
    /// store i32* @b, i32** %tmp, align 8
    /// where b is global varaible
    /// temp might be refereing global pointer

    else if (isa<GlobalVariable>(sourceOpr))
    {

        if (tempToVariableSet.count(rOpr->getName()) == 1)
        {

            vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(rOpr->getName());

            FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
            {

                Indirection *sList = new Indirection(0, true, SINGLE);

                GPUNode *rightNode =
                    new GlobalNode(cast<GlobalVariable>(sourceOpr), sList);

                Indirection *rList = listOfNodes[i]->getIndirectList();

                Indirection *rOprList;

                if (isa<IndirectionList>(rList))
                {

                    IndirectionList *ctList = (IndirectionList *)rList;
                    rOprList = new IndirectionList(1, true, ctList->getNumberOfFields(),
                                                   ctList->getFieldList());
                }
                else
                    rOprList = new Indirection(rList->getIndirectionLevel() + 1, true, SINGLE);

                if (isa<GlobalNode>(listOfNodes[i]))
                {

                    GlobalVariable *gv =
                        ((GlobalNode *)listOfNodes[i])->getGlobalVariable();

                    GPUNode *leftNode = new GlobalNode(gv, rOprList);

                    GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);

                    gpuSet.insert(gpu);
                }
                else if (isa<TmpNode>(listOfNodes[i]))
                {

                    GPUNode *tempNode = new TmpNode(listOfNodes[i]->getNameOfVariable(), fun->getName(), rOprList, listOfNodes[i]->getTypeofVariable());
                    GPU *gpu = new GPU(tempNode, rightNode, lineNo, fileName);
                    gpuSet.insert(gpu);
                }
            }
        }
        // getelement ptr
        else if (leftNode != NULL)
        {
            vector<int> q(1);
            IndirectionList *t3il = new IndirectionList(0, true, 0, q);
            GPUNode *rightNode = new GlobalNode(cast<GlobalVariable>(sourceOpr), t3il);
            GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
            gpuSet.insert(gpu);
        }
    }

    /// To process the instruction like
    ///   store i32* %tmp, i32** @y, align 8
    /// where y is global varaible
    /// temp might be refereing global pointer

    else if (isa<GlobalVariable>(rOpr))
    {

        if (tempToVariableSet.count(sourceOpr->getName()) == 1)
        {

            vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(sourceOpr->getName());

            FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
            {

                Indirection *rList = listOfNodes[i]->getIndirectList();

                Indirection *rOprList;

                if (isa<IndirectionList>(rList))
                {

                    vector<int> p(1);
                    rOprList = new IndirectionList(1, true, 0, p);
                }
                else
                    rOprList = new Indirection(1, true, SINGLE);

                GPUNode *leftNode = new GlobalNode(cast<GlobalVariable>(rOpr), rOprList);

                GPU *gpu = new GPU(leftNode, listOfNodes[i], lineNo, fileName);
                gpuSet.insert(gpu);
            }
        }

        //may not be required
        /*else if(GEPOperator *gOp = dyn_cast<GEPOperator>(sourceOpr)){
        outs()<<I <<"...........................ee\n";
        Value *pOpr = gOp->getPointerOperand();
        outs()<<*pOpr;
        int numIndices = gOp->getNumIndices();

        int *p = new int[numIndices];

        if (gOp->hasAllConstantIndices()) {

          int j = 0;
          for (User::op_iterator I = gOp->idx_begin() + 1, E = gOp->idx_end(); I != E; ++I) {

            if (Constant *c = dyn_cast<Constant>(I))
              p[j++] = c->getUniqueInteger().getLimitedValue() + 1;
          }

          IndirectionList *t4il = new IndirectionList(0, true, numIndices - 1, p);
          int *q = new int[1]; //dummy
          IndirectionList *t3il = new IndirectionList(0,true,0,q);
          GPUNode  *left = new GlobalNode(cast<GlobalVariable>(sourceOpr),t3il);
          GPUNode *right = new TmpNode(pOpr->getName(),fun->getName(),t4il,sourceOpr->getType());
          GPU *gpu = new GPU(left,right,lineNo,fileName);
          gpuSet.insert(gpu);
        }
    }*/
    }
    /// To process the instruction like
    ///   store i32* %tmp1, i32** tmp2, align 8
    /// where y is global varaible
    /// temp might be refereing global pointer

    else
    {
        //outs()<<"s: "<<sourceOpr->getName()<<" r:  "<<rOpr->getName()<<"\n";

        /*
         * syntax - store value, address
         * eg. int x = 5, y = 6, int *p = &x, *p = y => store y, *p
         */
        GPUNode *leftNode = new TmpNode(rOpr->getName(), fileName,
                                        new Indirection(2, true, SINGLE), rOpr->getType());

        GPUNode *rightNode = new TmpNode(sourceOpr->getName(), fileName,
                                        new Indirection(1, true, SINGLE), sourceOpr->getType());

        GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
        gpuSet.insert(gpu);

        if (tempToVariableSet.count(rOpr->getName()) == 1)
        {

            vector<GPUNode *> rListOfNodes = getListOfNodesMappedToTemp(rOpr->getName());

            vector<GPUNode *> sListOfNodes = getListOfNodesMappedToTemp(sourceOpr->getName());

            FOR_EACH_ELEMENT_OF_VECTOR(rListOfNodes)
            {
                //outs() << rListOfNodes[i]->getNameOfVariable() << "\n";
                Indirection *rList = rListOfNodes[i]->getIndirectList();

                // rList->print();
                Indirection *rOprList;

                if (isa<IndirectionList>(rList))
                {

                    IndirectionList *ctList = (IndirectionList *)rList;
                    rOprList = new IndirectionList(1, true, ctList->getNumberOfFields(),
                                                   ctList->getFieldList());
                }
                else
                    rOprList = new Indirection(rList->getIndirectionLevel() + 1, true, SINGLE);

                // rOprList->print();

                if (isa<GlobalNode>(rListOfNodes[i]))
                {

                    GlobalVariable *gv =
                        ((GlobalNode *)rListOfNodes[i])->getGlobalVariable();

                    GPUNode *t2n = new GlobalNode(gv, rOprList);

                    for (int j = 0; j < sListOfNodes.size(); j++)
                    {

                        GPU *gpu = new GPU(t2n, sListOfNodes[j], lineNo, fileName);
                        //gpuSet.insert(gpu);
                    }
                }

                else if (isa<TmpNode>(rListOfNodes[i]))
                {

                    for (int j = 0; j < sListOfNodes.size(); j++)
                    {

                        GPUNode *tempNode = new TmpNode(rListOfNodes[i]->getNameOfVariable(), fun->getName(), rOprList, rListOfNodes[i]->getTypeofVariable());
                        GPU *gpu = new GPU(tempNode, sListOfNodes[j], lineNo, fileName);
                        //gpuSet.insert(gpu);
                    }
                }
            } // for each rlist nodes
        }
        // getelement ptr
        else if (leftNode != NULL)
        {

            vector<GPUNode *> sListOfNodes = getListOfNodesMappedToTemp(sourceOpr->getName());

            for (int j = 0; j < sListOfNodes.size(); j++)
            {
                vector<int> q(1);
                int numberOfStars = sListOfNodes[j]->getIndirectList()->getIndirectionLevel();
                IndirectionList *t3il = new IndirectionList(numberOfStars, true, 0, q);

                if (isa<GlobalNode>(sListOfNodes[j]))
                {
                    GPUNode *rightNode = new GlobalNode(((GlobalNode *)sListOfNodes[j])->getGlobalVariable(), t3il);
                    GPU *gpu = new GPU(leftNode, sListOfNodes[j], lineNo, fileName);
                    gpuSet.insert(gpu);
                }
                else if (isa<TmpNode>(sListOfNodes[j]))
                {
                    GPUNode *rightNode = new TmpNode(sListOfNodes[j]->getNameOfVariable(), fun->getName(), t3il, sListOfNodes[j]->getTypeofVariable());
                    GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
                    gpuSet.insert(gpu);
                }
            }
        }
    }
    GPB *gpBlock = new GPB(gpuSet);
    //gpBlock->print();
    return gpBlock;
}

void FunctionWithGPG::setModule(Module *module)
{
    m = module;
}

void FunctionWithGPG::ConstructGPGForFPCall(StringRef fName, map<StringRef, FunctionWithGPG *> &functionToGPG)
{
    Function *FunctionsGPGtobeConstructed;
    CallGraph *callGraph = new CallGraph(*m);

    for (Function &F : *m)
    {
        if (F.getName() == fName)
        {
            FunctionsGPGtobeConstructed = &F;
        }
    }
    if (functionToGPG.find(FunctionsGPGtobeConstructed->getName()) != functionToGPG.end())
    {
        return;
    }
    CallGraphNode *rootNode = (*callGraph)[FunctionsGPGtobeConstructed];
    for (scc_iterator<CallGraphNode *> SCCI = scc_begin(rootNode); SCCI != scc_end(rootNode); ++SCCI)
    {
        const std::vector<CallGraphNode *> &nextSCC = *SCCI;

        FunctionWithGPG *fgpg = new FunctionWithGPG(FunctionsGPGtobeConstructed);
        outs() << "\n Summary of function (Call through FP): " << FunctionsGPGtobeConstructed->getName() << "\n";
        fgpg->setModule(m);
        Util *ut = new Util();

        if(SCCI.hasLoop())
        {
            outs() << "Recursion\n";            
            set<StringRef> sccFunctions;

            std::vector<CallGraphNode *>::const_iterator I;

            for (I = nextSCC.begin(); I != nextSCC.end(); ++I)
            {
                if ((*I)->getFunction())
                {
                    sccFunctions.insert((*I)->getFunction()->getName());                    
                }
            }

            ut->setSCCFunctions(sccFunctions);
            map<StringRef, char *> gToB;
            map<Function*, bool > InsideWorkList;
            I = nextSCC.begin();
            queue<Function*> WorkList;

            if((*I)->getFunction())    
            {
                WorkList.push((*I)->getFunction());  
                InsideWorkList[(*I)->getFunction()] = 1;
            }

            map<StringRef, FunctionWithGPG*> tmpMap;
            for(auto it : nextSCC)
            {
                if(it->getFunction())
                {
                    FunctionWithGPG *fgpg = new FunctionWithGPG((it)->getFunction());
                    fgpg->setModule((it)->getFunction()->getParent());
                    fgpg->findCallers();
                    fgpg->preProcessFunction();
                    fgpg->setupwardExposedVersionOfGlobalVar((it)->getFunction()->getParent()->getGlobalList(), gToB);
                    fgpg->constructGPG(functionToGPG, ut);
                    fgpg->removeEmptyNodesInGPG();
                    fgpg->setInitialSummary();
                    tmpMap[(it)->getFunction()->getName()] = fgpg;
                }
            }

            int itr = 1;
            while(!WorkList.empty())
            {

                Function* currFun = WorkList.front();
                WorkList.pop();
                InsideWorkList[currFun] = 0;

                if(functionToGPG.find(currFun->getName()) == functionToGPG.end())
                {
                    outs() << "\n Summary of function : ";
                    outs() << currFun->getName() << "\n";
                    FunctionWithGPG *fgpg = tmpMap[currFun->getName()]; 
                    fgpg->constructGPG(functionToGPG, ut);                       
                    fgpg->removeEmptyNodesInGPG();
                    fgpg->setBoundrayDef(currFun->getParent()->getGlobalList(), gToB);
                    fgpg->handleRecursion(ceil(1.0*itr/nextSCC.size()), 1);

                    set<Function*> callers = fgpg->getCallers();
                    for(auto it : callers)
                    {
                        if(it && ut->isItPartOfSCC(it->getName()) && !InsideWorkList[it])
                        {
                            WorkList.push(it);
                            InsideWorkList[it] = 1;
                        }
                    }
                    functionToGPG[currFun->getName()] = fgpg;
                }
                else
                {
                    FunctionWithGPG* fgpg = functionToGPG[currFun->getName()];
                    
                    set<GPU*, GPUComp> prevRGOutWOBlocking = fgpg->getRGOutOfEnd(1);
                    set<GPU*, GPUComp> prevRGOutWBlocking = fgpg->getRGOutOfEnd(0);

                    fgpg->inliningCallsInSCC(functionToGPG);
                    fgpg->handleRecursion(ceil(1.0*itr/nextSCC.size()), 1);

                    set<GPU*, GPUComp> currRGOutWOBlocking = fgpg->getRGOutOfEnd(1);
                    set<GPU*, GPUComp> currRGOutWBlocking = fgpg->getRGOutOfEnd(0);
                    if(ut->isEqualOrNot(prevRGOutWOBlocking, currRGOutWOBlocking) == false || ut->isEqualOrNot(prevRGOutWBlocking, currRGOutWBlocking) == false)
                    {
                        set<Function*> callers = fgpg->getCallers();
                        for(auto it : callers)
                        {
                            if(it && ut->isItPartOfSCC(it->getName()) && !InsideWorkList[it])
                            {
                                WorkList.push(it);
                                InsideWorkList[it] = 1;
                            }
                        }                
                    }
                }
                itr++;        
            }
            ut->reSetSCCFunctions();
        }
        else
        {
            map<StringRef, char *> gToB = ut->createXdashForAllGlobalVariables(m);
            fgpg->preProcessFunction();
            // std::cout << "After preprocess\n";

            fgpg->setupwardExposedVersionOfGlobalVar(m->getGlobalList(), gToB);
// std::cout << "After setupwardExposedVersionOfGlobalVar\n";
#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 1
            fgpg->printTempToVariableSet();
#endif
#if VERBOSE_LEVEL == 10
            fgpg->printTempToVariableSet();
#endif
#endif

            fgpg->constructGPG(functionToGPG, ut);
            // std::cout << "AfterconstructGPG\n";

            fgpg->ValidateInitialGPUTests();

            fgpg->setBoundrayDef(m->getGlobalList(), gToB);

            fgpg->removeEmptyNodesInGPG();
            // std::cout << "AfterremoveEmptyNodesInGPG_1\n";

            fgpg->reachingGPUAnalysisWithOutBlocking();
            // std::cout << "AfterreachingGPUAnalysisWithOutBlocking\n";

            fgpg->reachingGPUAnalysisWithBlocking();
            // std::cout << "AfterreachingGPUAnalysisWithBlocking\n";

            // if(dumpPointsTo) fgpg->dumpPointsToInfo();

            fgpg->deadGPUElimination();
            // std::cout << "AfterDeadGPUElimination\n";

            fgpg->removeEmptyNodesInGPG();
            // std::cout << "AfterremoveEmptyNodesInGPG_2\n";

            //fgpg->coalescingAnalysisInPaper();
            //outs()<<"Coalescing Analysis started .........eeee\n";
            // ------------------------------------------- My Implementation ---------------------------------//
            fgpg->UpdatedCoalescingAnalysis();
            // std::cout << "AfterUpdatedCoalescingAnalysis\n";
            // -----------------------------------------------------------------------------------------------//

            // fgpg->coalescingAnalysisInThesis();
            functionToGPG[fName] = fgpg;
        }
        outs() << "Constructed summary of function : " << FunctionsGPGtobeConstructed->getName() << "\n";
    }
}
void FunctionWithGPG::ReplaceFPUseNodeWithSummary(map<StringRef, FunctionWithGPG *> &functionToGPG)
{
    map<long, GPB *> gpbs = summary->getGPBMap();

    map<long, GPB *> newGPBMap;
    set<GPB *, GPBComp> newGPBset;
    vector<GPB *> GPBsToRemove;

    for (auto it = gpbs.begin(); it != gpbs.end(); it++)
    {
        set<GPU *, GPUComp> GPUsWithFPNode;
        set<GPU *, GPUComp> gpus = (*it).second->getGPUSet();

        for (auto gpu = gpus.begin(); gpu != gpus.end(); gpu++)
        {
            if (isa<UseNode>((*gpu)->getSourceOfGPU()) && isa<FPNode>((*gpu)->getTargetOfGPU()))
            {
                if ((*gpu)->getTargetOfGPU()->getIndirectList()->getIndirectionLevel() == 0)
                    GPUsWithFPNode.insert((*gpu));
            }
        }

        if (GPUsWithFPNode.size() == 0 || GPUsWithFPNode.size() != gpus.size())
        {
            newGPBMap.insert((*it));
            newGPBset.insert((*it).second);
        }
        if (GPUsWithFPNode.size() != 0)
        {
            GPB *entry = new GPB(); // dummy entry to connect callee's GPGs start node.
            newGPBset.insert(entry);
            newGPBMap[entry->getGPBNo()] = entry;
            GPB *exit = new GPB(); // dummy exit to connect callee's GPGs end node.
            newGPBset.insert(exit);            
            newGPBMap[exit->getGPBNo()] = exit;
            for (auto gpu : GPUsWithFPNode)
            {
                GPG *calleGPG = functionToGPG[gpu->getTargetOfGPU()->getNameOfVariable()]->getSummary();
                map<long, GPB *> GPBsMap = calleGPG->getGPBMap();
                set<GPB *, GPBComp> GPBSet = calleGPG->getGPBSet();

                map<long, long> oldToNew;
                map<long, GPB *> newGPBsMap;

                for (auto gpb = GPBSet.begin(); gpb != GPBSet.end(); gpb++)
                {
                    GPB *newGPB = new GPB();
                    newGPB->setGPUSet((*gpb)->getGPUSet());
                    newGPB->setisInlined(1);
                    newGPB->setMayDefSet((*gpb)->getMayDefSet());
                    oldToNew[(*gpb)->getGPBNo()] = newGPB->getGPBNo();
                    newGPBset.insert(newGPB);
                    newGPBsMap[newGPB->getGPBNo()] = newGPB;
                    newGPBMap[newGPB->getGPBNo()] = newGPB;
                }

                GPB *startNode = newGPBsMap[oldToNew[calleGPG->getEntryNode()->getGPBNo()]];
                startNode->addPredecessor(entry);
                entry->addSuccessor(startNode);
                summary->addEdge(entry->getGPBNo(), startNode->getGPBNo());

                GPB *endNode = newGPBsMap[oldToNew[calleGPG->getExitNode()->getGPBNo()]];
                endNode->addSuccessor(exit);
                exit->addPredecessor(endNode);
                summary->addEdge(endNode->getGPBNo(), exit->getGPBNo());

                for (auto gpb = GPBSet.begin(); gpb != GPBSet.end(); gpb++)
                {
                    // Iterate over all succSet
                    set<GPB *, GPBComp> succs = (*gpb)->getAllSuccessors();
                    for (auto succ = succs.begin(); succ != succs.end(); succ++)
                    {
                        newGPBsMap[oldToNew[(*gpb)->getGPBNo()]]->addSuccessor(newGPBsMap[oldToNew[(*succ)->getGPBNo()]]);
                        newGPBsMap[oldToNew[(*succ)->getGPBNo()]]->addPredecessor(newGPBsMap[oldToNew[(*gpb)->getGPBNo()]]);
                        summary->addEdge(oldToNew[(*gpb)->getGPBNo()], oldToNew[(*succ)->getGPBNo()]);
                    }
                    // Iterate over all preds
                    set<GPB *, GPBComp> preds = (*gpb)->getAllPredecessors();
                    for (auto pred = preds.begin(); pred != preds.end(); pred++)
                    {
                        newGPBsMap[oldToNew[(*gpb)->getGPBNo()]]->addPredecessor(newGPBsMap[oldToNew[(*pred)->getGPBNo()]]);
                        newGPBsMap[oldToNew[(*pred)->getGPBNo()]]->addSuccessor(newGPBsMap[oldToNew[(*gpb)->getGPBNo()]]);
                        summary->addEdge(oldToNew[(*pred)->getGPBNo()], oldToNew[(*gpb)->getGPBNo()]);
                    }
                }
            }
            if (GPUsWithFPNode.size() == gpus.size())
            {
                set<GPB *, GPBComp> preds = (*it).second->getAllPredecessors();
                set<GPB *, GPBComp> succs = (*it).second->getAllSuccessors();

                for (auto pred = preds.begin(); pred != preds.end(); pred++)
                {
                    entry->addPredecessor(*pred);
                    (*pred)->addSuccessor(entry);
                    summary->addEdge((*pred)->getGPBNo(), entry->getGPBNo());
                    (*pred)->removeSuccessor((*it).second);
                    summary->removeEdge((*pred)->getGPBNo(), (*it).second->getGPBNo());
                }
                (*it).second->removeAllPredecessors();
                for (auto succ = succs.begin(); succ != succs.end(); succ++)
                {
                    exit->addSuccessor(*succ);
                    (*succ)->addPredecessor(exit);
                    summary->addEdge(exit->getGPBNo(), (*succ)->getGPBNo());
                    (*succ)->removePredecessor((*it).second);
                    summary->removeEdge((*it).second->getGPBNo(), (*succ)->getGPBNo());
                }
                (*it).second->removeAllSuccessors();
                GPBsToRemove.push_back((*it).second);
            }
            else
            {

                set<GPB *, GPBComp> succs = (*it).second->getAllSuccessors();
                entry->addPredecessor((*it).second);
                summary->addEdge((*it).second->getGPBNo(), entry->getGPBNo());
                for (auto succ = succs.begin(); succ != succs.end(); succ++)
                {
                    exit->addSuccessor(*succ);
                    (*succ)->addPredecessor(exit);
                    summary->addEdge(exit->getGPBNo(), (*succ)->getGPBNo());
                    (*succ)->removePredecessor((*it).second);
                    summary->removeEdge((*it).second->getGPBNo(), (*succ)->getGPBNo());
                }
                (*it).second->removeAllSuccessors();
                (*it).second->addSuccessor(entry);
                set<GPU *, GPUComp> newGPUsOfCurrGPB;
                for (auto gpu = gpus.begin(); gpu != gpus.end(); gpu++)
                {
                    if (GPUsWithFPNode.find(*gpu) == GPUsWithFPNode.end())
                    {
                        newGPUsOfCurrGPB.insert(*gpu);
                    }
                }
                (*it).second->setGPUSet(newGPUsOfCurrGPB);
            }
            // summary->removeGPB((*it).second);
        }
    }
    for (auto it : GPBsToRemove)
    {
        summary->removeGPB(it);
        it->getGPBNo(), it;
    }
    summary->setGPBMap(newGPBMap);
    summary->setGPBSet(newGPBset);
    string funName = fun->getName();
    string dotFileName = funName + "AfterReplacingFPCallsgpg.dot";
#ifdef PRINT_TO_DOT
#if PRINT_TO_DOT == 1
    summary->printToDot(dotFileName);
#endif
#endif
}
GPB *FunctionWithGPG::processFPCallInst(Instruction &I)
{
    //%tmp3 = call i32 (...) %tmp2(), !dbg !37
    GPB *resultant = new GPB();
    set<GPU *, GPUComp> gpuSet;

    CallInst *CI = dyn_cast<CallInst>(&I);
    std::string FPCallName = CI->getCalledValue()->getName().str();
    vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(FPCallName);

    FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
    {
        long lineNo;
        StringRef fileName;
        if (I.hasMetadata())
        {
            MDNode *node = I.getMetadata("dbg");
            if (DILocation *loc = dyn_cast<DILocation>(node))
            {
                lineNo = loc->getLine();
                fileName = loc->getFilename();
            }
        }
        Indirection *u = new Indirection(1, true, SINGLE);
        GPUNode *leftNode = new UseNode("use@", lineNo, fileName, u);
        GPU *gpu = new GPU(leftNode, listOfNodes[i], lineNo, fileName);
        gpuSet.insert(gpu);
    }
    // outs() << dyn_cast<CallInst>(&I)->getCalledValue()->getName() << "\n";
    resultant->setGPUSet(gpuSet);
    return resultant;
}

Function* FunctionWithGPG::getFunction()
{
    return fun;
}

#include <fstream>
void FunctionWithGPG::constructGPG(map<StringRef, FunctionWithGPG *> &fToGPG,
                                   Util *util)
{
    // outs() << "\t\tconstruct GPG\n";
    /// this is for finding adjacency in GPG
    /// for every basic block, first GPB and last GPB
    map<string, pair<GPB *, GPB *>> bbNameGPBs;
    /// need to look in (removed in future)
    /// long insNo=1;
    GPG *gpg = new GPG();
    /// create entry block
    GPB *entryBlock = new GPB();
    /// prev, current GPBs
    GPB *prevGPB, *currentGPB, *firstGPB;
    gpg->setEntryNode(entryBlock);
    gpg->insertGPB(entryBlock);
    prevGPB = entryBlock;

    slim_transform = new Transform();

    fstream file;
    file.open("dump.txt", ios::app);
    file << "\n------------------------------------\nFunction : " << fun->getName().data() << endl;

    BasicBlock& firstBlock = fun->getEntryBlock();

    stack<GPB*> GPBStack;
    stack<BasicBlock> basicBlockStack;

    //basicBlockStack.push(firstBlock);

    /*while(!basicBlockStack.empty()){
        BasicBlock& curr = basicBlockStack.top();
    }*/

    std::map<BasicBlock*,std::pair<GPB*, GPB*>> constructedGPBs;

    FOR_EACH_BASICBLOCK(*fun)
    {
        /** Try slim integration*/
        slim_transform->simplifyIR(fun, &BB);
        slim_transform->setLhsRhsMap(fun, &BB);
        //slim_transform->optimizeTheSlimIR();
        //slim_transform->printGlobalInstrList(true);

        // stack 1, phi, 2 3 4
        // stack2 1created , phi, 2created- 3 created- 4 created,

        bool withInBB = false;
        bool firstInBB = true;


        /*for(auto &index : funcBBInsMap[{f,bb}]) { //llvm::outs() << "\n Forward contains a method call Index: "<<index;
                    auto &inst = globalInstrIndexList[index];*/
        outs() << "GPUs detected by SLIM" << "\n";
        for(auto &index : slim_transform->getfuncBBInsMap()[{fun,&BB}]){
            auto &inst = slim_transform->getGlobalInstrIndexList()[index];
            //() << inst << "\n";
            //outs() << inst.getLHS().first->getName() << "-" << inst.getLHS().second << "->" << inst.getRHS()[0].first->getName() << "-" << inst.getRHS()[0].second <<"\n";
            outs() << "found\n";
        }






        //FOR_EACH_INSTRUCTION(BB)
        for(auto &index : slim_transform->getfuncBBInsMap()[{fun,&BB}])
        {
            auto &inst = slim_transform->getGlobalInstrIndexList()[index];
            GPB *createdGPB = NULL;
            bool inliningPending = false;

            if(!inst.getCall() /*&& inst.getLHS().second != 999*/){
                GPUNode *leftNode =
                        new SpatialNode(inst.getLHS().first, new Indirection(inst.getLHS().second, true, SINGLE));

                GPUNode *rightNode =
                        new SpatialNode(inst.getRHS()[0].first, new Indirection(inst.getRHS()[0].second, true, SINGLE));

                GPU *gpu = new GPU(leftNode, rightNode, 0, "dummy");

                GPB *gpBlock = new GPB(gpu);
                createdGPB = gpBlock;

                /*GPUNode *rightNode = new AllocationSiteNode(tempName.str()  + "@allocasite@", lineNo, fileName,
                                                            new Indirection(0, true, SINGLE));

                GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
                gpuSet.insert(gpu);
                GPB *gpBlock = new GPB(gpuSet);
                //gpBlock->print();
                return gpBlock;*/
            }

            // outs() << I << "\n";
            /*switch (I.getOpcode())
            {

            case Instruction::Alloca:
                createdGPB = processAllocaInstruction(I);
                break;

            case Intrinsic::dbg_value:
                if (DbgValueInst *dbgValue = dyn_cast<DbgValueInst>(&I))
                    if (Value *v = dbgValue->getValue())
                        if (v->getType()->isPointerTy())
                            createdGPB = processDebugValueInstruction(dbgValue);
                break;
            case Instruction::Load:
                if (Value *rv = dyn_cast<Value>(&I))
                    if (!rv->getType()->isPointerTy())
                        createdGPB = processNonPointerLoadInstruction(I);
                    else
                        createdGPB = processPointerLoadInstruction(I);
                break;
            case Instruction::Store:
            {
                // source operand
                Value *sourceOpr = I.getOperand(0);
                // outs() << sourceOpr->getType()->getTypeID() << "\n";
                if (sourceOpr->getType()->isPointerTy())
                {
                    // pointer statements
                    createdGPB = processPointerStoreInstruction(I, fToGPG);
                }
                else
                {
                    // for use nodes
                    createdGPB = processNonPointerStoreInstruction(I);
                }
                break;
            }*/
             if(inst.getPhi()){
                 set<GPU*, GPUComp> gpuSet;
                 GPUNode *leftNode =
                         new SpatialNode(inst.getLHS().first, new Indirection(1, true, SINGLE));
                for(auto& rhs : inst.getRHS()){
                    GPUNode *rightNode =
                            new SpatialNode(rhs.first, new Indirection(1, true, SINGLE));

                    GPU *gpu = new GPU(leftNode, rightNode, 0, "dummy");

                    gpuSet.insert(gpu);
                }
                createdGPB = new GPB(gpuSet);
             }
            /*case Instruction::PHI:{
                if(PHINode *node = dyn_cast<PHINode>(&I))
                    createdGPB = processPointerPhiInstruction(*node);
                break;
            }
            case Instruction::Call:
            {
             */ if(inst.getCall()) {
                 llvm::Instruction &I = *slim_transform->getInstforIndx(index);
                // CallSite cs = CallSite(cast<CallInst>(inst.getRHS()[0].first));
                llvm::outs() << "hi";

                if (DbgDeclareInst *dbgDeclare = dyn_cast<DbgDeclareInst>(&I))
                    createdGPB = generateGPBforDebugDeclareInstruction(*dbgDeclare);
                if(DbgValueInst *dbgValue = dyn_cast<DbgValueInst>(&I)){
                    createdGPB = generateGPBforDebugValueInstruction(*dbgValue);
                }
                CallSite cs = CallSite(cast<CallInst>(&I));
                // if(cs.getCalledFunction())
                // outs() << cs.getCalledFunction()->getName() << "**\n";
                if (!cs.isIndirectCall())
                {
                    if (cs.getCalledFunction() && util->libraryFunctionOrNot(cs.getCalledFunction()->getName()))
                    {
                        //outs()<<cs.getCalledFunction()->getName()<<"   eeeeeeee\n";
                        //No operation
                    }
                    else if (cs.getCalledFunction() && cs.getCalledFunction()->isDeclaration())
                    {
                        //No operation
                    }
                    else if (cs.getCalledFunction() && util->testCaseFunctionOrNot(cs.getCalledFunction()->getName()))
                    {
                        createdGPB = handleTestCaseFunctions(I);
                    }
                    else if (cs.getCalledFunction() && fToGPG.find(cs.getCalledFunction()->getName()) == fToGPG.end())
                    {

                        // outs() << cs.getCalledFunction()->getName() << "\n";
                        if (util->isItPartOfSCC(fun->getName()) && util->isItPartOfSCC(cs.getCalledFunction()->getName()))
                        {
                            createdGPB = new GPB();
                            createdGPB->setAsRecursiveCallBlock();                            
                            GPU *top;
                            if(fun->getName() == cs.getCalledFunction()->getName())
                                top = new GPU(NULL, NULL, -11, "");
                            else
                                top = new GPU(NULL, NULL, -12, cs.getCalledFunction()->getName());                            

                            set<GPU *, GPUComp> gpuSet;
                            gpuSet.insert(top);
                            createdGPB->setGPUSet(gpuSet);
                        }
                        else
                        {
                            outs() << " \nSummary of Caller Not available \n";
                            exit(0);
                        }
                    }
                    else if (cs.getCalledFunction())
                    {

                        vector<StringRef> formalArgumentNames = fToGPG[cs.getCalledFunction()->getName()]->getFormalArgumentNames();
                        //process pointer arguments
                        if (formalArgumentNames.size() > 0)
                            createdGPB = processPointerArgumentsInFunctionCall(I, formalArgumentNames);
                        inliningPending = true;
                    }
                }
                else if (cs.isIndirectCall())
                {
                    // outs() << I << ": fp-call\n";
                    createdGPB = processFPCallInst(I);
                }
            }
            /*break;
            }*/

            //gpb created for the statement
            if (createdGPB != NULL)
            {
                //createdGPB->print();
                currentGPB = createdGPB;
                if (firstInBB == true)
                {
                    firstGPB = currentGPB;
                    firstInBB = false;
                }
                gpg->insertGPB(currentGPB);

                if (withInBB == true || prevGPB == entryBlock)
                {
                    gpg->addSuccessortoBB(prevGPB->getGPBNo(), currentGPB);
                    gpg->addPredecessortoBB(currentGPB->getGPBNo(), prevGPB);
                    gpg->addEdge(prevGPB->getGPBNo(), currentGPB->getGPBNo());
                    outs() << prevGPB->getGPBNo() << " " << currentGPB->getGPBNo() << "\n";
                }

                withInBB = true;
                prevGPB = currentGPB;
                bbNameGPBs[BB.getName()] = make_pair(currentGPB, currentGPB);
            }

            if (inliningPending)
            {
                // in-line procedure
                map<long, long> oldToNew;
                map<long, GPB *> newGPBMap;
                GPG *calleGPG;
                CallSite cs;
                //if (isa<CallInst>(&I))
                if(inst.getCall()) //TODO
                {
                    cs = CallSite(cast<CallInst>(&(*slim_transform->getInstforIndx(index))));
                    if (cs.getCalledFunction())
                    {
                        calleGPG = fToGPG[cs.getCalledFunction()->getName()]->getSummary();
                    }
                }
                 outs() << "Inlining " << cs.getCalledFunction()->getName()<< " started  \n";
                map<long, GPB *> GPBsMap = calleGPG->getGPBMap();
                set<GPB *, GPBComp> GPBSet = calleGPG->getGPBSet();
                set<GPB *, GPBComp>::iterator itrSet, itrSuccSet, itrPredSet;
                //calleGPG->print();
                // create a copy of new GPBs for all GPBs in callee
                FOR_EACH_ELEMENT_WITHITR(GPBSet, itrSet)
                {
                    GPB *newGPB = new GPB();
                    set<GPU *, GPUComp> newGPUSet = (*itrSet)->getGPUSet();
                    //util->print(newGPUSet);
                    set<GPU *, GPUComp> inlineGPUSet = newGPUSet;
                    newGPB->setGPUSet(inlineGPUSet);
                    newGPB->setisInlined(1);
                    set<GPUNode *, GPUNodeComp> mayDefs = (*itrSet)->getMayDefSet();
                    newGPB->setMayDefSet(mayDefs);
                    oldToNew[(*itrSet)->getGPBNo()] = newGPB->getGPBNo();
                    newGPBMap[newGPB->getGPBNo()] = newGPB;
                    gpg->insertGPB(newGPB);
                    bbNameGPBs[BB.getName()] = make_pair(newGPB, newGPB);
                }
                //  add and edge to start node of callee
                GPB *calleeStartNode = calleGPG->getEntryNode();
                //outs()<<calleeStartNode->getGPBNo();
                currentGPB = newGPBMap[oldToNew[calleeStartNode->getGPBNo()]];
                //outs()<<"Test inlining";
                if (firstInBB == true)
                {
                    firstGPB = currentGPB;
                    firstInBB = false;
                }

                withInBB = true;

                gpg->addSuccessortoBB(prevGPB->getGPBNo(), currentGPB);
                gpg->addPredecessortoBB(currentGPB->getGPBNo(), prevGPB);
                outs() << prevGPB->getGPBNo() << " -> " <<  currentGPB->getGPBNo() << "\n";
                gpg->addEdge(prevGPB->getGPBNo(), currentGPB->getGPBNo());
                // add the remaining edges of callee in copies of new GPBs
                FOR_EACH_ELEMENT_WITHITR(GPBSet, itrSet)
                {
                    set<GPB *, GPBComp> succSet = (*itrSet)->getAllSuccessors();
                    long newGPBNo = oldToNew[(*itrSet)->getGPBNo()];
                    //outs()<<"Test \n";
                    FOR_EACH_ELEMENT_WITHITR(succSet, itrSuccSet)
                    {
                        long succGPBNo = oldToNew[(*itrSuccSet)->getGPBNo()];
                        gpg->addSuccessortoBB(newGPBNo, newGPBMap[succGPBNo]);
                        outs() << newGPBNo << " " << newGPBMap[succGPBNo]->getGPBNo() << "\n";
                    }
                    set<GPB *, GPBComp> predSet = (*itrSet)->getAllPredecessors();
                    FOR_EACH_ELEMENT_WITHITR(predSet, itrPredSet)
                    {
                        long predGPBNo = oldToNew[(*itrPredSet)->getGPBNo()];
                        // outs()<<"Pred:  "<<predGPBNo;
                        gpg->addPredecessortoBB(newGPBNo, newGPBMap[predGPBNo]);
                        outs() << newGPBNo << " " << newGPBMap[predGPBNo]->getGPBNo() << "\n";
                    }
                }
                // set the end node to connect to next nodes after caller
                GPB *calleeEndNode = calleGPG->getExitNode();
                currentGPB = newGPBMap[oldToNew[calleeEndNode->getGPBNo()]];
                prevGPB = currentGPB;
                //if (isa<CallInst>(&I))
                //{
                //    if (cs.getType()->isPointerTy())
                //        processCallReturn(I, fToGPG[cs.getCalledFunction()->getName()]->getReturnNodes());
                //}
                //outs()<<*(cs.getType())<<I.getName()<<"\n";
                // outs() << "Inlining of" << cs.getCalledFunction()->getName()<< " finished\n";
            }
        } // end of Instruction block

        if (firstInBB == true)
        {

            currentGPB = new GPB();
            gpg->insertGPB(currentGPB);

            if (prevGPB == entryBlock)
            {
                gpg->addSuccessortoBB(prevGPB->getGPBNo(), currentGPB);
                currentGPB->addPredecessor(prevGPB);
                gpg->addEdge(prevGPB->getGPBNo(), currentGPB->getGPBNo());
                outs() << prevGPB->getGPBNo() << " " << currentGPB->getGPBNo() << "\n";
            }

            prevGPB = currentGPB;

            bbNameGPBs[BB.getName()] = make_pair(currentGPB, currentGPB);
        }
        else
            bbNameGPBs[BB.getName()] = make_pair(firstGPB, currentGPB);

    } // end of basic block

    /// create exit block
    GPB *exitBlock = new GPB();
    gpg->setExitNode(exitBlock);
    gpg->insertGPB(exitBlock);

    FOR_EACH_BASICBLOCK(*fun)
    {
        GPB *lastGPB = bbNameGPBs[BB.getName()].second;
        // outs()<<"begin-----------\n";
        // lastGPB->print();
        bool noSucc = true;

        for (BasicBlock *succ : successors(&BB))
        {
            noSucc = false;
            firstGPB = bbNameGPBs[succ->getName()].first;
            // firstGPB->print();
            gpg->addSuccessortoBB(lastGPB->getGPBNo(), firstGPB);
            gpg->addPredecessortoBB(firstGPB->getGPBNo(), lastGPB);
            gpg->addEdge(lastGPB->getGPBNo(), firstGPB->getGPBNo());
            outs() << lastGPB->getGPBNo() << " " << firstGPB->getGPBNo() << "\n";
            // lastGPB->addSuccessor(firstGPB);
            // firstGPB->addPredecessor(lastGPB);
        }
        // outs()<<"end-------------\n";
        if (noSucc == true)
        {
            gpg->addSuccessortoBB(lastGPB->getGPBNo(), exitBlock);
            gpg->addPredecessortoBB(exitBlock->getGPBNo(), lastGPB);
            gpg->addEdge(lastGPB->getGPBNo(), exitBlock->getGPBNo());
            // lastGPB->addSuccessor(exitBlock);
            // exitBlock->addPredecessor(lastGPB);
        }
    }

    file << "Number of GPBs initially constructed -> " << gpg->getGPBSet().size() << endl;

    int gpusInGPG = 0;
    file << "GPB freq - ";
    for(auto &GPB : gpg->getGPBSet()){
        file << GPB->getGPUSet().size() << ",";
        gpusInGPG += GPB->getGPUSet().size();

    }
    file << endl;
    for(auto &GPB : gpg->getGPBSet()){
        for(auto &GPU : GPB->getGPUSet()){
            file << GPU->toString() << " | ";
        }
    }
    file << endl;
    file << "Number of GPUs initially constructed - " << gpusInGPG << endl;
    file.close();

    //gpg->print();
    // gpg->printGraph();
    string funName = fun->getName();
    string dotFileName = funName + "-gpg.dot";
    gpg->printToDot(dotFileName);
#ifdef PRINT_TO_DOT
#if PRINT_TO_DOT == 1
    gpg->printToDot(dotFileName);
#endif
#endif    
    summary = gpg;
    summary->dump(funName + "-initialGPGDump");
}

/*void FunctionWithGPG::performEmptyNodeAnalysisOnGPG(){

   summary->emptyNodeAnalysis();

   string funName = fun->getName();
   string dotFileName = funName +"gpgAfterEmpty.dot";

   summary->printToDot(dotFileName);

   // summary->printGraph();
}*/

GPB *FunctionWithGPG::handleTestCaseFunctions(Instruction &I)
{

    GPB *gpb = NULL;

    StringRef funPointsTo("POINTSTO");
    StringRef funNotPointsTo("NOTPOINTSTO");
    StringRef funInitialGPU("INITIALGPU");
    StringRef funInterGPU("INTERMEDIATEGPU");
    StringRef funCoalesce("COALESCE");
    StringRef funNotCoalesce("NOCOALESCE");

    CallSite cs = CallSite(cast<CallInst>(&I));
    StringRef funName = cs.getCalledFunction()->getName();

    if (funName.equals(funPointsTo) || funName.equals(funNotPointsTo))
        gpb = processPointsToTestFunctions(I);
    else if (funName.equals(funInitialGPU) || funName.equals(funInterGPU))
        processGPUTestCaseFunctions(I);
    else if (funName.equals(funCoalesce) || funName.equals(funNotCoalesce))
        processCoalesceTestCaseFunctions(I);

    return gpb;
}
/**
 * @brief Removing GPUs from each GPB of kind (a,1) -> (a,1) [2].
 * 
 * @param gpbs 
 */
void FunctionWithGPG::preprocessGPUSet(map<long, GPB *> gpbs)
{
    for (auto gpb = gpbs.begin(); gpb != gpbs.end(); gpb++)
    {
        set<GPU *, GPUComp> NewGPUSet;
        auto GPUset = (*gpb).second->getGPUSet();
        for (auto gpu = GPUset.begin(); gpu != GPUset.end(); gpu++)
        {
            GPUNode *source = (*gpu)->getSourceOfGPU();
            GPUNode *target = (*gpu)->getTargetOfGPU();
            if (!source || !target)
            {
                if(!source && !target)
                    NewGPUSet.insert(*gpu);
                continue;
            }
            bool skip = 0; // Whether to skip the current GPU or not

            if (source->getNameOfVariable().equals(target->getNameOfVariable()))
            {
                Indirection *slist = source->getIndirectList();
                Indirection *tlist = target->getIndirectList();
                int sourceilev = source->getIndirectList()->getIndirectionLevel();
                int targetilev = target->getIndirectList()->getIndirectionLevel();
                // if both source and target of GPU has a list.
                if (isa<IndirectionList>(slist) && isa<IndirectionList>(tlist))
                {
                    if (sourceilev == targetilev)
                    {
                        vector<int> source_list = dyn_cast<IndirectionList>(slist)->getFieldList();
                        vector<int> target_list = dyn_cast<IndirectionList>(tlist)->getFieldList();
                        // Both source and target should have list of same size.
                        if (source_list.size() == target_list.size())
                        {
                            for (int i = 0; i < target_list.size(); i++)
                            {
                                if (source_list[i] == target_list[i])
                                    skip = 1;
                                else
                                {
                                    skip = 0;
                                    break;
                                }
                            }
                        }
                    }
                }
                // if source of GPU has a list.
                else if (isa<IndirectionList>(slist) && !isa<IndirectionList>(tlist))
                {
                    if (sourceilev == targetilev)
                    {
                        int source_list_size = dyn_cast<IndirectionList>(slist)->getNumberOfFields();
                        if (source_list_size == 0)
                        {
                            skip = 1;
                        }
                    }
                }
                // if target of GPU has a list.
                else if (!isa<IndirectionList>(slist) && isa<IndirectionList>(tlist))
                {
                    if (sourceilev == targetilev)
                    {
                        int target_list_size = dyn_cast<IndirectionList>(tlist)->getNumberOfFields();
                        if (target_list_size == 0)
                        {
                            skip = 1;
                        }
                    }
                }
                // if neither source or target has a list.
                else if (!isa<IndirectionList>(slist) && !isa<IndirectionList>(tlist))
                {
                    if (sourceilev == targetilev)
                    {
                        skip = 1;
                    }
                }
            }
            if (!skip)
                NewGPUSet.insert(*gpu);
        }
        (*gpb).second->setGPUSet(NewGPUSet);
    }
}
/**
 * @brief Removes the GPUs with source as UseNode to prevents its propagation.
 * 
 * @param CurOut 
 * @return set<GPU*, GPUComp> 
 */
set<GPU *, GPUComp> FunctionWithGPG::removeUseGPUs(set<GPU *, GPUComp> CurOut)
{
    set<GPU *, GPUComp> UpdatedOut;
    for (set<GPU *, GPUComp>::iterator it = CurOut.begin(); it != CurOut.end(); it++)
    {
        if ((*it)->getSourceOfGPU() && !isa<UseNode>((*it)->getSourceOfGPU()))
        {
            UpdatedOut.insert(*it);
        }
    }
    return UpdatedOut;
}
void FunctionWithGPG::reachingGPUAnalysisWithOutBlocking()
{

    map<long, set<GPU *, GPUComp>> genSet;
    map<long, set<GPU *, GPUComp>> inMinusKillSet;
    map<long, set<GPU *, GPUComp>> inSet;
    map<long, set<GPU *, GPUComp>> outSet;
    map<long, set<GPU *, GPUComp>> killSet;
    set<GPU*, GPUComp> AddToRGOut;

    set<long> outEdges;
    set<long> inEdges;

    set<GPU *, GPUComp> newOut, emptyBlockedSet;

    set<GPU *, GPUComp> blank;

    set<GPU *, GPUComp>::iterator elem;

    map<long, GPB *> gpbs = summary->getGPBMap();

    Util util;

    set<long> workList;

    int curGPB, inNode;

    preprocessGPUSet(gpbs);

    /*initialize outSet of all nodes with empty(Union problem)*/
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {

        outSet[(*bItr).first] = blank;
        inSet[(*bItr).first] = blank;
    }

    long stGPBNo = summary->getEntryNode()->getGPBNo();

    inSet[stGPBNo] = getBoundaryDef();

    // outSet[stGPBNo].insert(inSet[stGPBNo].begin(),inSet[stGPBNo].end());
    // outSet[entry] = inSet[entry]
    for (elem = inSet[stGPBNo].begin(); elem != inSet[stGPBNo].end(); elem++)
        outSet[stGPBNo].insert(*elem);

        // test print

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 2
    outs() << "\nBlock: " << stGPBNo << "\n";
    util.print(stGPBNo, inSet[stGPBNo], 1);
    util.print(stGPBNo, outSet[stGPBNo], 4);
#endif
#if VERBOSE_LEVEL == 10
    outs() << "\nBlock: " << stGPBNo << "\n";
    util.print(stGPBNo, inSet[stGPBNo], 1);
    util.print(stGPBNo, outSet[stGPBNo], 4);
#endif
#endif

    // GPG is connected

    outEdges = summary->getEdgeOut()[stGPBNo];

    for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
        workList.insert(*eItr);

    // util.print(workList);

    while (!workList.empty())
    {

        set<long>::iterator nItr = workList.begin();

        curGPB = *nItr;
        workList.erase(curGPB);

        // in = U pred(Out)
        inEdges = summary->getEdgeIn()[curGPB];

        for (auto eItr = inEdges.begin(); eItr != inEdges.end(); eItr++)
        {

            inNode = *eItr;

            for (elem = outSet[inNode].begin(); elem != outSet[inNode].end(); elem++)
                inSet[curGPB].insert(*elem);

            // inSet[curGPB].insert(outSet[inNode].begin(),outSet[inNode].end());
        }

        // gen = delta_{n} o In
        if (!gpbs[curGPB]->isItRecursiveCallBlock())
            genSet[curGPB] = gpbs[curGPB]->augmentedGPUReductionOverBlock(inSet[curGPB], emptyBlockedSet).first;
        else
        {
            genSet[curGPB] = gpbs[curGPB]->getGPUSet();        
            for(auto it : genSet[curGPB])
            {
                AddToRGOut.insert(it);
            }
        }                   

        // kill set: Kill(Gen,IN), find strong updates
        if (!gpbs[curGPB]->isItRecursiveCallBlock())
            killSet[curGPB] = gpbs[curGPB]->computeKillSet(genSet[curGPB], inSet[curGPB]);
        else
            killSet[curGPB] = inSet[curGPB];

        // in-kill
        if (!gpbs[curGPB]->isItRecursiveCallBlock())
            inMinusKillSet[curGPB] = gpbs[curGPB]->computeInMinusKill(inSet[curGPB], killSet[curGPB]);
        else
            inMinusKillSet[curGPB] = blank;

        newOut.clear();
        // out = gen U (in -kill)
        for (elem = genSet[curGPB].begin(); elem != genSet[curGPB].end(); elem++)
            newOut.insert(*elem);

        for (elem = inMinusKillSet[curGPB].begin();
             elem != inMinusKillSet[curGPB].end(); elem++)
            newOut.insert(*elem);

        newOut = removeUseGPUs(newOut);

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 2
        outs() << "\nBlock: " << curGPB << "\n";
        util.print(curGPB, inSet[curGPB], 1);
        util.print(curGPB, genSet[curGPB], 2);
        util.print(curGPB, killSet[curGPB], 6);
        util.print(curGPB, inMinusKillSet[curGPB], 3);
        util.print(curGPB, newOut, 4);
#endif
#if VERBOSE_LEVEL == 10
        outs() << "\nBlock: " << curGPB << "\n";
        util.print(curGPB, inSet[curGPB], 1);
        util.print(curGPB, genSet[curGPB], 2);
        util.print(curGPB, killSet[curGPB], 6);
        util.print(curGPB, inMinusKillSet[curGPB], 3);
        util.print(curGPB, newOut, 4);
#endif
#endif
        // if there is a change in the out, add successors to the WorkList
        //if (newOut != outSet[curGPB]) {
        if (!util.isEqualOrNot(newOut, outSet[curGPB]))
        {
            outEdges = summary->getEdgeOut()[curGPB];
            for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
                workList.insert(*eItr);
        }

        for (elem = newOut.begin(); elem != newOut.end(); elem++)
            outSet[curGPB].insert(*elem);
    }

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 12
    outs() << "\nBlock: "
           << "\t\t\t";
    outs() << "RGIn \t\t\t";
    outs() << "RGOut \n";
    util.print('-');
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        outs() << "\n"
               << curGPB << "\t\t\t";
        util.print(curGPB, inSet[curGPB], -1);
        if (inSet[curGPB].size() > 0)
            outs() << "\t";
        else
            outs() << "\t\t";
        util.print(curGPB, outSet[curGPB], -4);
        outs() << "\n";
        util.print('-');
    }
#endif
#if VERBOSE_LEVEL == 10
    outs() << "\nBlock: "
           << "\t\t\t";
    outs() << "RGIn \t\t\t";
    outs() << "RGOut \n";
    util.print('-');
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        outs() << "\n"
               << curGPB << "\t\t";
        util.print(curGPB, inSet[curGPB], -1);
        if (inSet[curGPB].size() > 0)
            outs() << "\t";
        else
            outs() << "\t\t";
        util.print(curGPB, outSet[curGPB], -4);
        outs() << "\n";
        util.print('-');
    }
#endif
#endif

    long endGPBNo = summary->getExitNode()->getGPBNo();
    set<GPU *, GPUComp> outSetWithOutUpWardExposed = getGPUSetWithOutUpWardExposed(outSet[endGPBNo]);    
    for(auto it : AddToRGOut) { outSetWithOutUpWardExposed.insert(it); }
    setRGOutOfEnd(false, outSetWithOutUpWardExposed);
}

//@brief Forward flow analysis, Reaching GPU by considering barriers
void FunctionWithGPG::reachingGPUAnalysisWithBlocking()
{

    map<long, set<GPU *, GPUComp>> genSet;
    map<long, set<GPU *, GPUComp>> inMinusKillSet;
    map<long, set<GPU *, GPUComp>> inSet;
    map<long, set<GPU *, GPUComp>> outSet;
    map<long, set<GPU *, GPUComp>> killSet;
    map<long, set<GPU *, GPUComp>> blockedSet;
    map<long, set<GPU *, GPUComp>> killBlockedSet;
    map<long, set<GPU *, GPUComp>> boundarySetAdded;
    set<GPU*, GPUComp> AddToRGOut;
    set<long> outEdges;
    set<long> inEdges;

    set<GPU *, GPUComp> newOut;

    set<GPU *, GPUComp> blank;

    set<GPU *, GPUComp>::iterator elem;

    map<long, GPB *> gpbs = summary->getGPBMap();

    Util util;

    set<long> workList;

    int curGPB, inNode;

    /*initialize outSet of all nodes with empty(Union problem)*/
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {

        outSet[(*bItr).first] = blank;
        inSet[(*bItr).first] = blank;
    }

    long stGPBNo = summary->getEntryNode()->getGPBNo();

    inSet[stGPBNo] = getBoundaryDef();

    for (elem = inSet[stGPBNo].begin(); elem != inSet[stGPBNo].end(); elem++)
        outSet[stGPBNo].insert(*elem);

        // test print
#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 3
    outs() << "\nBlock: " << stGPBNo << "\n";
    util.print(stGPBNo, inSet[stGPBNo], 1);
    util.print(stGPBNo, outSet[stGPBNo], 4);
#endif
#if VERBOSE_LEVEL == 10
    outs() << "\nBlock: " << stGPBNo << "\n";
    util.print(stGPBNo, inSet[stGPBNo], 1);
    util.print(stGPBNo, outSet[stGPBNo], 4);
#endif
#endif

    // GPG is connected

    outEdges = summary->getEdgeOut()[stGPBNo];

    for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
        workList.insert(*eItr);

    // util.print(workList);
    while (!workList.empty())
    {

        set<long>::iterator nItr = workList.begin();

        curGPB = *nItr;

        workList.erase(curGPB);

        // in = U pred(Out)
        inEdges = summary->getEdgeIn()[curGPB];

        for (auto eItr = inEdges.begin(); eItr != inEdges.end(); eItr++)
        {

            inNode = *eItr;

            for (elem = outSet[inNode].begin(); elem != outSet[inNode].end(); elem++)
                inSet[curGPB].insert(*elem);

            // inSet[curGPB].insert(outSet[inNode].begin(),outSet[inNode].end());
        }

        // gen = delta_{n} o In
        if (!gpbs[curGPB]->isItRecursiveCallBlock())
            genSet[curGPB] = gpbs[curGPB]->augmentedGPUReductionOverBlock(inSet[curGPB], blockedSet[curGPB]).first;
        else
        {
            genSet[curGPB] = gpbs[curGPB]->getGPUSet();
            for(auto it : genSet[curGPB])
            {
                AddToRGOut.insert(it);
            } 

        }        

        //blocked GPUs TODO
        /*if (!gpbs[curGPB]->isItRecursiveCallBlock())
            blockedSet[curGPB] = gpbs[curGPB]->getBlockedGPUs(inSet[curGPB], genSet[curGPB]);
        else
            blockedSet[curGPB] = blank;
*/
        // kill set: Kill(Gen,IN), find strong updates
        if (!gpbs[curGPB]->isItRecursiveCallBlock())
            killSet[curGPB] = gpbs[curGPB]->computeKillSet(genSet[curGPB], inSet[curGPB]);
        else
            killSet[curGPB] = inSet[curGPB];

        // Killblocked = Kill(Gen,IN) U blockedSet

        for (elem = killSet[curGPB].begin(); elem != killSet[curGPB].end(); elem++)
            killBlockedSet[curGPB].insert(*elem);

        for (elem = blockedSet[curGPB].begin(); elem != blockedSet[curGPB].end(); elem++)
            killBlockedSet[curGPB].insert(*elem);

        // in-kill

        if (!gpbs[curGPB]->isItRecursiveCallBlock())
            inMinusKillSet[curGPB] = gpbs[curGPB]->computeInMinusKill(inSet[curGPB], killBlockedSet[curGPB]);
        else
            inMinusKillSet[curGPB] = blank;

        newOut.clear();
        // out = gen U (in -kill) U (x->x'[i|i], if x->y[i|j] is belongs to blocked set )
        for (elem = genSet[curGPB].begin(); elem != genSet[curGPB].end(); elem++)
            newOut.insert(*elem);

        for (elem = inMinusKillSet[curGPB].begin();
             elem != inMinusKillSet[curGPB].end(); elem++)
            newOut.insert(*elem);

        if (!gpbs[curGPB]->isItRecursiveCallBlock())
            boundarySetAdded[curGPB] = addingBoundaryGPUsDueToBlocking(blockedSet[curGPB], killSet[curGPB]);
        else
            boundarySetAdded[curGPB] = blank;

        for (elem = boundarySetAdded[curGPB].begin(); elem != boundarySetAdded[curGPB].end(); elem++)
            newOut.insert(*elem);

        newOut = removeUseGPUs(newOut);

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 3
        outs() << "\nBlock: " << curGPB << "\n";
        util.print(curGPB, inSet[curGPB], 1);
        util.print(curGPB, genSet[curGPB], 2);
        util.print(curGPB, killSet[curGPB], 6);
        util.print(curGPB, blockedSet[curGPB], 5);
        util.print(curGPB, killBlockedSet[curGPB], 8);
        util.print(curGPB, inMinusKillSet[curGPB], 3);
        util.print(curGPB, boundarySetAdded[curGPB], 7);
        util.print(curGPB, newOut, 4);
#endif
#if VERBOSE_LEVEL == 10
        outs() << "\nBlock: " << curGPB << "\n";
        util.print(curGPB, inSet[curGPB], 1);
        util.print(curGPB, genSet[curGPB], 2);
        util.print(curGPB, killSet[curGPB], 6);
        util.print(curGPB, blockedSet[curGPB], 5);
        util.print(curGPB, killBlockedSet[curGPB], 8);
        util.print(curGPB, inMinusKillSet[curGPB], 3);
        util.print(curGPB, boundarySetAdded[curGPB], 7);
        util.print(curGPB, newOut, 4);
#endif
#endif

        // if there is a change in the out, add successors to the WorkList
        // if (newOut != outSet[curGPB])

        if (!util.isEqualOrNot(newOut, outSet[curGPB]))
        {
            outEdges = summary->getEdgeOut()[curGPB];
            for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
                workList.insert(*eItr);
        }

        for (elem = newOut.begin(); elem != newOut.end(); elem++)
            outSet[curGPB].insert(*elem);
    }

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 13
    outs() << "\nBlock: "
           << "\t\t\t";
    outs() << "RGIn' \t\t\t";
    outs() << "RGOut' \n";
    util.print('-');
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        outs() << "\n"
               << curGPB << "\t\t\t";
        util.print(curGPB, inSet[curGPB], -1);
        if (inSet[curGPB].size() > 0)
            outs() << "\t";
        else
            outs() << "\t\t";
        util.print(curGPB, outSet[curGPB], -4);
        outs() << "\n";
        util.print('-');
    }
#endif
#if VERBOSE_LEVEL == 10
    outs() << "\nBlock: "
           << "\t\t\t";
    outs() << "RGIn' \t\t\t";
    outs() << "RGOut' \n";
    util.print('-');
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        outs() << "\n"
               << curGPB << "\t\t";
        util.print(curGPB, inSet[curGPB], -1);
        if (inSet[curGPB].size() > 0)
            outs() << "\t";
        else
            outs() << "\t\t";
        util.print(curGPB, outSet[curGPB], -4);
        outs() << "\n";
        util.print('-');
    }
#endif
#endif    
    // Strength reduction and set rgIn, rgOut of every block
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {

        curGPB = (*bItr).first;
        pair<set<GPU *, GPUComp>, set<GPU *, GPUComp>> simplifiedAndUndesSet;

        if (!gpbs[curGPB]->isItRecursiveCallBlock())
        {

            simplifiedAndUndesSet = gpbs[curGPB]->augmentedGPUReductionOverBlock(inSet[curGPB], blockedSet[curGPB]);

            set<GPU *, GPUComp> simplifiedSet = simplifiedAndUndesSet.first;
            set<GPU *, GPUComp> undseriableSet = simplifiedAndUndesSet.second;

            set<GPU *, GPUComp> simplifiedSetWithoutUpWardExposed = getGPUSetWithOutUpWardExposed(simplifiedSet);

            gpbs[curGPB]->setGPUSet(simplifiedSetWithoutUpWardExposed);

            for (elem = undseriableSet.begin(); elem != undseriableSet.end(); elem++)
                addToQueuedSet(*elem);
        }
        gpbs[curGPB]->setRGBlockingIn(inSet[curGPB]);
        gpbs[curGPB]->setRGBlockingOut(outSet[curGPB]);
    }

    // GPUs that are blocked should be added to Queue.
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {

        curGPB = (*bItr).first;

        for (elem = blockedSet[curGPB].begin(); elem != blockedSet[curGPB].end(); elem++)
        {
            addToQueuedSet(*elem);
        }
    }
    // What GPUs are reaching to the end of procedure
    long endGPBNo = summary->getExitNode()->getGPBNo();
    set<GPU *, GPUComp> outSetWithOutUpWardExposed = getGPUSetWithOutUpWardExposed(outSet[endGPBNo]);
    for(auto it : AddToRGOut) { outSetWithOutUpWardExposed.insert(it); }
    setRGOutOfEnd(true, outSetWithOutUpWardExposed);

    string funName = fun->getName();
    string dotFileName = funName + "gpgAfterStrengthReduction.dot";

    summary->setGPBMap(gpbs);
#ifdef PRINT_TO_DOT
#if PRINT_TO_DOT == 1
    summary->printToDot(dotFileName);
#endif // PRINT_TO_DOT == 1
#endif // PRINT_TO_DOT
}

//@brief Backward flow analysis

void FunctionWithGPG::removeEmptyNodesInGPG()
{

    map<long, set<long>> genSet;
    map<long, set<long>> outMinusKillSet;
    map<long, set<long>> inSet;
    map<long, set<long>> outSet;
    set<long> outEdges;
    set<long> inEdges;

    set<long> newIn;

    set<long>::iterator elem;

    map<long, GPB *> gpbs = summary->getGPBMap();

    Util util;

    set<long> workList;

    long curGPB, outNode;

    /*outs()<<"..................ee\n";

  for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++) {

      outs()<<(*bItr).first<<" ";

  }*/

    /*initialize inSet,Outset of all nodes with empty(Union problem)*/
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {

        set<long> blank;

        curGPB = (*bItr).first;
        outSet[curGPB] = blank;
        inSet[curGPB] = blank;

        //s outs()<<curGPB <<"........\n\n";
        // gen = {n} or {}
        if (!gpbs[curGPB]->isEmpty())
        {

            genSet[curGPB].insert(curGPB);
            workList.insert(curGPB);
        }
        else if (curGPB == summary->getEntryNode()->getGPBNo() ||
                 curGPB == summary->getExitNode()->getGPBNo())
        {

            genSet[curGPB].insert(curGPB);
            workList.insert(curGPB);
        }
        else
            genSet[curGPB] = blank;
    }

    // outs()<<"...............eeeeeeeeeeeeeeeee\n";

    while (!workList.empty())
    {

        set<long>::iterator nItr = workList.begin();

        curGPB = *nItr;

        workList.erase(curGPB);

        // Out = U succ(In)
        outEdges = summary->getEdgeOut()[curGPB];

        for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
        {

            outNode = *eItr;

            for (elem = inSet[outNode].begin(); elem != inSet[outNode].end(); elem++)
                outSet[curGPB].insert(*elem);

            // inSet[curGPB].insert(outSet[inNode].begin(),outSet[inNode].end());
        }

        // out-kill   out or {}
        if (!gpbs[curGPB]->isEmpty())
            outMinusKillSet[curGPB].clear();
        else if (curGPB == summary->getEntryNode()->getGPBNo() ||
                 curGPB == summary->getExitNode()->getGPBNo())
            outMinusKillSet[curGPB].clear();
        else
            for (elem = outSet[curGPB].begin(); elem != outSet[curGPB].end(); elem++)
                outMinusKillSet[curGPB].insert(*elem);

        newIn.clear();
        // in = gen U (out -kill)
        for (elem = genSet[curGPB].begin(); elem != genSet[curGPB].end(); elem++)
            newIn.insert(*elem);

        for (elem = outMinusKillSet[curGPB].begin();
             elem != outMinusKillSet[curGPB].end(); elem++)
            newIn.insert(*elem);

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 4
        outs() << "\nBlock: " << curGPB << "\n";
        util.print(curGPB, outSet[curGPB], 4);
        util.print(curGPB, genSet[curGPB], 2);
        util.print(curGPB, outMinusKillSet[curGPB], 3);
        util.print(curGPB, newIn, 1);
#endif
#if VERBOSE_LEVEL == 10
        outs() << "\nBlock: " << curGPB << "\n";
        util.print(curGPB, outSet[curGPB], 4);
        util.print(curGPB, genSet[curGPB], 2);
        util.print(curGPB, outMinusKillSet[curGPB], 3);
        util.print(curGPB, newIn, 1);
#endif
#endif

        // if there is a change in the in, add predecssors to the WorkList
        if (newIn != inSet[curGPB])
        {

            inEdges = summary->getEdgeIn()[curGPB];
            for (auto eItr = inEdges.begin(); eItr != inEdges.end(); eItr++)
                workList.insert(*eItr);
        }

        for (elem = newIn.begin(); elem != newIn.end(); elem++)
            inSet[curGPB].insert(*elem);

        // util.print(workList);
    }

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 14
    outs() << "\nBlock: "
           << "\t";
    outs() << "In \t\t\t\t\t";
    outs() << "Out \n";
    util.print('-');
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        outs() << "\n"
               << curGPB << "\t";
        util.print(curGPB, inSet[curGPB], -1);
        if (inSet[curGPB].size() > 0)
            outs() << "\t";
        else
            outs() << "\t\t\t\t";
        util.print(curGPB, outSet[curGPB], -4);
        outs() << "\n";
        util.print('-');
    }
#endif
#if VERBOSE_LEVEL == 10
    outs() << "\nBlock: "
           << "\t";
    outs() << "In \t\t\t\t\t";
    outs() << "Out \n";
    util.print('-');
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        outs() << "\n"
               << curGPB << "\t";
        util.print(curGPB, inSet[curGPB], -1);
        if (inSet[curGPB].size() > 0)
            outs() << "\t";
        else
            outs() << "\t\t\t\t";
        util.print(curGPB, outSet[curGPB], -4);
        outs() << "\n";
        util.print('-');
    }
#endif
#endif

    /*for(auto bItr= gpbs.begin();bItr!=gpbs.end();bItr++) {

     curGPB = (*bItr).first;
     util.print(curGPB,outSet[curGPB],4);
  }*/

    long EntryNodeNo = summary->getEntryNode()->getGPBNo();
    long ExitNodeNo = summary->getExitNode()->getGPBNo();

    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {

        curGPB = (*bItr).first;

        if (!gpbs[curGPB]->isEmpty() || curGPB == EntryNodeNo ||
            curGPB == ExitNodeNo)
        {

            for (elem = outSet[curGPB].begin(); elem != outSet[curGPB].end();
                 elem++)
            {
                summary->addSuccessortoBB(curGPB, gpbs[*elem]);
                summary->addPredecessortoBB(*elem, gpbs[curGPB]);
            }

            set<GPB *, GPBComp> succSet = gpbs[curGPB]->getAllSuccessors();

            set<GPB *, GPBComp>::iterator itrSuccSet, itrPredSet;

            FOR_EACH_ELEMENT_WITHITR(succSet, itrSuccSet)
            {

                long succGPBNo = (*itrSuccSet)->getGPBNo();

                if ((*itrSuccSet)->isEmpty() && succGPBNo != EntryNodeNo &&
                    succGPBNo != ExitNodeNo)
                {
                    summary->removeSuccessorOfBB(curGPB, gpbs[succGPBNo]);
                    summary->removePredecessorOfBB(succGPBNo, gpbs[curGPB]);
                }
            }
            set<GPB *, GPBComp> predSet = gpbs[curGPB]->getAllPredecessors();

            FOR_EACH_ELEMENT_WITHITR(predSet, itrPredSet)
            {

                long predGPBNo = (*itrPredSet)->getGPBNo();

                if ((*itrPredSet)->isEmpty() && predGPBNo != EntryNodeNo &&
                    predGPBNo != ExitNodeNo)
                {
                    summary->removePredecessorOfBB(curGPB, gpbs[predGPBNo]);
                    summary->removeSuccessorOfBB(predGPBNo, gpbs[curGPB]);
                }
            }
        }
    }

    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {

        curGPB = (*bItr).first;

        if (gpbs[curGPB]->isEmpty() && curGPB != EntryNodeNo &&
            curGPB != ExitNodeNo)
        {

            // outs()<<curGPB<<"removed \n";
            summary->removeGPB(gpbs[curGPB]);
        }
    }

    string funName = fun->getName();
    string dotFileName = funName + "gpgAfterEmpty.dot";

    /*gpbs = summary->getGPBMap();

  for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++) {

     outs()<<"GPB :"<<(*bItr).first<<"\n";
  }*/

#ifdef PRINT_TO_DOT
#if PRINT_TO_DOT == 1
    summary->printToDot(dotFileName);
#endif // PRINT_TO_DOT == 1
#endif // PRINT_TO_DOT
}

set<GPU *, GPUComp> FunctionWithGPG::addingBoundaryGPUsDueToBlocking(set<GPU *, GPUComp> blockedSet, set<GPU *, GPUComp> killSet)
{

    set<GPU *, GPUComp> addedDueToBlocked;
    set<GPU *, GPUComp> blockedMinusKillGPUSet;

    for (auto blockItr = blockedSet.begin(); blockItr != blockedSet.end(); blockItr++)
    {
        // not there in Kill set
        if (killSet.find(*blockItr) == killSet.end())
            blockedMinusKillGPUSet.insert(*blockItr);
    }

    for (auto blockItr = blockedMinusKillGPUSet.begin(); blockItr != blockedMinusKillGPUSet.end(); blockItr++)
    {

        GPUNode *leftOfBlocked = (*blockItr)->getSourceOfGPU();

        // same indirection level for both left and right
        Indirection *list = leftOfBlocked->getIndirectList();
        IndirectionList *indlist = llvm::dyn_cast<IndirectionList>(list);
        int listlen = 0;
        if (indlist)
        {
            listlen = indlist->getNumberOfFields();
        }
        // type at this indirection level is same
        Type *type = leftOfBlocked->getTypeOfVariableAtIndirection(list->getIndirectionLevel() + listlen);
        // type at this indirection level is same

        if (type == NULL)
        {
            outs() << "Not handeled this type\n";
            exit(0);
        }

        StringRef name = leftOfBlocked->getNameOfVariable();

        if (isa<GlobalNode>(leftOfBlocked))
        {

            StringRef upName = globalToUpwardExposedVersion[name];
            StringRef blank;

            GPUNode *right = new TmpNode(upName, blank, list, type);

            GPU *gpu = new GPU(leftOfBlocked, right, 0, blank);

            addedDueToBlocked.insert(gpu);
        }
        else if (isa<TmpNode>(leftOfBlocked))
        {

            if (isUpwardExposed(name))
            {

                GlobalVariable *var = upwardExposedToGlobalVariable[name];

                GPUNode *leftNode = new GlobalNode(var, list);

                StringRef blank;

                GPU *gpu = new GPU(leftNode, leftOfBlocked, 0, blank);

                addedDueToBlocked.insert(gpu);
            }
        }

        else
        {
            outs() << "Not handeled this Node\n";
            exit(0);
        }
    }

    return addedDueToBlocked;
}

void FunctionWithGPG::deadGPUElimination()
{

    map<long, GPB *> gpbs = summary->getGPBMap();
    long curGPB;
    set<GPU *, GPUComp> gpuSet;

    // initially it contains EndRG with blocking
    set<GPU *, GPUComp> unionEndQ = getRGOutOfEnd(true);

    set<GPU *, GPUComp> endRGWOBlocking = getRGOutOfEnd(false);

    set<GPU *, GPUComp> qSet = getQueuedSet();

    // Union of EndRGWB, EndRGWOB, Queued

    for (auto elem = endRGWOBlocking.begin(); elem != endRGWOBlocking.end(); elem++)
        unionEndQ.insert(*elem);

    for (auto elem = qSet.begin(); elem != qSet.end(); elem++)
        unionEndQ.insert(*elem);

    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {

        set<GPU *, GPUComp> tmpGpuSet;
        curGPB = (*bItr).first;
        gpuSet = gpbs[curGPB]->getGPUSet();

        // elem belongs unionEndQ should be retained, all other removed
        // and all use node must be retained
        // if (!gpbs[curGPB]->isItRecursiveCallBlock())
        // {

            for (auto gItr = gpuSet.begin(); gItr != gpuSet.end(); gItr++)
            {

                GPUNode *leftNode = (*gItr)->getSourceOfGPU();
                if (leftNode && isa<UseNode>(leftNode))
                    tmpGpuSet.insert(*gItr);
                else if (unionEndQ.find(*gItr) != unionEndQ.end())
                    tmpGpuSet.insert(*gItr);
            }
        // }

        // else
        //     tmpGpuSet.insert(*gItr);
            // gpbs[curGPB]->setAsRecursiveCallBlock(false);

        /* for(auto tItr= tmpGpuSet.begin();tItr!=tmpGpuSet.end();tItr++){
                  (*tItr)->print();

         }*/

        gpbs[curGPB]->setGPUSet(tmpGpuSet);
    }

    string funName = fun->getName();
    string dotFileName = funName + "gpgAfterDeadGPUElimination.dot";

    summary->setGPBMap(gpbs);

#ifdef PRINT_TO_DOT
#if PRINT_TO_DOT == 1
    summary->printToDot(dotFileName);
#endif // PRINT_TO_DOT == 1
#endif // PRINT_TO_DOT
}

/*  May be required in future
void  FunctionWithGPG::livenessAnalysis(){

  map<long, set<StringRef>> genSet;
  map<long, set<StringRef>> outMinusKillSet;
  map<long, set<StringRef>> inSet;
  map<long, set<StringRef>> outSet;
  set<long> outEdges;
  set<long> inEdges;

  set<long> newIn;

  set<long>::iterator elem;

  map<long, GPB *> gpbs = summary->getGPBMap();

  Util util;

  set<long> workList;

  long curGPB, inNode;

  // initialize inSet,Outset of all nodes with empty(Union problem)
  for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++) {

    set<StringRef> empty;

    curGPB = (*bItr).first;
    outSet[curGPB] = empty;
    inSet[curGPB] = empty;

    // gen = {x,y}  given (x,i)->(y,j) i>1 and j>0 
    if (!gpbs[curGPB]->isEmpty()) {

      

    } else if (curGPB == summary->getEntryNode()->getGPBNo() ||
               curGPB == summary->getExitNode()->getGPBNo()) {

     // genSet[curGPB].insert(curGPB);
      workList.insert(curGPB);
    } else
      genSet[curGPB] = empty;
  }

  // long exGPBNo = summary->getExitNode()->getGPBNo();

  // outs()<<"\nBlock: "<<exGPBNo<<"\n";

  // test print
  // util.print(exGPBNo,outSet[exGPBNo],4);

  // In = Gen
  // for(elem=genSet[exGPBNo].begin(); elem!=genSet[exGPBNo].end();elem++)
  //       inSet[curGPB].insert(*elem);

  // test print
  // util.print(exGPBNo,inSet[exGPBNo],1);

  // util.print(workList);

}*/

void FunctionWithGPG::addToQueuedSet(GPU *gpu)
{
    queuedSet.insert(gpu);
}

set<GPU *, GPUComp> FunctionWithGPG::getQueuedSet()
{
    return queuedSet;
}

//@brief sets RGOUT of RGWithblocking if withblocking_or_not is true
//       sets RGOUT of RGWithoutBlocking if withblocking_or_not is false
void FunctionWithGPG::setRGOutOfEnd(bool withblocking_or_not, set<GPU *, GPUComp> outRG)
{

    if (withblocking_or_not == true)
        endRGWithBlocking = outRG;
    else
        endRGWithOutBlocking = outRG;
}

//@brief get RGOUT of RGWithblocking if withblocking_or_not is true
//       get RGOUT of RGWithoutBlocking if withblocking_or_not is false
set<GPU *, GPUComp> FunctionWithGPG::getRGOutOfEnd(bool withblocking_or_not)
{

    if (withblocking_or_not == true)
        return endRGWithBlocking;
    else
        return endRGWithOutBlocking;
}

//@brief coalescing, bi-directional flow analysis

void FunctionWithGPG::coalescingAnalysisInPaper()
{

    map<long, bool> inCoalescSet;
    map<long, bool> outCoalescSet;

    map<long, set<GPU *, GPUComp>> inGPUSet;
    map<long, set<GPU *, GPUComp>> outGPUSet;

    set<long> outEdges;
    set<long> inEdges;

    set<long> workList;
    long curGPB;

    long EntryNodeNo;

    long ExitNodeNo;

    set<long> succToEntry;

    set<long> predToExit;

    bool newInCol, newOutCol;
    set<GPU *, GPUComp> newOut;

    Util util;

    map<long, GPB *> gpbs = summary->getGPBMap();

    /* initialize with false */
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        outCoalescSet[curGPB] = false;
        inCoalescSet[curGPB] = false;
        workList.insert(curGPB);
    }

    ExitNodeNo = summary->getExitNode()->getGPBNo();
    inEdges = summary->getEdgeIn()[ExitNodeNo];

    for (auto eItr = inEdges.begin(); eItr != inEdges.end(); eItr++)
        predToExit.insert(*eItr);

    EntryNodeNo = summary->getEntryNode()->getGPBNo();
    outEdges = summary->getEdgeOut()[EntryNodeNo];

    for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
        succToEntry.insert(*eItr);

    while (!workList.empty())
    {

        set<long>::iterator nItr = workList.begin();
        curGPB = *nItr;
        workList.erase(curGPB);

        // In_n  = n.pred(n.gpuflow(m))
        inEdges = summary->getEdgeIn()[curGPB];

        for (auto eItr = inEdges.begin(); eItr != inEdges.end(); eItr++)
        {

            long inNode = *eItr;
            set<GPU *, GPUComp> inPredGPUSet;
            inPredGPUSet = gpbs[curGPB]->computeGPUFlow(outGPUSet[inNode], inCoalescSet[curGPB]);

            for (auto elem = inPredGPUSet.begin(); elem != inPredGPUSet.end(); elem++)
                inGPUSet[curGPB].insert(*elem);
        }

        newOut = gpbs[curGPB]->getGPUSet();
        // union with inGPUSet
        if (inCoalescSet[curGPB])
        {

            for (auto elem = inGPUSet[curGPB].begin(); elem != inGPUSet[curGPB].end(); elem++)
                newOut.insert(*elem);
        }

        newOutCol = false;
        if (predToExit.find(curGPB) == predToExit.end() && (curGPB != EntryNodeNo))
        {

            // Out_n = n.succ(coalsec)
            outEdges = summary->getEdgeOut()[curGPB];

            for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
            {
                long outNode = *eItr;
                // if any one of them is true set it to true
                if (inCoalescSet[outNode])
                {
                    newOutCol = true;
                    break;
                }
            }
        }

        // newInCol
        newInCol = false;
        // not a successor to start
        if (succToEntry.find(curGPB) == succToEntry.end() && (curGPB != ExitNodeNo))
        {

            inEdges = summary->getEdgeIn()[curGPB];

            for (auto eItr = inEdges.begin(); eItr != inEdges.end(); eItr++)
            {

                long inNode = *eItr;
                // if any one of them is true set it to true
                if (gpbs[curGPB]->coalesceOrNot(outCoalescSet[inNode], inCoalescSet[curGPB], outGPUSet[inNode]))
                {
                    newInCol = true;
                    break;
                }
            }
        }

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 5
        outs() << "\nBlock: " << curGPB << "\n";
        util.print(curGPB, inGPUSet[curGPB], 1);
        util.print(curGPB, newOut, 4);
        outs() << "\noutCoalescSet: " << newOutCol << "\n";
        outs() << "inCoalescSet:" << newInCol << "\n";
#endif
#if VERBOSE_LEVEL == 5
        outs() << "\nBlock: " << curGPB << "\n";
        util.print(curGPB, inGPUSet[curGPB], 1);
        util.print(curGPB, newOut, 4);
        outs() << "\noutCoalescSet: " << newOutCol << "\n";
        outs() << "inCoalescSet:" << newIn << "\n";
#endif
#endif

        if (newInCol != inCoalescSet[curGPB])
        {

            inEdges = summary->getEdgeIn()[curGPB];
            for (auto eItr = inEdges.begin(); eItr != inEdges.end(); eItr++)
                workList.insert(*eItr);
        }

        inCoalescSet[curGPB] = newInCol;

        if (newOutCol != outCoalescSet[curGPB])
        {
            outEdges = summary->getEdgeOut()[curGPB];
            for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
                workList.insert(*eItr);
        }

        outCoalescSet[curGPB] = newOutCol;

        //if (newOut != outGPUSet[curGPB]) {
        if (!util.isEqualOrNot(newOut, outGPUSet[curGPB]))
        {

            outEdges = summary->getEdgeOut()[curGPB];
            for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
                workList.insert(*eItr);
        }

        for (auto elem = newOut.begin(); elem != newOut.end(); elem++)
            outGPUSet[curGPB].insert(*elem);
    }

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 15
    outs() << "\nBlock: "
           << "\t";
    outs() << "ColIn \t";
    outs() << "ColOut \t\t";
    outs() << "GPUIn \t\t\t";
    outs() << "GPUOut \n";
    util.print('-');
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        outs() << "\n"
               << curGPB << "\t";
        outs() << inCoalescSet[curGPB] << " \t";
        outs() << outCoalescSet[curGPB] << "  \t";
        util.print(curGPB, inGPUSet[curGPB], -1);
        if (inGPUSet[curGPB].size() > 0)
            outs() << "\t";
        else
            outs() << "\t\t\t";
        util.print(curGPB, outGPUSet[curGPB], -4);
        outs() << "\n";
        util.print('-');
    }
#endif
#if VERBOSE_LEVEL == 10
    outs() << "\nBlock: "
           << "\t";
    outs() << "ColIn \t";
    outs() << "ColOut \t\t";
    outs() << "GPUIn \t\t\t";
    outs() << "GPUOut \n";
    util.print('-');
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        outs() << "\n"
               << curGPB << "\t";
        outs() << inCoalescSet[curGPB] << " \t";
        outs() << outCoalescSet[curGPB] << "  \t";
        util.print(curGPB, inGPUSet[curGPB], -1);
        if (inGPUSet[curGPB].size() > 0)
            outs() << "\t";
        else
            outs() << "\t\t\t";
        util.print(curGPB, outGPUSet[curGPB], -4);
        outs() << "\n";
        util.print('-');
    }
#endif
#endif
    // Use the coalescing analysis results for coalescing.

    map<long, bool> coalesced;

    map<long, long> partitionNoOfBlock;

    //vector<long> postOrderTraversal = summary->getReversePostOrder();

    vector<long> postOrderTraversal = summary->getBFSTraversal();

    // initialize to false, every block is in different part
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        coalesced[curGPB] = false;
        partitionNoOfBlock[curGPB] = -1;
    }

    map<long, set<GPB *, GPBComp>> partitionToBlocks;
    long curPartNo = 1;
    for (auto vItr = postOrderTraversal.begin(); vItr != postOrderTraversal.end(); vItr++)
    {

        long partNo = partitionNoOfBlock[*vItr];
        //set<GPB*,GPBComp>  inSamePartition;

        if (partNo == -1)
        {
            partitionNoOfBlock[*vItr] = curPartNo;
            partitionToBlocks[curPartNo].insert(gpbs[*vItr]);
        }

        if (outCoalescSet[*vItr])
        {

            outEdges = summary->getEdgeOut()[*vItr];

            for (auto outN = outEdges.begin(); outN != outEdges.end(); outN++)
            {
                if (inCoalescSet[*outN])
                {
                    long partNoSucc = partitionNoOfBlock[*outN];
                    if (partNoSucc == -1)
                    {
                        partitionNoOfBlock[*outN] = curPartNo;
                        partitionToBlocks[curPartNo].insert(gpbs[*outN]);
                    }
                }
            }
        }
        else
        {
            curPartNo++;
        }
    }

    /*outs()<<"\n";
    for(auto vItr = postOrderTraversal.begin();vItr!=postOrderTraversal.end();vItr++) {
       outs()<<partitionNoOfBlock[*vItr]<<",";
     }*/
}

//@brief coalescing, bi-directional flow analysis

void FunctionWithGPG::coalescingAnalysisInThesis()
{

    map<long, bool> inCoalescSet;
    map<long, bool> outCoalescSet;

    map<long, set<GPU *, GPUComp>> inGPUSet;
    map<long, set<GPU *, GPUComp>> outGPUSet;

    set<long> outEdges;
    set<long> inEdges;

    set<long> workList;
    long curGPB;

    long entryNodeNo;

    long exitNodeNo;

    set<long> succToEntry;

    set<long> predToExit;

    bool newInCol, newOutCol;
    set<GPU *, GPUComp> newOut;

    Util util;

    map<long, GPB *> gpbs = summary->getGPBMap();

    exitNodeNo = summary->getExitNode()->getGPBNo();

    entryNodeNo = summary->getEntryNode()->getGPBNo();

    //outs()<<"Coalescing Analysis started .........eeee\n";

    /* initialize with false */
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {

        curGPB = (*bItr).first;
        if (curGPB == exitNodeNo || curGPB == entryNodeNo || gpbs[curGPB]->isItRecursiveCallBlock())
        {
            outCoalescSet[curGPB] = false;
            inCoalescSet[curGPB] = false;
        }
        else
        {
            outCoalescSet[curGPB] = true;
            inCoalescSet[curGPB] = true;
            workList.insert(curGPB);
        }
    }

    inEdges = summary->getEdgeIn()[exitNodeNo];

    for (auto eItr = inEdges.begin(); eItr != inEdges.end(); eItr++)
        predToExit.insert(*eItr);

    outEdges = summary->getEdgeOut()[entryNodeNo];

    for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
        succToEntry.insert(*eItr);

    while (!workList.empty())
    {

        set<long>::iterator nItr = workList.begin();
        curGPB = *nItr;
        //util.print(workList);
        //outs()<<curGPB<<"\n";
        workList.erase(curGPB);

        // In_n  = n.pred(n.gpuflow(m))
        inEdges = summary->getEdgeIn()[curGPB];

        for (auto eItr = inEdges.begin(); eItr != inEdges.end(); eItr++)
        {

            long inNode = *eItr;
            set<GPU *, GPUComp> inPredGPUSet;
            inPredGPUSet = gpbs[curGPB]->computeGPUFlow(outGPUSet[inNode], inCoalescSet[curGPB]);

            for (auto elem = inPredGPUSet.begin(); elem != inPredGPUSet.end(); elem++)
                inGPUSet[curGPB].insert(*elem);
        }

        newOut = gpbs[curGPB]->getGPUSet();
        // union with inGPUSet
        if (inCoalescSet[curGPB])
        {

            for (auto elem = inGPUSet[curGPB].begin(); elem != inGPUSet[curGPB].end(); elem++)
                newOut.insert(*elem);
        }

        newOutCol = true;

        //if(curGPB!=ExitNodeNo && curGPB!=EntryNodeNo) {

        // Out_n = n.succ(coalesce)
        outEdges = summary->getEdgeOut()[curGPB];

        for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
        {
            long outNode = *eItr;
            // if any one of them is false set it to false
            if (inCoalescSet[outNode] == false)
            {
                newOutCol = false;
                break;
            }
        }
        //}
        //else  newOutCol = false;
        // newInCol
        newInCol = true;

        //if(curGPB!=EntryNodeNo && curGPB!=ExitNodeNo) {

        inEdges = summary->getEdgeIn()[curGPB];

        for (auto eItr = inEdges.begin(); eItr != inEdges.end(); eItr++)
        {
            long inNode = *eItr;
            // outs()<<"coalesce check: "<<inNode<<"  "<<curGPB<<"\n";
            // if any one of them is false set it to false
            if (gpbs[curGPB]->coalesceOrNot(outCoalescSet[inNode], inCoalescSet[curGPB], outGPUSet[inNode]) == false)
            {
                newInCol = false;
                //   outs()<<"cannot be coalesced \n";
                break;
            }
        }
        //}
        //else newInCol = false;

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 5
        outs() << "\nBlock: " << curGPB << "\n";
        util.print(curGPB, inGPUSet[curGPB], 1);
        util.print(curGPB, newOut, 4);
        outs() << "\noutCoalescSet: " << newOutCol << "\n";
        outs() << "inCoalescSet:" << newInCol << "\n";
#endif
#if VERBOSE_LEVEL == 5
        outs() << "\nBlock: " << curGPB << "\n";
        util.print(curGPB, inGPUSet[curGPB], 1);
        util.print(curGPB, newOut, 4);
        outs() << "\noutCoalescSet: " << newOutCol << "\n";
        outs() << "inCoalescSet:" << newIn << "\n";
#endif
#endif

        if (newInCol != inCoalescSet[curGPB])
        {

            inEdges = summary->getEdgeIn()[curGPB];
            for (auto eItr = inEdges.begin(); eItr != inEdges.end(); eItr++)
                if (*eItr != entryNodeNo)
                    workList.insert(*eItr);
        }

        inCoalescSet[curGPB] = newInCol;

        if (newOutCol != outCoalescSet[curGPB])
        {
            outEdges = summary->getEdgeOut()[curGPB];
            for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
                if (*eItr != exitNodeNo)
                    workList.insert(*eItr);
        }

        outCoalescSet[curGPB] = newOutCol;

        //if (newOut != outGPUSet[curGPB]) {
        if (!util.isEqualOrNot(newOut, outGPUSet[curGPB]))
        {

            outEdges = summary->getEdgeOut()[curGPB];
            for (auto eItr = outEdges.begin(); eItr != outEdges.end(); eItr++)
                if (*eItr != exitNodeNo)
                    workList.insert(*eItr);
        }

        // need to be tested
        outGPUSet[curGPB].clear();

        for (auto elem = newOut.begin(); elem != newOut.end(); elem++)
            outGPUSet[curGPB].insert(*elem);
    }

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 15
    outs() << "\nBlock: "
           << "\t";
    outs() << "ColIn \t";
    outs() << "ColOut \t\t";
    outs() << "GPUIn \t\t\t";
    outs() << "GPUOut \n";
    util.print('-');
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        outs() << "\n"
               << curGPB << "\t";
        outs() << inCoalescSet[curGPB] << " \t";
        outs() << outCoalescSet[curGPB] << "  \t";
        util.print(curGPB, inGPUSet[curGPB], -1);
        if (inGPUSet[curGPB].size() > 0)
            outs() << "\t";
        else
            outs() << "\t\t\t";
        util.print(curGPB, outGPUSet[curGPB], -4);
        outs() << "\n";
        util.print('-');
    }
#endif
#if VERBOSE_LEVEL == 10
    outs() << "\nBlock: "
           << "\t";
    outs() << "ColIn \t";
    outs() << "ColOut \t\t";
    outs() << "GPUIn \t\t\t";
    outs() << "GPUOut \n";
    util.print('-');
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        outs() << "\n"
               << curGPB << "\t";
        outs() << inCoalescSet[curGPB] << " \t";
        outs() << outCoalescSet[curGPB] << "  \t";
        util.print(curGPB, inGPUSet[curGPB], -1);
        if (inGPUSet[curGPB].size() > 0)
            outs() << "\t";
        else
            outs() << "\t\t\t";
        util.print(curGPB, outGPUSet[curGPB], -4);
        outs() << "\n";
        util.print('-');
    }
#endif
#endif

    //outs()<<"Analysis completed .........eeee\n";

    // Use the coalescing analysis results for coalescing.

    map<long, bool> coalesced;

    map<long, long> partitionNoOfBlock;

    vector<long> rPostOrderTraversal = summary->getReversePostOrder();

    //vector<long> postOrderTraversal = summary->getBFSTraversal();

    // initialize to false, every block is in different part
    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        curGPB = (*bItr).first;
        coalesced[curGPB] = false;
        partitionNoOfBlock[curGPB] = -1;
    }

    map<long, set<GPB *, GPBComp>> partitionToBlocks;
    long curPartNo = 1, nextPartNo;
    for (auto vItr = rPostOrderTraversal.begin(); vItr != rPostOrderTraversal.end(); vItr++)
    {

        if (*vItr == entryNodeNo || *vItr == exitNodeNo)
        {

            partitionNoOfBlock[*vItr] = curPartNo;
            partitionToBlocks[*vItr].insert(gpbs[*vItr]);
            curPartNo = curPartNo + 1;
        }

        long partNo = partitionNoOfBlock[*vItr];
        if (partNo == -1)
        {

            long curNode = *vItr;
            set<long> outEdges, emptySet;
            queue<long> nodeQueue;

            //outs()<<curNode<<"      eeeee\n";
            partitionNoOfBlock[curNode] = curPartNo;
            nextPartNo = curPartNo + 1;
            partitionToBlocks[curPartNo].insert(gpbs[curNode]);

            if (outCoalescSet[curNode])
                nodeQueue.push(curNode);

            while (!nodeQueue.empty())
            {

                curNode = nodeQueue.front();
                nodeQueue.pop();

                // outs()<<curNode<<"    eeeeeeee\n";
                if (curNode != exitNodeNo)
                    outEdges = summary->getEdgeOut()[curNode];
                else
                    outEdges = emptySet;
                if (outCoalescSet[curNode])
                {
                    for (auto n = outEdges.begin(); n != outEdges.end(); n++)
                    {
                        if (partitionNoOfBlock[*n] == -1)
                        {

                            nodeQueue.push(*n);
                            partitionNoOfBlock[*n] = curPartNo;
                            partitionToBlocks[curPartNo].insert(gpbs[*n]);
                        }
                    }
                }
            }
            curPartNo = nextPartNo;
        }
    }

    /*outs()<<"\n";
    for(auto vItr = rPostOrderTraversal.begin();vItr!=rPostOrderTraversal.end();vItr++) {
       outs()<<partitionNoOfBlock[*vItr]<<",";
     }*/

    vector<Partition *> vPartitions, tPartitions;
    for (auto pItr = partitionToBlocks.begin(); pItr != partitionToBlocks.end(); pItr++)
    {
        set<GPB *, GPBComp> sGPBs = (*pItr).second;
        Partition *part = new Partition(sGPBs, summary);

        /*outs()<<"\n {";
            for(auto sItr = sGPBs.begin(); sItr!=sGPBs.end();sItr++){
                long gpbNo = (*sItr)->getGPBNo();
                outs()<< (sItr==sGPBs.begin() ? "": ", ");
                outs()<<gpbNo;
            }
            outs()<<" }";*/

        if (!part->coherentOrNot(summary))
        {

            /*outs()<<"NOT COHERENT \n";
            outs()<<"\n {";
            for(auto sItr = sGPBs.begin(); sItr!=sGPBs.end();sItr++){
                long gpbNo = (*sItr)->getGPBNo();
                outs()<< (sItr==sGPBs.begin() ? "": ", ");
                outs()<<gpbNo;
            }
            outs()<<" }";*/

            tPartitions = part->getCoherentPartitions(summary);
            //util.print(tPartitions);
            for (auto vItr = tPartitions.begin(); vItr != tPartitions.end(); vItr++)
                vPartitions.push_back(*vItr);
        }

        else
            vPartitions.push_back(part);
    }

    //util.print(vPartitions);
    performCoalescing(vPartitions);
}

set<GPU *, GPUComp> FunctionWithGPG::getGPUSetWithOutUpWardExposed(set<GPU *, GPUComp> originalSet)
{

    set<GPU *, GPUComp> resultSet;

    for (auto elem = originalSet.begin(); elem != originalSet.end(); elem++)
    {

        GPUNode *leftInline, *rightInline;
        GPUNode *leftOrg = (*elem)->getSourceOfGPU();
        GPUNode *rightOrg = (*elem)->getTargetOfGPU();
        // Both not upward Exposed
        StringRef leftName = leftOrg->getNameOfVariable();
        StringRef rightName = rightOrg->getNameOfVariable();
        Indirection *leftInd = leftOrg->getIndirectList();
        Indirection *rightInd = rightOrg->getIndirectList();
        long stmtNo = (*elem)->getStmtNo();
        StringRef fileName = (*elem)->getFileName();

        if (isUpwardExposed(leftName))
            leftInline = new GlobalNode(upwardExposedToGlobalVariable[leftName], leftInd);
        else
            leftInline = leftOrg;

        if (isUpwardExposed(rightName))
            rightInline = new GlobalNode(upwardExposedToGlobalVariable[rightName], rightInd);
        else
            rightInline = rightOrg;

        GPU *gpu = new GPU(leftInline, rightInline, stmtNo, fileName);
        resultSet.insert(gpu);
    }

    return resultSet;
}

void FunctionWithGPG::performCoalescing(vector<Partition *> vPartitions)
{

    map<long, GPB *> gpbs = summary->getGPBMap();

    map<long, GPB *> newgpbs;

    map<long, Partition *> partitionMap;

    map<long, bool> visited;

    map<long, GPB *> partitionIdToNewOrOldGPB;

    map<long, long> gpbIdToPartitionId;

    GPG *gpgAfterCoalescing = new GPG();

    Util util;

    for (auto vItr = vPartitions.begin(); vItr != vPartitions.end(); vItr++)
    {

        set<GPB *, GPBComp> gpbSet = (*vItr)->getGPBs();

        // (*vItr)->print();

        if ((*vItr)->partitionHasEntryNodeOfGPG(summary))
        {

            set<GPB *, GPBComp>::iterator gItr = gpbSet.begin();

            partitionIdToNewOrOldGPB[(*vItr)->getPartitionId()] = gpbs[(*gItr)->getGPBNo()];

            gpbIdToPartitionId[(*gItr)->getGPBNo()] = (*vItr)->getPartitionId();

            //  outs()<<"Test "<<((*gItr)->getGPBNo())<<"\n";

            gpgAfterCoalescing->setEntryNode((*gItr));

            (*gItr)->removeAllSuccessors();

            gpgAfterCoalescing->insertGPB((*gItr));
        }

        else if ((*vItr)->partitionHasExitNodeOfGPG(summary))
        {

            set<GPB *, GPBComp>::iterator gItr = gpbSet.begin();

            gpbIdToPartitionId[(*gItr)->getGPBNo()] = (*vItr)->getPartitionId();

            partitionIdToNewOrOldGPB[(*vItr)->getPartitionId()] = gpbs[(*gItr)->getGPBNo()];

            gpgAfterCoalescing->setExitNode((*gItr));

            (*gItr)->removeAllPredecessors();

            gpgAfterCoalescing->insertGPB((*gItr));
        }

        else
        {

            set<GPU *, GPUComp> mergedGPUSet;

            for (auto gItr = gpbSet.begin(); gItr != gpbSet.end(); gItr++)
            {

                gpbIdToPartitionId[(*gItr)->getGPBNo()] = (*vItr)->getPartitionId();

                set<GPU *, GPUComp> gpuSet = (*gItr)->getGPUSet();

                for (auto gpuItr = gpuSet.begin(); gpuItr != gpuSet.end(); gpuItr++)
                    mergedGPUSet.insert((*gpuItr));
            }

            partitionMap[(*vItr)->getPartitionId()] = *vItr;

            if ((*vItr)->size() > 1)
            {

                GPB *newGPB = new GPB();

                newGPB->setGPUSet(mergedGPUSet);

                set<GPUNode *, GPUNodeComp> mayDefs = (*vItr)->mayDefSetsOfPartition();

                /*for(auto elem= mayDefs.begin();elem!=mayDefs.end();elem++)
                       newGPB->addElmntToMayDefSet(*elem);*/
                newGPB->setMayDefSet(mayDefs);

                //util.print(mayDefs);

                gpgAfterCoalescing->insertGPB(newGPB);

                partitionIdToNewOrOldGPB[(*vItr)->getPartitionId()] = newGPB;
            }
            else
            {

                set<GPB *, GPBComp>::iterator gItr = gpbSet.begin();

                partitionIdToNewOrOldGPB[(*vItr)->getPartitionId()] = gpbs[(*gItr)->getGPBNo()];

                gpgAfterCoalescing->insertGPB((*gItr));
                (*gItr)->removeAllSuccessors();
                (*gItr)->removeAllPredecessors();
            }
        }
    }

    for (auto vItr = vPartitions.begin(); vItr != vPartitions.end(); vItr++)
    {

        set<long> predSet = (*vItr)->getPredecessorsOfPartition(summary);
        set<long> succSet = (*vItr)->getSuccessorsOfPartition(summary);

        GPB *node = partitionIdToNewOrOldGPB[(*vItr)->getPartitionId()];

        //add successors to GPB
        for (auto succ = succSet.begin(); succ != succSet.end(); succ++)
        {

            long partitionNo = gpbIdToPartitionId[*succ];
            gpgAfterCoalescing->addSuccessortoBB(node->getGPBNo(), partitionIdToNewOrOldGPB[partitionNo]);
        }

        //add prdecessors to GPB
        for (auto pred = predSet.begin(); pred != predSet.end(); pred++)
        {

            long partitionNo = gpbIdToPartitionId[*pred];
            gpgAfterCoalescing->addPredecessortoBB(node->getGPBNo(), partitionIdToNewOrOldGPB[partitionNo]);
        }

        newgpbs[node->getGPBNo()] = node;
    }

    summary = gpgAfterCoalescing;

    string funName = fun->getName();
    string dotFileName = funName + "gpgAfterCoalescing.dot";

    summary->setGPBMap(newgpbs);
#ifdef PRINT_TO_DOT
#if PRINT_TO_DOT == 1
    summary->printToDot(dotFileName);
#endif // PRINT_TO_DOT == 1
#endif // PRINT_TO_DOT
    //summary->print();
}

void FunctionWithGPG::addPointsToTestCase(StringRef fName, long lno, StringRef var, StringRef pToList, bool pOrN)
{

    //outs()<<"line:"<<lno<<"\n";
    TestCase *ptest = new PointsToTest(fName, lno, var, pToList, pOrN);
    list<TestCase *> lst;
    lst.push_back(ptest);
    testCases[lno] = lst;
}

void FunctionWithGPG::processGPUTestCaseFunctions(Instruction &I)
{

    CallSite cs = CallSite(cast<CallInst>(&I));

    string tempName = I.getName();

    StringRef fileName;
    long lineNo;
    Util util;

    /*get line number and file name */
    if (I.hasMetadata())
    {
        MDNode *node = I.getMetadata("dbg");
        if (DILocation *loc = dyn_cast<DILocation>(node))
        {
            lineNo = loc->getLine();
            fileName = loc->getFilename();
        }
    }
    else
        util.debugInfoErrorMsg(I);

    if (!cs.isIndirectCall())
    {

        StringRef funInitialGPU("INITIALGPU");
        StringRef funInterGPU("INTERMEDIATEGPU");
        Function *function = cs.getCalledFunction();
        StringRef funName = function->getName();

        if (funName.equals(funInitialGPU) || funName.equals(funInterGPU))
        {

            if (cs.getNumArgOperands() == 2)
            {

                Value *arg1 = cs.getArgument(0);

                Value *arg2 = cs.getArgument(1);

                StringRef gpuStr;

                if (Constant *cv = dyn_cast<Constant>(arg2))
                    if (ConstantExpr *cexpr = dyn_cast<ConstantExpr>(cv))
                    {
                        Instruction *inst = cexpr->getAsInstruction();
                        if (GetElementPtrInst *gEPI = dyn_cast<GetElementPtrInst>(inst))
                        {
                            Value *baseOpr = gEPI->getPointerOperand();
                            if (GlobalVariable *gv = dyn_cast<GlobalVariable>(baseOpr))
                            {
                                if (ConstantDataArray *ar = dyn_cast<ConstantDataArray>(gv->getInitializer()))
                                    gpuStr = ar->getAsCString();
                            }
                        }
                    }

                long linegpu;

                if (ConstantInt *CI = dyn_cast<ConstantInt>(arg1))
                    linegpu = CI->getSExtValue();

                //outs()<<constIntValue<<"\t"<<gpuStr<<"\n";
                if (funName.equals(funInitialGPU))
                    addInitialGPUTestCase(fileName, lineNo, gpuStr, linegpu);
                else
                    addInterGPUTestCase(fileName, lineNo, gpuStr, linegpu);
            }
        }
    }
}

void FunctionWithGPG::processCoalesceTestCaseFunctions(Instruction &I)
{

    CallSite cs = CallSite(cast<CallInst>(&I));

    string tempName = I.getName();
    StringRef fileName;
    long lineNo;
    Util util;

    /*get line number and file name */
    if (I.hasMetadata())
    {

        MDNode *node = I.getMetadata("dbg");
        if (DILocation *loc = dyn_cast<DILocation>(node))
        {
            lineNo = loc->getLine();
            fileName = loc->getFilename();
        }
    }
    else
        util.debugInfoErrorMsg(I);

    if (!cs.isIndirectCall())
    {

        StringRef funCoalesce("COALESCE");
        StringRef funNotCoalesce("NOCOALESCE");
        Function *function = cs.getCalledFunction();
        StringRef funName = function->getName();

        if (funName.equals(funCoalesce) || funName.equals(funNotCoalesce))
        {

            if (cs.getNumArgOperands() == 2)
            {

                Value *arg1 = cs.getArgument(0);

                Value *arg2 = cs.getArgument(1);

                long line1, line2;

                if (ConstantInt *CI = dyn_cast<ConstantInt>(arg1))
                    line1 = CI->getSExtValue();
                if (ConstantInt *CI = dyn_cast<ConstantInt>(arg2))
                    line2 = CI->getSExtValue();

                //outs()<<constIntValue<<"\t"<<gpuStr<<"\n";
                if (funName.equals(funCoalesce))
                    addCoalesceTestCase(fileName, lineNo, line1, line2, true);
                else
                    addCoalesceTestCase(fileName, lineNo, line1, line2, false);
            }
        }
    }
}

void FunctionWithGPG::addInitialGPUTestCase(StringRef fName, long lineNo, StringRef gpu, long linegpu)
{

    TestCase *iGtest = new InitialGPUTest(fName, lineNo, gpu, linegpu);
    list<TestCase *> lst;
    lst.push_back(iGtest);
    testCases[linegpu] = lst;
}
void FunctionWithGPG::addInterGPUTestCase(StringRef fName, long lineNo, StringRef gpu, long linegpu)
{

    TestCase *iGtest = new IntermediateGPUTest(fName, lineNo, gpu, linegpu);
    list<TestCase *> lst;
    lst.push_back(iGtest);
    testCases[linegpu] = lst;
}
void FunctionWithGPG::addCoalesceTestCase(StringRef fName, long lineNo, long line1, long line2, bool cOrNot)
{

    TestCase *cTest = new CoalesceTest(fName, lineNo, line1, line2, cOrNot);
    list<TestCase *> lst;
    lst.push_back(cTest);
    testCases[lineNo] = lst;
}

void FunctionWithGPG::ValidateInitialGPUTests()
{

    map<long, GPB *> gpbMap = summary->getGPBMap();

    for (auto gItr = gpbMap.begin(); gItr != gpbMap.end(); gItr++)
    {

        set<GPU *, GPUComp> gpuSet = (*gItr).second->getGPUSet();

        for (auto gpuItr = gpuSet.begin(); gpuItr != gpuSet.end(); gpuItr++)
            if (testCases.find((*gpuItr)->getStmtNo()) != testCases.end())
            {

                list<TestCase *> lstTest = testCases[(*gpuItr)->getStmtNo()];

                for (auto lItr = lstTest.begin(); lItr != lstTest.end(); lItr++)
                {

                    if (InitialGPUTest *igpuTest = dyn_cast<InitialGPUTest>(*lItr))
                    {

                        outs() << "[GPG-PointsTo]: checking INITIALGPU \n";
                        StringRef userGPU = igpuTest->getGPU();
                        StringRef actualGPU = (*gpuItr)->toString();
                        //outs()<<"user:"<<userGPU<<"\n";
                        //outs()<<"actual:"<<actualGPU<<"\n";

                        Util util;
                        if (userGPU.equals(actualGPU))
                            outs() << util.succMsg("SUCCESS :");
                        else
                            outs() << util.failMsg("FAIL :");

                        outs() << "INITIALGPU Test at line:" << (*lItr)->getLineNo() << " in file: " << (*lItr)->getFileName() << "\n";
                    }
                }
                // (*gpuItr)->print();
                // outs()<<"\n";
            }
    }
}

void FunctionWithGPG::ValidatePointsToTests()
{

    for (auto testItr = testCases.begin(); testItr != testCases.end(); testItr++)
    {

        list<TestCase *> lstTest = (*testItr).second;

        for (auto lItr = lstTest.begin(); lItr != lstTest.end(); lItr++)
        {

            if (PointsToTest *pTest = dyn_cast<PointsToTest>(*lItr))
            {

                Util util;
                outs() << "[GPG-PointsTo]: checking PointsTo \n";

                if (pTest->ssaReplacedPointeeOrNot())
                {

                    if (pTest->gotSameDuringSSAConversionOrNot() == pTest->pointsToOrNotPointsToTest())
                        outs() << util.succMsg("SUCCESS :");
                    else
                        outs() << util.failMsg("FAIL:");
                }
                else
                {

                    set<StringRef> actualPointsTo = summary->getPointsToInfo((*lItr)->getLineNo());

                    if (actualPointsTo.empty())
                    {
                        outs() << util.needInfoMsg("ContextNeeded: ");
                    }
                    else
                    {
                        if (pTest->equalToUserPointsToSet(actualPointsTo))
                            outs() << util.succMsg("SUCCESS :");
                        else
                            outs() << util.failMsg("FAIL :");
                    }
                }
                outs() << "POINTSTO Test at line:" << (*lItr)->getLineNo() << " in file: " << (*lItr)->getFileName() << "\n";
            }
        }
    }
}

void FunctionWithGPG::ValidateCoalesceTests()
{

    Util util;

    for (auto testItr = testCases.begin(); testItr != testCases.end(); testItr++)
    {

        list<TestCase *> lstTest = (*testItr).second;

        for (auto lItr = lstTest.begin(); lItr != lstTest.end(); lItr++)
        {

            if (CoalesceTest *cTest = dyn_cast<CoalesceTest>(*lItr))
            {

                outs() << "[GPG-PointsTo]: checking Coalesce \n";
                if (cTest->coalesceOrNotCoalesceTest())
                {

                    if (summary->checkGPUsInSameBlockOrNot(cTest->getFirstLineNo(), cTest->getSecondLineNo()))
                        outs() << util.succMsg("SUCCESS :");
                    else
                        outs() << util.failMsg("FAIL :");
                }
                else
                {
                    if (summary->checkGPUsInSameBlockOrNot(cTest->getFirstLineNo(), cTest->getSecondLineNo()))
                        outs() << util.failMsg("FAIL :");
                    else
                        outs() << util.succMsg("SUCCESS :");
                }

                outs() << "CoalesceTest Test at line:" << (*lItr)->getLineNo() << " in file: " << (*lItr)->getFileName() << "\n";
            }
        }
    }
}

GPB *FunctionWithGPG::processDebugValueInstruction(DbgValueInst *dbgValue)
{

    set<GPU *, GPUComp> gpuSet;

    if (Value *v = dbgValue->getValue())
    {

        StringRef name = dbgValue->getVariable()->getName();
        long line = -5; //we have to get the line number
        StringRef file = dbgValue->getVariable()->getFile()->getName();

        //outs()<<name<<"e \n";

        if (GlobalVariable *gv = dyn_cast<GlobalVariable>(v))
        {

            Indirection *ind = new Indirection(1, true, SINGLE);

            GPUNode *left = new TmpNode(name, fun->getName(), ind, v->getType());

            Indirection *ind1 = new Indirection(0, true, SINGLE);
            GPUNode *right = new GlobalNode(gv, ind1);
            GPU *gpu = new GPU(left, right, line, file);
            gpuSet.insert(gpu);
        }

        else if (PHINode *node = dyn_cast<PHINode>(v))
        {

            return NULL;
        }
        else if (Argument *farg = dyn_cast<Argument>(v))
        {
            return NULL;
        }
        else
        {
            //outs()<<v->getName()<<"  e\n";
            if (tempToVariableSet.count(v->getName()) == 1)
            {

                StringRef tempName = v->getName();
                vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(tempName);
                FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
                {

                    if (isa<TmpNode>(listOfNodes[i]))
                    {

                        Indirection *ind = new Indirection(1, true, SINGLE);

                        GPUNode *left = new TmpNode(name, fun->getName(), ind, v->getType());

                        GPU *gpu = new GPU(left, listOfNodes[i], line, file);
                        gpuSet.insert(gpu);
                    }
                    else if (isa<AllocationSiteNode>(listOfNodes[i]))
                    {

                        Indirection *rList = listOfNodes[i]->getIndirectList();

                        Indirection *rOprList;

                        if (isa<IndirectionList>(rList))
                        {

                            IndirectionList *ctList = (IndirectionList *)rList;
                            rOprList = new IndirectionList(1, true, ctList->getNumberOfFields(), ctList->getFieldList());

                            GPUNode *left = new TmpNode(name, fun->getName(), rOprList, v->getType());

                            GPU *gpu = new GPU(left, listOfNodes[i], line, file);
                            gpuSet.insert(gpu);
                        }
                    }
                }
            }
            else
            {
                if (!isa<Argument>(v))
                {
                    // outs()<<v->getName()<<"  e\n";
                }
            }
        }

        GPB *gpb = new GPB(gpuSet);
        return gpb;
    }

    else
        return NULL;
}

void FunctionWithGPG::addSSAPointsToTestCase(StringRef fName, long lineNo, bool pOrNp, bool yOrN)
{

    TestCase *ptest = new PointsToTest(fName, lineNo, pOrNp, yOrN);
    list<TestCase *> lst;
    lst.push_back(ptest);
    testCases[lineNo] = lst;
}

void FunctionWithGPG::findPointsToPairs(map<long, std::pair<set<GPU *, GPUComp>, std::string>> &PointsToInfo)
{
    set<GPB *, GPBComp> GPBSet = summary->getGPBSet();
    for (auto gpb : GPBSet)
    {
        set<GPU *, GPUComp> gpuSet = gpb->getGPUSet();
        for (auto gpu : gpuSet)
        {
            PointsToInfo[gpu->getStmtNo()].first.insert(gpu);
            PointsToInfo[gpu->getStmtNo()].second = gpu->getFileName().str();
        }
    }
}

vector<StringRef> FunctionWithGPG::getFormalArgumentNames()
{

    return formalArguments;
}

GPB *FunctionWithGPG::processPointerArgumentsInFunctionCall(Instruction &I, vector<StringRef> formalArgumentNames)
{

    GPB *gpb;
    set<GPU *, GPUComp> gpuSet;
    CallSite cs = CallSite(cast<CallInst>(&I));
    Function *f = cs.getCalledFunction();

    StringRef fileName;
    long lineNo;
    Util util;

    /*get line number and file name */
    if (I.hasMetadata())
    {
        MDNode *node = I.getMetadata("dbg");
        if (DILocation *loc = dyn_cast<DILocation>(node))
        {
            lineNo = loc->getLine();
            fileName = loc->getFilename();
        }
    }
    else
        util.debugInfoErrorMsg(I);

    int numberOfPointerArguments = formalArgumentNames.size();

    int currentPointerArg = 0, argi = 0;

    for (auto argItr = f->arg_begin(); argItr != f->arg_end(); argItr++, argi++)
        if (argItr->getType()->isPointerTy())
        {

            if (currentPointerArg < numberOfPointerArguments)
            {

                StringRef fArgName = formalArgumentNames.at(currentPointerArg);
                currentPointerArg++;
                Indirection *ind = new Indirection(1, true, SINGLE);
                GPUNode *left = new TmpNode(fArgName, f->getName(), ind, argItr->getType());

                Value *argument = cs.getArgument(argi);

                if (GlobalVariable *gv = dyn_cast<GlobalVariable>(argument))
                {

                    Indirection *gil = new Indirection(0, true, SINGLE);
                    GPUNode *gNode = new GlobalNode(gv, gil);
                    GPU *gpu = new GPU(left, gNode, lineNo, fileName);
                    gpuSet.insert(gpu);
                }
                else if (tempToVariableSet.count(argument->getName()) == 1)
                {

                    vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(argument->getName());

                    FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes)
                    {

                        if (isa<TmpNode>(listOfNodes[i]))
                        {
                            GPU *gpu = new GPU(left, listOfNodes[i], lineNo, fileName);
                            gpuSet.insert(gpu);
                        }
                        else if (isa<GlobalNode>(listOfNodes[i]))
                        {
                            GPU *gpu = new GPU(left, listOfNodes[i], lineNo, fileName);
                            gpuSet.insert(gpu);
                        }
                        else if (isa<AllocationSiteNode>(listOfNodes[i]))
                        {

                            Indirection *rList = listOfNodes[i]->getIndirectList();

                            Indirection *rOprList;

                            if (isa<IndirectionList>(rList))
                            {

                                IndirectionList *ctList = (IndirectionList *)rList;
                                rOprList = new IndirectionList(1, true, ctList->getNumberOfFields(), ctList->getFieldList());
                                GPUNode *left = new TmpNode(fArgName, f->getName(), rOprList, argItr->getType());
                                GPU *gpu = new GPU(left, listOfNodes[i], lineNo, fileName);
                                gpuSet.insert(gpu);
                            }
                        }
                    }
                }
            }
        }

    gpb = new GPB(gpuSet);
    return gpb;
}

void FunctionWithGPG::inlineAtRecursiveBlock(GPG *optimized)
{

    set<long> rCallBlocks = summary->getRecursiveCallBlocks();

    map<long, GPB *> GPBsMap = optimized->getGPBMap();

    set<GPB *, GPBComp> GPBSet = optimized->getGPBSet();

    set<GPB *, GPBComp>::iterator itrSet, itrSuccSet, itrPredSet;

    for (auto rItr = rCallBlocks.begin(); rItr != rCallBlocks.end(); rItr++)
    {

        map<long, GPB *> gpbs = summary->getGPBMap();

        /*outs()<<"..................eeeee\n";

        for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++) {

            outs()<<(*bItr).first<<" ";
          }*/

        /* get successors and predecessors of recursive block */

        if (gpbs.find(*rItr) != gpbs.end())
        {

            set<GPB *, GPBComp> succRecBlock = gpbs[*rItr]->getAllSuccessors();
            set<GPB *, GPBComp> predRecBlock = gpbs[*rItr]->getAllPredecessors();

            map<long, long> oldToNew;

            map<long, GPB *> newGPBMap;

            FOR_EACH_ELEMENT_WITHITR(GPBSet, itrSet)
            {

                GPB *newGPB = new GPB();
                set<GPU *, GPUComp> newGPUSet = (*itrSet)->getGPUSet();
                set<GPU *, GPUComp> inlineGPUSet = newGPUSet;

                newGPB->setGPUSet(inlineGPUSet);

                set<GPUNode *, GPUNodeComp> mayDefs = (*itrSet)->getMayDefSet();

                newGPB->setMayDefSet(mayDefs);

                oldToNew[(*itrSet)->getGPBNo()] = newGPB->getGPBNo();
                newGPBMap[newGPB->getGPBNo()] = newGPB;
                summary->insertGPB(newGPB);
            }

            FOR_EACH_ELEMENT_WITHITR(GPBSet, itrSet)
            {

                set<GPB *, GPBComp> succSet = (*itrSet)->getAllSuccessors();

                long newGPBNo = oldToNew[(*itrSet)->getGPBNo()];

                FOR_EACH_ELEMENT_WITHITR(succSet, itrSuccSet)
                {

                    long succGPBNo = oldToNew[(*itrSuccSet)->getGPBNo()];
                    summary->addSuccessortoBB(newGPBNo, newGPBMap[succGPBNo]);
                }

                set<GPB *, GPBComp> predSet = (*itrSet)->getAllPredecessors();

                FOR_EACH_ELEMENT_WITHITR(predSet, itrPredSet)
                {

                    long predGPBNo = oldToNew[(*itrPredSet)->getGPBNo()];
                    // outs()<<"Pred:  "<<predGPBNo;
                    summary->addPredecessortoBB(newGPBNo, newGPBMap[predGPBNo]);
                }
            }

            GPB *optimizedStartNode = optimized->getEntryNode();

            GPB *firstAtRec = newGPBMap[oldToNew[optimizedStartNode->getGPBNo()]];

            for (auto pItr = predRecBlock.begin(); pItr != predRecBlock.end(); pItr++)
            {

                summary->addSuccessortoBB((*pItr)->getGPBNo(), firstAtRec);
                summary->addPredecessortoBB(firstAtRec->getGPBNo(), (*pItr));
                summary->removeSuccessorOfBB((*pItr)->getGPBNo(), gpbs[*rItr]);
                summary->removePredecessorOfBB(*rItr, gpbs[(*pItr)->getGPBNo()]);
            }

            GPB *optimizedEndNode = optimized->getExitNode();

            GPB *endAtRec = newGPBMap[oldToNew[optimizedEndNode->getGPBNo()]];

            for (auto sItr = succRecBlock.begin(); sItr != succRecBlock.end(); sItr++)
            {

                summary->addPredecessortoBB((*sItr)->getGPBNo(), endAtRec);
                summary->addSuccessortoBB(endAtRec->getGPBNo(), (*sItr));
                summary->removePredecessorOfBB((*sItr)->getGPBNo(), gpbs[*rItr]);
                summary->removeSuccessorOfBB(*rItr, gpbs[(*sItr)->getGPBNo()]);
            }

            // outs()<<" removing  "<<*rItr;
            summary->removeGPB(gpbs[*rItr]);
        }
    }
}

void FunctionWithGPG::findCallers()
{
    for(Function& F : *m)
    {
        for(BasicBlock& BB : F)
        {
            for(Instruction& I : BB)
            {
                if(isa<CallInst>(&I))
                {
                    if(dyn_cast<CallInst>(&I)->getCalledFunction() == fun)
                    {
                        Callers.insert(&F);
                    }
                }
            }
        }
    }
}

void FunctionWithGPG::inliningCallsInSCC(map<StringRef, FunctionWithGPG*>& functionToGPG)
{    
    GPG* inline_summary_direct_recursion = new GPG();
    inline_summary_direct_recursion->DeepCopy(summary);
    delete summary; 

    // initial_summary_with_rec_calls->printToDot("test_"+fun->getName().str()+".dot");
    summary = new GPG();    
    summary->DeepCopy(initial_summary_with_rec_calls);
    map<long, GPB*> gpbs = summary->getGPBMap();           

    map<long, GPB *> newGPBMap;
    set<GPB *, GPBComp> newGPBset;
    vector<GPB*> GPBsToRemove;    

    for(auto it = gpbs.begin(); it != gpbs.end(); it++)
    {
        if((*it).second->isItRecursiveCallBlock())
        {
            set<GPU*, GPUComp> gpus = (*it).second->getGPUSet();            
            GPG* calleGPG = nullptr;            
            for(auto gpu = gpus.begin(); gpu != gpus.end(); gpu++)
            {
                if((*gpu)->getStmtNo() == -11) // Direct Recursion
                {
                    calleGPG = inline_summary_direct_recursion;
                }
                else if((*gpu)->getStmtNo() == -12) // InDirect Recursion
                {                
                    if(functionToGPG.find((*gpu)->getFileName()) != functionToGPG.end())                   
                        calleGPG = functionToGPG[(*gpu)->getFileName()]->getSummary();
                }
            }
            if(calleGPG == nullptr) continue;
                    
            // Inilining summary of callee            
            GPB *entry = new GPB(); // dummy entry to connect callee's GPGs start node.
            newGPBset.insert(entry);
            newGPBMap[entry->getGPBNo()] = entry;
            GPB *exit = new GPB(); // dummy exit to connect callee's GPGs end node.
            newGPBset.insert(exit);
            newGPBMap[exit->getGPBNo()] = exit;           
        
            map<long, GPB *> GPBsMap = calleGPG->getGPBMap();
            set<GPB *, GPBComp> GPBSet = calleGPG->getGPBSet();

            map<long, long> oldToNew;            

            for (auto gpb = GPBSet.begin(); gpb != GPBSet.end(); gpb++)
            {
                GPB *newGPB = new GPB();
                newGPB->setGPUSet((*gpb)->getGPUSet());
                newGPB->setMayDefSet((*gpb)->getMayDefSet());
                oldToNew[(*gpb)->getGPBNo()] = newGPB->getGPBNo();
                newGPBset.insert(newGPB);  
                newGPB->setisInlined(1);                              
                newGPBMap[newGPB->getGPBNo()] = newGPB;
            }

            GPB *startNode = newGPBMap[oldToNew[calleGPG->getEntryNode()->getGPBNo()]];
            startNode->addPredecessor(entry);
            entry->addSuccessor(startNode);
            summary->addEdge(entry->getGPBNo(), startNode->getGPBNo());

            GPB *endNode = newGPBMap[oldToNew[calleGPG->getExitNode()->getGPBNo()]];
            endNode->addSuccessor(exit);
            exit->addPredecessor(endNode);
            summary->addEdge(endNode->getGPBNo(), exit->getGPBNo());

            for (auto gpb = GPBSet.begin(); gpb != GPBSet.end(); gpb++)
            {
                // Iterate over all succSet
                set<GPB *, GPBComp> succs = (*gpb)->getAllSuccessors();
                for (auto succ = succs.begin(); succ != succs.end(); succ++)
                {
                    newGPBMap[oldToNew[(*gpb)->getGPBNo()]]->addSuccessor(newGPBMap[oldToNew[(*succ)->getGPBNo()]]);
                    newGPBMap[oldToNew[(*succ)->getGPBNo()]]->addPredecessor(newGPBMap[oldToNew[(*gpb)->getGPBNo()]]);
                    summary->addEdge(oldToNew[(*gpb)->getGPBNo()], oldToNew[(*succ)->getGPBNo()]);
                }
                // Iterate over all preds
                set<GPB *, GPBComp> preds = (*gpb)->getAllPredecessors();
                for (auto pred = preds.begin(); pred != preds.end(); pred++)
                {
                    newGPBMap[oldToNew[(*gpb)->getGPBNo()]]->addPredecessor(newGPBMap[oldToNew[(*pred)->getGPBNo()]]);
                    newGPBMap[oldToNew[(*pred)->getGPBNo()]]->addSuccessor(newGPBMap[oldToNew[(*gpb)->getGPBNo()]]);
                    summary->addEdge(oldToNew[(*pred)->getGPBNo()], oldToNew[(*gpb)->getGPBNo()]);
                }
            }
            set<GPB *, GPBComp> preds = (*it).second->getAllPredecessors();
            set<GPB *, GPBComp> succs = (*it).second->getAllSuccessors();
            bool has_self_loop = 0;
            for (auto pred = preds.begin(); pred != preds.end(); pred++)
            {
                if(*pred == (*it).second)
                {
                    has_self_loop = 1;
                    continue;
                }
                entry->addPredecessor(*pred);
                (*pred)->addSuccessor(entry);
                summary->addEdge((*pred)->getGPBNo(), entry->getGPBNo());
                (*pred)->removeSuccessor((*it).second);
                summary->removeEdge((*pred)->getGPBNo(), (*it).second->getGPBNo());
            }
            (*it).second->removeAllPredecessors();
            for (auto succ = succs.begin(); succ != succs.end(); succ++)
            {
                if(*succ == (*it).second)
                {
                    has_self_loop = 1;
                    continue;
                }
                exit->addSuccessor(*succ);
                (*succ)->addPredecessor(exit);
                summary->addEdge(exit->getGPBNo(), (*succ)->getGPBNo());
                (*succ)->removePredecessor((*it).second);
                summary->removeEdge((*it).second->getGPBNo(), (*succ)->getGPBNo());
            }
            if(has_self_loop)
            {
                exit->addSuccessor(entry);
                entry->addPredecessor(exit);
                summary->addEdge(exit->getGPBNo(), entry->getGPBNo());                
            }
            (*it).second->removeAllSuccessors();
            GPBsToRemove.push_back((*it).second);
        }
        else
        {
            newGPBMap.insert((*it));
            newGPBset.insert((*it).second);
        }
    }    
    for (auto it : GPBsToRemove)
    {
        summary->removeGPB(it);            
    }
    summary->setGPBMap(newGPBMap);
    summary->setGPBSet(newGPBset);        
    // summary->printToDot("test_inlining.dot");

}
void FunctionWithGPG::removeUnreachableNodes()
{
    set<long> rStart = summary->ReachableNodesFromStratInRecursiveFunctions();
    set<long> rExit = summary->ReachableNodesToEndInRecursiveFunctions();

    set<long> rStartAndExit;

    for (auto rItr = rStart.begin(); rItr != rStart.end(); rItr++)
        if (rExit.find(*rItr) != rExit.end())
            rStartAndExit.insert(*rItr);
    

    map<long, GPB *> gpbs = summary->getGPBMap();
    // for(auto it : rStartAndExit)
    // {
    //     outs() << "-------------------\n";
    //     gpbs[it]->print();   
    //     outs() << "\n-------------------\n";
    // }

    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        if (rStartAndExit.find((*bItr).first) == rStartAndExit.end())
        {
            GPB *curBlock = gpbs[(*bItr).first];

            summary->removeAllSuccessorsOfBB(curBlock->getGPBNo());
            summary->removeAllPredecessorsOfBB(curBlock->getGPBNo());
        }
        else
        {

            GPB *curBlock = gpbs[(*bItr).first];

            set<GPB *, GPBComp> succSet = curBlock->getAllSuccessors();

            for (auto sItr = succSet.begin(); sItr != succSet.end(); sItr++)
                if (rStartAndExit.find((*sItr)->getGPBNo()) == rStartAndExit.end())
                {
                    summary->removeSuccessorOfBB(curBlock->getGPBNo(), gpbs[(*sItr)->getGPBNo()]);
                    summary->removePredecessorOfBB((*sItr)->getGPBNo(), curBlock);
                }

            set<GPB *, GPBComp> predSet = curBlock->getAllPredecessors();

            for (auto pItr = predSet.begin(); pItr != predSet.end(); pItr++)
                if (rStartAndExit.find((*pItr)->getGPBNo()) == rStartAndExit.end())
                {
                    summary->removePredecessorOfBB(curBlock->getGPBNo(), gpbs[(*pItr)->getGPBNo()]);
                    summary->removeSuccessorOfBB((*pItr)->getGPBNo(), curBlock);
                }
        }
    }

    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        if (rStartAndExit.find((*bItr).first) == rStartAndExit.end())
        {
            summary->removeGPB(gpbs[(*bItr).first]);            
        }
    }  
    if(rStartAndExit.size() == 0)
    {
        GPG* gpg = new GPG();
        GPB* entry = new GPB();
        GPB* d_top = new GPB();
        GPB* exit = new GPB();
        set<GPB*, GPBComp> newGPBset;
        map<long, GPB*> newGPBMap;
        newGPBset.insert(entry);
        newGPBset.insert(d_top);        
        newGPBset.insert(exit);
        newGPBMap[entry->getGPBNo()] = entry;
        newGPBMap[d_top->getGPBNo()] = d_top;
        newGPBMap[exit->getGPBNo()] = exit;        
        entry->addSuccessor(d_top);
        d_top->addSuccessor(exit);        
        summary->addEdge(entry->getGPBNo(), d_top->getGPBNo());
        summary->addEdge(d_top->getGPBNo(), exit->getGPBNo());
        d_top->addPredecessor(entry);
        exit->addPredecessor(d_top);        
        summary->setEntryNode(entry);
        summary->setExitNode(exit);
        summary->setGPBMap(newGPBMap);
        summary->setGPBSet(newGPBset);
    }
}
set<Function*> FunctionWithGPG::getCallers()
{
    return Callers;
}
void FunctionWithGPG::handleRecursion(int itrNo, bool with_updated_coalescing)
{
    outs() << "Iteration " << itrNo << ": " << fun->getName() << "\n";    
    removeEmptyNodesInGPG();
std::string dotFileName;

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 6        
        dotFileName = fun->getName().str() + "_Iteration" + std::to_string(itrNo) + "_gpgAfterEmpty.dot";
        summary->printToDot(dotFileName);
#endif
#endif

    reachingGPUAnalysisWithOutBlocking();
    reachingGPUAnalysisWithBlocking();


#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 6        
        dotFileName = fun->getName().str() + "_Iteration" + std::to_string(itrNo) + "_gpgAfterStrengthReduction.dot";
        summary->printToDot(dotFileName);
#endif
#endif

    deadGPUElimination();

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 6        
        dotFileName = fun->getName().str() + "_Iteration" + std::to_string(itrNo) + "_gpgAfterDeadGPUElimination.dot";
        summary->printToDot(dotFileName);
#endif
#endif
    removeUnreachableNodes();
#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 6        
        dotFileName = fun->getName().str() + "_Iteration" + std::to_string(itrNo) + "_gpgAfterRemovingUnreachableNodes.dot";
        summary->printToDot(dotFileName);
#endif
#endif

    if(with_updated_coalescing)
    {
        UpdatedCoalescingAnalysis();
#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 6         
        dotFileName = fun->getName().str() + "_Iteration" + std::to_string(itrNo) + "_gpgAfterUpdatedCoalescing.dot";
        summary->printToDot(dotFileName);
#endif
#endif
    }
    else
    {
        coalescingAnalysisInThesis();  
#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 6         
        dotFileName = fun->getName().str() + "_Iteration" + std::to_string(itrNo) + "_gpgAfterCoalescing.dot";
        summary->printToDot(dotFileName);
#endif
#endif
    }
}
void FunctionWithGPG::setInitialSummary()
{
    initial_summary_with_rec_calls = new GPG();
    initial_summary_with_rec_calls->DeepCopy(summary);
}

void FunctionWithGPG::handleDirectRecursion()
{

    GPG *initialSummary, *optimizedSummary;
    Util util;

    initialSummary = new GPG();
    initialSummary->DeepCopy(summary);

    reachingGPUAnalysisWithOutBlocking();
    reachingGPUAnalysisWithBlocking();
    deadGPUElimination();

    set<long> rStart = summary->ReachableNodesFromStratInRecursiveFunctions();
    set<long> rExit = summary->ReachableNodesToEndInRecursiveFunctions();

    set<long> rStartAndExit;

    for (auto rItr = rStart.begin(); rItr != rStart.end(); rItr++)
        if (rExit.find(*rItr) != rExit.end())
            rStartAndExit.insert(*rItr);

    map<long, GPB *> gpbs = summary->getGPBMap();

    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        if (rStartAndExit.find((*bItr).first) == rStartAndExit.end())
        {

            GPB *curBlock = gpbs[(*bItr).first];

            summary->removeAllSuccessorsOfBB(curBlock->getGPBNo());
            summary->removeAllPredecessorsOfBB(curBlock->getGPBNo());
        }
        else
        {

            GPB *curBlock = gpbs[(*bItr).first];

            set<GPB *, GPBComp> succSet = curBlock->getAllSuccessors();

            for (auto sItr = succSet.begin(); sItr != succSet.end(); sItr++)
                if (rStartAndExit.find((*sItr)->getGPBNo()) == rStartAndExit.end())
                {
                    summary->removeSuccessorOfBB(curBlock->getGPBNo(), gpbs[(*sItr)->getGPBNo()]);
                    summary->removePredecessorOfBB((*sItr)->getGPBNo(), curBlock);
                }

            set<GPB *, GPBComp> predSet = curBlock->getAllPredecessors();

            for (auto pItr = predSet.begin(); pItr != predSet.end(); pItr++)
                if (rStartAndExit.find((*pItr)->getGPBNo()) == rStartAndExit.end())
                {
                    summary->removePredecessorOfBB(curBlock->getGPBNo(), gpbs[(*pItr)->getGPBNo()]);
                    summary->removeSuccessorOfBB((*pItr)->getGPBNo(), curBlock);
                }
        }
    }

    for (auto bItr = gpbs.begin(); bItr != gpbs.end(); bItr++)
    {
        if (rStartAndExit.find((*bItr).first) == rStartAndExit.end())
        {
            summary->removeGPB(gpbs[(*bItr).first]);
        }
    }

    //util.print(rStartAndExit);

    // initialSummaryWithCallBlock->print();
    // initialSummary->print();
    //summary->print();
    removeEmptyNodesInGPG();
    coalescingAnalysisInThesis();
    optimizedSummary = summary;

    set<GPU *, GPUComp> currRGWOB = getRGOutOfEnd(false);

    set<GPU *, GPUComp> currRGWB = getRGOutOfEnd(true);

    //util.print(currRGWOB);

    //outs()<<"                    ..............\n";
    set<GPU *, GPUComp> prevRGWOB, prevRGWB;

    //summary->print();

    int itrNo = 1;
    do
    {

        prevRGWOB = currRGWOB;
        prevRGWB = currRGWB;
        outs() << "Recursion Iteration:" << itrNo << "\n";

        summary = new GPG();

        summary->DeepCopy(initialSummary);

        map<long, GPB *> gpbs = summary->getGPBMap();

        inlineAtRecursiveBlock(optimizedSummary);

        //summary->print();

        string funName;
        string dotFileName;

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 6
        funName = fun->getName();
        dotFileName = funName + std::to_string(itrNo) + "gpg.dot";
        summary->printToDot(dotFileName);
#endif
#endif

        removeEmptyNodesInGPG();
        reachingGPUAnalysisWithOutBlocking();
        reachingGPUAnalysisWithBlocking();

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 6
        funName = fun->getName();
        dotFileName = funName + std::to_string(itrNo) + "AfterStrengthReductiongpg.dot";
        summary->printToDot(dotFileName);
#endif
#endif

        deadGPUElimination();

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 6
        funName = fun->getName();
        dotFileName = funName + std::to_string(itrNo) + "gpgAfterDeadGPUElimination.dot";
        summary->printToDot(dotFileName);
#endif
#endif

        coalescingAnalysisInThesis();

#ifdef VERBOSE_LEVEL
#if VERBOSE_LEVEL == 6
        funName = fun->getName();
        dotFileName = funName + std::to_string(itrNo) + "gpgAfterCoalescing.dot";
        summary->printToDot(dotFileName);
#endif
#endif

        optimizedSummary = summary;

        currRGWOB = getRGOutOfEnd(false);
        currRGWB = getRGOutOfEnd(true);

        // util.print(currRGWOB);
        // util.print(currRGWB);

        itrNo++;

        /*outs()<<"....................................eeee\n\n";
        util.print(prevRGWOB);
        util.print(prevRGWB);*/

    } while (util.isEqualOrNot(prevRGWOB, currRGWOB) == false || util.isEqualOrNot(prevRGWB, currRGWB) == false);
}

void FunctionWithGPG::processCallReturn(Instruction &I, set<GPUNode *, GPUNodeComp> returnNodesOfCalle)
{

    for (auto rItr = returnNodesOfCalle.begin(); rItr != returnNodesOfCalle.end(); rItr++)
        addVariableToTempMap(I.getName(), *rItr);
}

set<GPUNode *, GPUNodeComp> FunctionWithGPG::getReturnNodes()
{

    return returnNodes;
}

GPB *FunctionWithGPG::processAllocaInstruction(Instruction &I) {
    long lineNo = 0;
    StringRef fileName = I.getFunction()->getName();
    Util util;


    if (I.hasMetadata())
    {
        MDNode *node = I.getMetadata("dbg");
        if (DILocation *loc = dyn_cast<DILocation>(node))
        {
            lineNo = loc->getLine();
            fileName = loc->getFilename();
        }
    }
    else
        util.debugInfoErrorMsg(I);

    set<GPU*, GPUComp> gpuSet;
    StringRef tempName = I.getName();

    GPUNode *leftNode = new TmpNode(tempName, fileName, new Indirection(1, true, SINGLE),
                                     I.getType());

    GPUNode *rightNode = new AllocationSiteNode(tempName.str()  + "@allocasite@", lineNo, fileName,
                                                new Indirection(0, true, SINGLE));

    GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
    gpuSet.insert(gpu);
    GPB *gpBlock = new GPB(gpuSet);
    //gpBlock->print();
    return gpBlock;


}

GPB *FunctionWithGPG::processPointerLoadInstruction(Instruction &I) {
    long lineNo;
    StringRef fileName;
    Util util;

    if (I.hasMetadata())
    {
        MDNode *node = I.getMetadata("dbg");
        if (DILocation *loc = dyn_cast<DILocation>(node))
        {
            lineNo = loc->getLine();
            fileName = loc->getFilename();
        }
    }
    else
        util.debugInfoErrorMsg(I);

    set<GPU*, GPUComp> gpuSet;
    StringRef assignedVariable = I.getName();
    Value *sourceOpr = I.getOperand(0);
    //if(dyn_cast<Argument>(sourceOpr)){
        GPUNode *rightNode =
                new TmpNode(sourceOpr->getName(), I.getFunction()->getName(),
                            new Indirection(2, true, SINGLE), sourceOpr->getType());
        GPUNode *leftNode = new TmpNode(assignedVariable,
                                        I.getFunction()->getName(),
                                        new Indirection(1, true, SINGLE), I.getType());
        GPU *gpu = new GPU(leftNode, rightNode, lineNo, fileName);
        gpuSet.insert(gpu);

        return new GPB(gpuSet);
   // }
    //vector<GPUNode *> listOfNodes = getListOfNodesMappedToTemp(assignedVariable);
    //FOR_EACH_ELEMENT_OF_VECTOR(listOfNodes){

    //}
    //return nullptr;

}

GPB* FunctionWithGPG::generateGPBforDebugDeclareInstruction(DbgDeclareInst &dbgDeclare) {
    if(Value *v = dbgDeclare.getAddress()){
        if(v->hasName()){
            StringRef name = dbgDeclare.getVariable()->getName();
            StringRef file = dbgDeclare.getVariable()->getFile()->getName();
            GPUNode *leftNode = new TmpNode(v->getName(), file, new Indirection(1, true, SINGLE), v->getType());
            GPUNode *rightNode = new TmpNode(name, file, new Indirection(0, true, SINGLE), dbgDeclare.getType());
            GPU* gpu = new GPU(leftNode, rightNode, dbgDeclare.getDebugLoc().getLine(),
                               dbgDeclare.getDebugLoc()->getFilename());
            GPB *gpBlock = new GPB(gpu);
            //gpBlock->print();
            return gpBlock;
        }
    }

    return nullptr;
}

GPB *FunctionWithGPG::generateGPBforDebugValueInstruction(DbgValueInst &dbgValue) {
    if (Value *v = dbgValue.getValue()) {
        if (v->getType()->isPointerTy()) {
            StringRef name = dbgValue.getVariable()->getName();
            StringRef fileName = dbgValue.getVariable()->getFile()->getName();
            if (Argument *argument = dyn_cast<Argument>(v)){
                // this variable and the argument have the same value. (even better to say they are the same variable)
                GPUNode *leftNode = new TmpNode(argument->getName(), fileName, new Indirection(1, true, SINGLE), v->getType());
                GPUNode *rightNode = new TmpNode(name, fileName, new Indirection(1, true, SINGLE), v->getType());
                GPU* gpu = new GPU(leftNode, rightNode, 0, fileName);
                GPB *gpBlock = new GPB(gpu);
                //gpBlock->print();
                return gpBlock;
            }else if (GlobalVariable *globalVariable = dyn_cast<GlobalVariable>(v)){
                // this variable and the argument have the same value. (even better to say they are the same variable)
                GPUNode *leftNode = new TmpNode(globalVariable->getName(), fileName, new Indirection(1, true, SINGLE), v->getType());
                GPUNode *rightNode = new TmpNode(name, fileName, new Indirection(0, true, SINGLE), v->getType());
                GPU* gpu = new GPU(leftNode, rightNode, 0, fileName);
                GPB *gpBlock = new GPB(gpu);
                //gpBlock->print();
                return gpBlock;
            }
        }
    }
            //preProcessDebugValueInstruction(dbgValue)
    return nullptr;
}

GPB *FunctionWithGPG::processPointerPhiInstruction(PHINode &node) {
    if (!node.getOperand(0)->getType()->isPointerTy()) {
        return nullptr;
    }

    set<GPU*, GPUComp> gpuSet;

    for (unsigned i = 0; i < node.getNumIncomingValues(); i++){
        if (Value *v = node.getIncomingValue(i))
        {
            GPUNode *leftNode = new TmpNode(node.getName(), "", new Indirection(1, true, SINGLE), node.getType());
            GPUNode *rightNode = new TmpNode(v->getName(), "", new Indirection(1, true, SINGLE), v->getType());
            GPU* gpu = new GPU(leftNode, rightNode, 0, "");
            gpuSet.insert(gpu);
        }
    }
    GPB *gpBlock = new GPB(gpuSet);
    //gpBlock->print();
    return gpBlock;

}

