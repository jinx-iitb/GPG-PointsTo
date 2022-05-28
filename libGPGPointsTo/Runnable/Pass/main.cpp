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
#include "GPGPTAnalysis/Driver.h"
/*#include "PointsToDump/FS_PTWriter.h"
#include "PointsToDump/PTWriter.h"
#include "PointsToDump/PTReader.h"
#include "PointsToDump/FS_PTReader.h"
#include "PTEval/EvaluateAnalysis.h"
*/
const std::string white("\033[1;97m");


#define FOR_EACH_FUNCTION(module) for (auto &F : *module)
#define FOR_EACH_BASICBLOCK(function) for (auto &BB : function)

using namespace llvm;
using namespace std;

void printSCCOrder(CallGraphNode *rootNode);

int checkCount(set<GPU*, GPUComp>& RGOut, Value* Pointer)
{
    set<std::pair<std::string, std::string>> VisitedPts;
    int count = 0;
    for(auto i2 : RGOut)
    {
        Value *Pt, *Pointee;
        if((i2->getTargetOfGPU()->getIndirectList()->getIndirectionLevel() != 0 || i2->getSourceOfGPU()->getIndirectList()->getIndirectionLevel() != 1) && !(i2->getSourceOfGPU()->getIndirectList()->getIndirectionLevel() == 1 && i2->getTargetOfGPU()->getIndirectList()->getIndirectionLevel() == 1 && i2->getStmtNo() == 0)) continue;
        if(i2->getSourceOfGPU()->getIndirectList()->getIndirectionLevel() == 1 && i2->getTargetOfGPU()->getIndirectList()->getIndirectionLevel() == 1 && i2->getStmtNo() == 0)
        {
            if(Pointer->getName().str() == i2->getSourceOfGPU()->getNameOfVariable().str() && VisitedPts.find({Pointer->getName().str() , i2->getTargetOfGPU()->getNameOfVariable().str()}) == VisitedPts.end())
                count++;
            VisitedPts.insert({Pointer->getName().str() , i2->getTargetOfGPU()->getNameOfVariable().str()});
        }
        else
        {
            GPUNode* left = i2->getSourceOfGPU();
            GPUNode* right = i2->getTargetOfGPU();
            if(isa<GlobalNode>(left))
            {
                GlobalNode* leftSource = dyn_cast<GlobalNode>(left);
                Pt =  dyn_cast<Value>(leftSource->getGlobalVariable());
            }
            if(isa<GlobalNode>(right))
            {
                Pointee = dyn_cast<Value>(dyn_cast<GlobalNode>(right)->getGlobalVariable());
            }
            if(!Pointee || !Pt)
            {
                outs() << left->getNameOfVariable() << ", " << right->getNameOfVariable() << "\n";
                continue;
            }
            else
            {
                if(Pointer == Pt && VisitedPts.find({Pt->getName().str() ,Pointee->getName().str()}) == VisitedPts.end())
                    count++;
                VisitedPts.insert({Pt->getName().str() ,Pointee->getName().str()});
            }
        }
    }
    // outs() << count << "\n";
    return count;
}

int main(int argc, char *argv[])
{
    //cout<<"Please enter ll file name : ";
    remove("dump.txt");
    char *str1 = "GPG";
    char *str2 = "../../GPG_Impl/TestCases/output23.ll";
    //char *str2 = "../../GPG_Impl/TestCases/lbm.0.4.opt.ll";
    //char *str2 = "bzip2.0.4.opt.ll";
    //char *str2 = "h264ref.0.4.opt.ll";
    //char *str2 = "lbm.0.4.opt.ll";
    char *args[2];
    args[0] = str1;
    args[1] = "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases/output.ll";
    argc = 2;
    auto start_time = chrono::steady_clock::now();
    Driver* exec = new Driver(argc, args);
    exec->performAnalysis();
    auto end_time = chrono::steady_clock::now();
    auto total_time = end_time - start_time;
#ifdef PRINT_STATS
#if PRINT_STATS == 1
    std::cout << yellow << "\nTotal time taken for complete Construction: " << std::fixed << std::setprecision(2) << chrono::duration <double, milli> (total_time).count()  << " ms" << reset << "\n";
    std::cout << "\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n";
#endif
#endif

    /*
    int idx;
    std::cout << "\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
    std::cout << "\n\nEnter the testcase Number for which Analysis must be tested:\t ";
    std::cin >> idx;
    std::cout << "\n";
    PTDump::FS_PTWriter* pt = new PTDump::FS_PTWriter(PTDump::AnalysisType::FlowSensitive, "user"+std::to_string(idx));
    Value *Pointer, *Pointee;
    Value* curPointer, *curPointee, *prevPointer, *prevPointee;
    auto functionToGPG = exec->getfunctionWithGPGMap();
    llvm::Module* module = exec->getModule();
    map<Value*, set<Value*>> CountGPUs;

    for(auto it : functionToGPG)
    {
        if(!it.second) continue;
        llvm::Function* fun =  it.second->getFunction();
        map<long, GPB*> GPBMap = it.second->getSummaryAfterStrengthReduction()->getGPBMap();
        for(auto i : GPBMap)
        {
            auto s = i.second->getRGBlockingOut();
            std::string fname;
            int LineNumber;
            for(auto gpu : i.second->getGPUSet()) { if(gpu) { fname = gpu->getFileName().str(); LineNumber = gpu->getStmtNo(); } }
            if(fname == "") continue;
            for(auto i2 : s)
            {
                if(!i2) continue;
                if(i2->getTargetOfGPU()->getIndirectList()->getIndirectionLevel() != 0 || i2->getSourceOfGPU()->getIndirectList()->getIndirectionLevel() != 1) continue;
                GPUNode* left = i2->getSourceOfGPU();
                GPUNode* right = i2->getTargetOfGPU();
                if(isa<GlobalNode>(left))
                {
                    GlobalNode* leftSource = dyn_cast<GlobalNode>(left);
                    Pointer =  dyn_cast<Value>(leftSource->getGlobalVariable());
                }
                if(isa<GlobalNode>(right))
                {
                    Pointee = dyn_cast<Value>(dyn_cast<GlobalNode>(right)->getGlobalVariable());
                }
                if(!Pointee || !Pointer)
                {
                    outs() << "*******************************************************\n";
                    outs() << left->getNameOfVariable() << ", " << right->getNameOfVariable() << ", " << LineNumber << "\n";
                    std::string pointerTy, pointeeTy;
                    llvm::raw_string_ostream rso1(pointerTy);
                    llvm::raw_string_ostream rso2(pointeeTy);
                    isa<GlobalNode>(left) ? left->getTypeofVariable()->getPointerElementType()->print(rso1) : left->getTypeofVariable()->print(rso1);
                    isa<GlobalNode>(right) ? right->getTypeofVariable()->getPointerElementType()->print(rso2) : right->getTypeofVariable()->print(rso2);
                    if(checkCount(s, Pointer) > 1)
                        pt->WritePointsToinfoAt(fun, LineNumber, fname, left->getNameOfVariable().str(), right->getNameOfVariable().str(), rso1.str(),rso2.str(), PTDump::MayPointee);
                    else
                        pt->WritePointsToinfoAt(fun, LineNumber, fname, left->getNameOfVariable().str(), right->getNameOfVariable().str(), rso1.str(),rso2.str(), PTDump::MustPointee);
                }
                else
                {
                    prevPointer = curPointer;
                    prevPointee = curPointee;
                    curPointer = Pointer;
                    curPointee = Pointee;
                    // if(LineNumber == 59) outs() << Pointer->getName() << ", " << Pointee->getName() << "\t";
                    if(checkCount(s, Pointer) > 1)
                        pt->WritePointsToinfoAt(fun, LineNumber, fname, Pointer ,Pointee, PTDump::MayPointee);
                    else
                        pt->WritePointsToinfoAt(fun, LineNumber, fname, Pointer ,Pointee, PTDump::MustPointee);
                }
            }
        }
    }
    delete pt;
    if(idx == 1)
    {
        PTDump::FS_PTReader* pr = new PTDump::FS_PTReader("user"+to_string(idx));
        std::cout<< YELLOWT <<"1. Printing Information to a .dot file\n" << RST;
        pr->printToDot(7, module->getSourceFileName());

        std::cout << YELLOWT << "2. Printing Information from the dump to Result.log file\n" << RST;
        pr->printPointsToDump();

        std::cout<< YELLOWT << "\n\n3. Checking getMayPointsToPairsAt() and getMustPointsToPairsAt()\n" << RST;
        auto mayptPairs = pr->getMayPointsToPairsAt(82, module->getSourceFileName());
        std::cout << cyan << "\tMay Points To Pairs: " << RST << white << "{";
        for(auto i : mayptPairs)
        {
            if(i != *(mayptPairs.begin()))
                std::cout << ",  ";
            std::cout << "(" << i.first << ", " << i.second << ")";
        }
        std::cout << "}\n" << RST;
        auto mustptPairs = pr->getMustPointsToPairsAt(82, module->getSourceFileName());
        std::cout << cyan << "\tMust Points To Pairs:" << RST << white << "{" ;
        for(auto i : mustptPairs)
        {
            if(i != *(mustptPairs.begin()))
                std::cout << ",  ";
            std::cout << "(" << i.first << ", " << i.second << ")";
        }
        std::cout << "}\n\n" << RST;

        std::cout<< YELLOWT << "4. Checking isMayPointee() and isMustPointee()\n" << RST;
        bool res1 = pr->isMayPointee(82, module->getSourceFileName(), curPointer, curPointee);
        std::cout << "\t";
        if(res1) std::cout << white << curPointee->getName().str() << RST << GREENT << " is a Must Pointee of " << RST << white << curPointer->getName().str() << RST << "\n";
        else std::cout << white << curPointee->getName().str() << RST <<  REDT << " is not a Must Pointee of " << RST << white << curPointer->getName().str() << RST << "\n";

        std::cout << "\t";
        res1 = pr->isMustPointee(82, module->getSourceFileName(), curPointer, curPointee);
        if(res1) std::cout << white << curPointee->getName().str() << RST <<  GREENT << " is a Must Pointee of " << RST << white <<  curPointer->getName().str() << RST << "\n";
        else std::cout << white << curPointee->getName().str() << RST << REDT << " is not a Must Pointee of " << RST << white << curPointer->getName().str() << "\n";

        std::cout << "\t";
        res1 = pr->isMayPointee(82, module->getSourceFileName(), prevPointer, prevPointee);
        if(res1) std::cout << white << prevPointee->getName().str() << RST <<  GREENT << " is a Must Pointee of " << RST << white <<  prevPointer->getName().str() << RST << "\n";
        else std::cout << white << prevPointee->getName().str() << RST << REDT << " is not a Must Pointee of " << RST << white << prevPointer->getName().str() << RST << "\n";

        std::cout << "\t";
        res1 = pr->isMustPointee(82, module->getSourceFileName(), prevPointer, prevPointee);
        if(res1) std::cout << white << prevPointee->getName().str() << RST << GREENT << " is a Must Pointee of " << RST << white << prevPointer->getName().str() << RST << "\n";
        else std::cout << white << prevPointee->getName().str() << RST << REDT << " is not a Must Pointee of " << RST << white << prevPointer->getName().str() << RST << "\n";

        std::cout<< YELLOWT << "\n5. Checking getPointeesOf()\n" << RST;
        auto pointeeset = pr->getPointeesOf(82, module->getSourceFileName(), curPointer);
        std::cout << "\t" << cyan << "Pointees of " << curPointer->getName().str() << ":" << RST << white << " {";
        for(auto p : pointeeset) { if(p != *(pointeeset.begin())) std::cout << ", "; std::cout << p; }
        std::cout << "}\n" << RST;
        delete pr;

    }



    PointsToEval::EvaluateAnalysis* ev = new PointsToEval::EvaluateAnalysis("../../../PT-Test-suite/Test-suite/FSRef_pt_Files/", "./", idx);
    ev->PrintStats();
    delete ev;*/
    return 0;
}
// Testing the libPointsToDump
/*PTDump::FS_PTWriter* pt = new PTDump::FS_PTWriter(PTDump::AnalysisType::FlowSensitive, "GPGTest");
Value *Pointer, *Pointee;
for(auto it : functionToGPG)
{
    llvm::Function* fun =  it.second->getFunction();
    map<long, GPB*> GPBMap = it.second->getSummary()->getGPBMap();
    for(auto i : GPBMap)
    {
        for(auto i2 : i.second->getGPUSet())
        {
            if(i2->getTargetOfGPU()->getIndirectList()->getIndirectionLevel() != 0 || i2->getSourceOfGPU()->getIndirectList()->getIndirectionLevel() != 1) continue;
            std::string fname = i2->getFileName().str();
            int LineNumber = i2->getStmtNo();
            GPUNode* left = i2->getSourceOfGPU();
            GPUNode* right = i2->getTargetOfGPU();
            if(isa<GlobalNode>(left))
            {
                GlobalNode* leftSource = dyn_cast<GlobalNode>(left);
                Pointer =  dyn_cast<Value>(leftSource->getGlobalVariable());
            }
            if(isa<GlobalNode>(right))
            {
                Pointee = dyn_cast<Value>(dyn_cast<GlobalNode>(right)->getGlobalVariable());
            }
            if(!Pointee || !Pointer)
            {
                outs() << left->getNameOfVariable() << ", " << right->getNameOfVariable() << "\n";
                continue;
            }
            else
            {
                pt->WritePointsToinfoAt(fun, LineNumber, fname, Pointer ,Pointee, PTDump::MayPointee);
            }
        }
    }
}
delete pt;
PTDump::FS_PTReader* pr = new PTDump::FS_PTReader("GPGTest");
pr->printToDot(14, module->getSourceFileName());
*/