#include "Driver.h"

Driver::Driver(int count, char** options)
{
    with_updated_coalescing = false;
    process_cmd_options(count, options);    
}

void Driver::performAnalysis()
{
    llvm::SMDiagnostic diag;
    unique_ptr<llvm::LLVMContext> context(new llvm::LLVMContext);
    unique_ptr<llvm::Module> M = llvm::parseIRFile(nameofIRfile, diag, *context);
    if(M == nullptr)
    {
        show_usage("GPGPointsTo", 1);
        exit(1);
    }
    module = M.get();
    
    ut = new Util();
    gToB = ut->createXdashForAllGlobalVariables(module);
    ut->findAllLibraryFunctionsInModule(module);

    module->print(outs(),nullptr);
    CallGraph *callGraph = new CallGraph(*module);
    Function *mainFunction = module->getFunction("main");    
    CallGraphNode *rootNode = (*callGraph)[mainFunction];

    ut->printSCCOrder(rootNode);     

    for (scc_iterator<CallGraphNode *> SCCI = scc_begin(rootNode); SCCI != scc_end(rootNode); ++SCCI)
    {
        const std::vector<CallGraphNode *> &nextSCC = *SCCI;
        
        int i = 0;

        std::vector<CallGraphNode *>::const_iterator I;
        
        if(SCCI.hasLoop())
        {
            outs() << "Recursion\n";            
            set<StringRef> sccFunctions;

            for (I = nextSCC.begin(); I != nextSCC.end(); ++I, i++)
            {
                if ((*I)->getFunction())
                {

                    sccFunctions.insert((*I)->getFunction()->getName());                    
                }
            }

            ut->setSCCFunctions(sccFunctions);
        
            CreateSummaryForSCCFunctions(nextSCC);
            
            ut->reSetSCCFunctions();
        }        
        else
        {
            I = nextSCC.begin();
            if ((*I)->getFunction())
            {
                //(*I)->getFunction()->viewCFG();
                if (functionToGPG[(*I)->getFunction()->getName()])
                    continue;
                outs() << "\n Summary of function : ";
                outs() << (*I)->getFunction()->getName() << "\n";

                if (ut->libraryFunctionOrNot((*I)->getFunction()->getName()))
                {
                    outs() << "Empty \n";
                    continue;
                }

                if (ut->testCaseFunctionOrNot((*I)->getFunction()->getName()))
                {
                    outs() << "Empty \n";
                    continue;
                }

                if ((*I)->getFunction()->isDeclaration())
                {
                    outs() << "Empty \n";
                    continue;
                }

                FunctionWithGPG *fgpg = new FunctionWithGPG((*I)->getFunction());

                fgpg->setModule(module);

                fgpg->setDumpPointsTo(dumpPointsTo);
                std::cout << "\n";
                // std::cout << "Before preprocess\n";
            auto start_time = chrono::steady_clock::now();
                fgpg->preProcessFunction();
            auto end_time = chrono::steady_clock::now();
            auto preprocess_time = end_time - start_time;
                string progress = "\t[==>          ] 16.67\% Completed Preprocessing, Starting Initial GPG Construction";
                std::cout << cyan << progress << reset <<"\r";
                std::cout.flush();
                // std::cout << "After preprocess\n";

                fgpg->setupwardExposedVersionOfGlobalVar(module->getGlobalList(), gToB);
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
                progress = "\t[====>        ] 33.33\% Completed initial GPG construction, Starting Empty Nodes Removal      ";
                std::cout << cyan << progress << reset <<"\r";
                std::cout.flush();
                // std::cout << "AfterconstructGPG\n";

                fgpg->ValidateInitialGPUTests();

                fgpg->setBoundrayDef(module->getGlobalList(), gToB);

            start_time = chrono::steady_clock::now();
                fgpg->removeEmptyNodesInGPG();
            end_time = chrono::steady_clock::now();
            auto remove_empty_nodes_in_GPG_time = end_time - start_time;

                progress = "\t[======>      ] 50\% Completed Removing Empty Nodes, Starting Reaching GPU Analysis               ";
                std::cout << cyan << progress << reset <<"\r";
                std::cout.flush();
                // std::cout << "AfterremoveEmptyNodesInGPG_1\n";

            start_time = chrono::steady_clock::now();
                //fgpg->reachingGPUAnalysisWithOutBlocking();
            end_time = chrono::steady_clock::now();
            auto reaching_GPU_Analysis_WithOut_Blocking_time = end_time - start_time;
                // std::cout << "AfterreachingGPUAnalysisWithOutBlocking\n";
            
            start_time = chrono::steady_clock::now();
                //fgpg->reachingGPUAnalysisWithBlocking();
            end_time = chrono::steady_clock::now();
            auto reaching_GPU_Analysis_With_Blocking_time = end_time - start_time;
                
                progress = "\t[========>    ] 66.67\% Completed Reaching GPU Analysis and performed Strength Reduction, Starting Dead GPU Elimination";
                std::cout << cyan << progress << reset <<"\r";
                std::cout.flush();
                // std::cout << "AfterreachingGPUAnalysisWithBlocking\n";

                // fgpg->ReplaceFPUseNodeWithSummary(functionToGPG);
                // std::cout << "AfterReplaceFPUseNodeWithSummary\n";

                // fgpg->reachingGPUAnalysisWithOutBlocking();

                // fgpg->reachingGPUAnalysisWithBlocking();

                if (dumpPointsTo) fgpg->findPointsToPairs(PointsToInfo);

            start_time = chrono::steady_clock::now();
                //fgpg->deadGPUElimination();
            end_time = chrono::steady_clock::now();
            auto Dead_GPU_Elimination_time = end_time - start_time;
                
                progress = "\t[==========>  ] 83.33\% Completed Dead GPU Elimination, Starting Coalescing Analysis                                                   ";            
                std::cout << cyan << progress << reset <<"\r";
                std::cout.flush();

                // std::cout << "AfterDeadGPUElimination\n";
                fgpg->removeEmptyNodesInGPG();
                // fgpg->coalescingAnalysisInPaper();
                //outs()<<"Coalescing Analysis started .........eeee\n";
                // ------------------------------------------- My Implementation ---------------------------------//
            std::chrono::nanoseconds Coalescing_Analysis_time;
            if(with_updated_coalescing)
            {
                start_time = chrono::steady_clock::now();
                    //fgpg->UpdatedCoalescingAnalysis();
                end_time = chrono::steady_clock::now();
                Coalescing_Analysis_time = end_time - start_time;
            }
                // std::cout << "AfterUpdatedCoalescingAnalysis\n";
                // -----------------------------------------------------------------------------------------------//
            else
            {
                start_time = chrono::steady_clock::now();
                    //fgpg->coalescingAnalysisInThesis();
                end_time = chrono::steady_clock::now();
                Coalescing_Analysis_time = end_time - start_time;
            }
                progress = "\t[============>] 100\% Completed Coalescing Analysis and Summary Construction is Complete           ";
                std::cout << green << progress << reset <<"\r";
                std::cout << std::endl;
                // std::cout << "AfterCoalescingAnalysisInThesis\n";

                //fgpg->ValidateCoalesceTests();

                //fgpg->ValidatePointsToTests();

                functionToGPG[(*I)->getFunction()->getName()] = fgpg;
                TimeCalc[(*I)->getFunction()].push_back(preprocess_time);
                TimeCalc[(*I)->getFunction()].push_back(remove_empty_nodes_in_GPG_time);
                TimeCalc[(*I)->getFunction()].push_back(reaching_GPU_Analysis_WithOut_Blocking_time);
                TimeCalc[(*I)->getFunction()].push_back(reaching_GPU_Analysis_With_Blocking_time);
                TimeCalc[(*I)->getFunction()].push_back(Dead_GPU_Elimination_time);
                TimeCalc[(*I)->getFunction()].push_back(Coalescing_Analysis_time);
                outs() << "\nConstructed summary of function : " << (*I)->getFunction()->getName() << "\n";
            }
            else
            {
                // outs() << "Indirect CallGraph node (function pointer) or Library: Not handled\n";
                // exit(0);
                continue;
            }
        }
    }

#ifdef PRINT_STATS
#if PRINT_STATS == 1
    printAnalysisStatistics();
#endif
#endif
    // Dump
    std::string fn;
    for (int i = nameofIRfile.length() - 4; i >= 0; i--)
    {
        if (nameofIRfile[i] == '/')
            break;
        fn = nameofIRfile[i] + fn;
    }
    if (dumpPointsTo)
    {
        dumpPointsToInfo(fn);
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

}
std::string Driver::ExtractFileName(std::string nameofIRfile)
{
    std::string fn;
    for (int i = nameofIRfile.length() - 3; i >= 0; i--)
    {
        if (nameofIRfile[i] == '/')
            break;
        fn = nameofIRfile[i] + fn;
    }
    return fn;
}
void Driver::printAnalysisStatistics()
{
    std::chrono::nanoseconds total_preprocess_time = std::chrono::nanoseconds::zero(), total_Empty_Nodes_time = std::chrono::nanoseconds::zero() , total_RGAnalysisWOB_time = std::chrono::nanoseconds::zero(), total_RGAnalysisWB_time = std::chrono::nanoseconds::zero(), total_dead_GPU_time = std::chrono::nanoseconds::zero() , total_Coalescing_time = std::chrono::nanoseconds::zero();
    for(int i = 0; i < TimeCalc.size(); i++)
    {
        for(auto it : TimeCalc)
        {
            switch (i)
            {
                case 0:
                    total_preprocess_time += it.second[0];
                    break;
                case 1:
                    total_Empty_Nodes_time += it.second[1];
                    break;
                case 2:
                    total_RGAnalysisWOB_time += it.second[2];
                    break;
                case 3:
                    total_RGAnalysisWB_time += it.second[3];
                    break;
                case 4:
                    total_dead_GPU_time += it.second[4];
                    break;
                case 5:
                    total_Coalescing_time += it.second[5];
                    break;
                default:
                    break;
            }
        }
    }
    //statistics of Analysis    
    std::cout << "\n\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
    if(with_updated_coalescing) std::cout << magenta << "\n                                                 Statistics of GPG construction for every Function (Updated Coalescing)                                                       \n" << reset;
    else std::cout << magenta << "\n                                             Statistics of GPG construction for every Function (Coalescing in Thesis)                                                \n" << reset;
    std::cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n";
    std::cout << "\t================================================================================================================================================================\n";
    std::cout << "\t|" << std::setw(25) << red << "Function" << std::setw(22) << reset << "|" << std::setw(12) << green << "Preprocess" << std::setw(7) << reset << "|"<< std::setw(12) << green <<"EmptyNodes" <<  std::setw(7) << reset << "|" << std::setw(10) << green <<"RGAnalysisWOB" <<  std::setw(6) << reset <<"|"<< std::setw(10) << green <<"RGAnalysisWB"<< std::setw(7) << reset << "|" << std::setw(10) << green <<"DeadGPU" <<  std::setw(12) << reset  << "|"<< std::setw(12) << green <<"Coalescing"<<  std::setw(7) << reset <<"|";
    std::cout << "\n\t================================================================================================================================================================\n";
    int cnt = 0;
    for(auto it : TimeCalc)
    {
        std::cout << "\t|" << std::setw(35) << it.first->getName().str() << std::setw(10) << "|";
        for(auto i : it.second)
        {
            std::cout << std::setw(10) << std::fixed <<std::setprecision(2) << chrono::duration <double, milli> (i).count() << "ms" << std::setw(7) << "|";
        }
        if(it == *(--TimeCalc.end())) std::cout << cyan << "\n\t================================================================================================================================================================\n" << reset;
        else std::cout << "\n\t================================================================================================================================================================\n";
    }
    std::cout << cyan << "\t|" << setw(23) << "Total Time" << setw(22) << std::fixed << std::setprecision(2) << "|" << reset << std::setw(10) << chrono::duration <double, milli>(total_preprocess_time).count() << "ms" << std::setw(7) << "|" << std::setw(10) << chrono::duration <double, milli>(total_Empty_Nodes_time).count() << "ms" << std::setw(7) << "|" << std::setw(10)<< chrono::duration <double, milli>(total_RGAnalysisWOB_time).count() << "ms" << std::setw(7) << "|" << std::setw(10) << chrono::duration <double, milli>(total_RGAnalysisWB_time).count() <<  "ms" << std::setw(7) << "|" << std::setw(10) <<chrono::duration <double, milli>(total_dead_GPU_time).count() << "ms" << std::setw(7) << "|" << std::setw(10) << chrono::duration <double, milli>(total_Coalescing_time).count() << "ms" << std::setw(7) << "|";
    std::cout << cyan << "\n\t================================================================================================================================================================\n" << reset;
    std::cout << "\n\n\n";
    std::cout << "\t==========================================================================\n";
    std::cout << "\t|" << std::setw(35) << "Function" << std::setw(10) << "|" << std::setw(22) << "GPB Count" << std::setw(7) << "|\n";
    for(auto it :  functionToGPG)
    {
        if(!it.second) continue;
        std::cout << "\t==========================================================================\n";
        std::cout << "\t|" << std::setw(35) << it.first.str() << std::setw(10) << "|" << std::setw(15) << it.second->getSummary()->getGPBSet().size() << std::setw(14) << "|\n";
    }            
    std::cout << "\t==========================================================================\n";
}
void Driver::dumpPointsToInfo(std::string file)
{
    string path = "../../PointsToResults/";
    string fileName = file + ".pta.txt";
    ofstream ptWriter;
    ptWriter.open(path + fileName);
    ptWriter << "\t"
             << "******************************  Points-To Information  ******************************"
             << "\t\n";
    ptWriter << "\t"
             << "*************************************************************************************"
             << "\t\n";
    for (map<long, std::pair<set<GPU *, GPUComp>, std::string>>::iterator it = PointsToInfo.begin(); it != PointsToInfo.end(); it++)
    {
        ptWriter << "\t\t"
                 << "File: " << ExtractFileName((*it).second.second);
        ptWriter << "\t"
                 << "Line " << (*it).first << ": ";
        int cnt = 0;
        ptWriter << "\t{ ";
        for (auto i : (*it).second.first)
        {
            if (i->getSourceOfGPU()->getIndirectList()->getIndirectionLevel() == 1 && i->getTargetOfGPU()->getIndirectList()->getIndirectionLevel() == 0)
            {
                if (cnt != 0)
                    ptWriter << ", ";
                ptWriter << "(" << i->getSourceOfGPU()->getNameOfVariable().str() << ", " << i->getTargetOfGPU()->getNameOfVariable().str() << ")";
                cnt++;
            }
        }
        ptWriter << " }\n";
    }
    ptWriter << "\t"
             << "*************************************************************************************"
             << "\t";
    ptWriter.close();
}
void Driver::CreateSummaryForSCCFunctions(const std::vector<CallGraphNode *> &nextSCC)
{
    std::vector<CallGraphNode *>::const_iterator I; 
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
            outs() << "\n Initial Summary of function: ";
            outs() << (it)->getFunction()->getName() << "\n";
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

    map<StringRef, int> Iteration_count;
    while(!WorkList.empty())
    {

        Function* currFun = WorkList.front();
        WorkList.pop();        
        InsideWorkList[currFun] = 0;

        Iteration_count[currFun->getName()]++;

        if(functionToGPG.find(currFun->getName()) == functionToGPG.end())
        {
            outs() << "\n Summary of function: ";
            outs() << currFun->getName() << "\n";
            FunctionWithGPG *fgpg = tmpMap[currFun->getName()]; 
            fgpg->constructGPG(functionToGPG, ut);                       
            fgpg->removeEmptyNodesInGPG();
            fgpg->setBoundrayDef(currFun->getParent()->getGlobalList(), gToB);
            fgpg->handleRecursion(Iteration_count[currFun->getName()], with_updated_coalescing);

            set<Function*> callers = fgpg->getCallers();
            outs() << "Callers: {";
            for(auto it : callers)
            {
                if(it && ut->isItPartOfSCC(it->getName()) && !InsideWorkList[it])
                {
                    outs() << it->getName() << ", ";
                    WorkList.push(it);
                    InsideWorkList[it] = 1;
                }
            }
            outs() << "}\n";
            functionToGPG[currFun->getName()] = fgpg;            
        }
        else
        {
            FunctionWithGPG* fgpg = functionToGPG[currFun->getName()];            
            set<GPU*, GPUComp> prevRGOutWOBlocking = fgpg->getRGOutOfEnd(1);
            set<GPU*, GPUComp> prevRGOutWBlocking = fgpg->getRGOutOfEnd(0);
            
            fgpg->inliningCallsInSCC(functionToGPG);
            fgpg->handleRecursion(Iteration_count[currFun->getName()], with_updated_coalescing);

            set<GPU*, GPUComp> currRGOutWOBlocking = fgpg->getRGOutOfEnd(1);
            set<GPU*, GPUComp> currRGOutWBlocking = fgpg->getRGOutOfEnd(0);
            if(ut->isEqualOrNot(prevRGOutWOBlocking, currRGOutWOBlocking) == false || ut->isEqualOrNot(prevRGOutWBlocking, currRGOutWBlocking) == false)
            {
                set<Function*> callers = fgpg->getCallers();
                outs() << "Callers: {";
                for(auto it : callers)
                {
                    if(it && ut->isItPartOfSCC(it->getName()) && !InsideWorkList[it])
                    {
                        outs() << it->getName() << ", ";
                        WorkList.push(it);
                        InsideWorkList[it] = 1;
                    }
                }                
                outs() << "}\n";
            }
        }               
    }
}
void Driver::process_cmd_options(int count, char** options)
{
    if (count < 2)
    {
        show_usage(options[0]);
        return ;
    }
    for (int i = 1; i < count; ++i)
    {

        string arg = options[i];

        if ((arg == "-h") || (arg == "--help"))
        {
            show_usage(options[0]);
            return;
        }
        else if ((arg == "-d") || (arg == "--dump"))
        {
            dumpPointsTo = true;
        }
        else if(arg == "-updated-coalescing")
        {
            with_updated_coalescing = true;
        }
        else
            nameofIRfile = arg;
    }

}
void Driver::show_usage(string name, int err)
{

    if (err == 1)
        std::cerr << "Input File is not a valid llvm IR file" << std::endl;

    std::cerr
        << "\nUsage:  " << name << " <option(s)> InputFile \n"
        << "Options:\n"
        << "\t-h,--help\t Show this help message\n"
        << "\t-d, --dump \t Dump points-to information\n"
        << "\nInputFile: Valid llvm IR file \n"
        << std::endl;
}
