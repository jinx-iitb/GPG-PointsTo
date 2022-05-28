#ifndef _DRIVER_
#define _DRIVER_

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "Util.h"
#include "FunctionWithGPG.h"
#include "llvm/ADT/GraphTraits.h"
#include "llvm/ADT/PostOrderIterator.h"
#include "llvm/ADT/SCCIterator.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
// #include "PointsToDump/FS_PTWriter.h"
// #include "PointsToDump/PTWriter.h"
// #include "PointsToDump/PTReader.h"
// #include "PointsToDump/FS_PTReader.h"

const std::string red("\033[1;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[1;36m");
const std::string magenta("\033[1;35m");
const std::string reset("\033[0m");
const std::string bgBrightWhite("\033[47;1m");

class Driver
{
    std::string nameofIRfile;
    bool dumpPointsTo;
    llvm::Module* module;
    std::map<StringRef, char *> gToB;
    map<StringRef, FunctionWithGPG *> functionToGPG;
    bool with_updated_coalescing;
    std::map<Function*, std::vector<std::chrono::nanoseconds> > TimeCalc;
    map<long, std::pair<set<GPU *, GPUComp>, std::string>> PointsToInfo;
    Util *ut;

    public:
        Driver(int, char**);
        ~Driver();
        void process_cmd_options(int count, char* options[]);
        void show_usage(std::string, int err = 0);
        void performAnalysis();
        void CreateSummaryForSCCFunctions(const std::vector<CallGraphNode *> &nextSCC);
        void dumpPointsToInfo(std::string file);
        std::string ExtractFileName(std::string);
        void printAnalysisStatistics();

};
#endif // !_DRIVER_