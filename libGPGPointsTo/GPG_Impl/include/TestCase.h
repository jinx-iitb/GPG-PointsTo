#ifndef TestCase_H_
#define TestCase_H_
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
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/raw_ostream.h"
#include <set>
#include "Util.h"
using namespace llvm;
using namespace std;

enum TestType { INITGPU, INTERGPU, POINTSTO, COALESCE };

class TestCase{

    StringRef fileName;
	  long lineNo;
    TestType type;

public:

    TestCase(StringRef,long,TestType);

    static inline bool classof(TestCase const *g) { return true; }

    TestType getTypeID() const { return type; }

    StringRef getFileName();

    long getLineNo();
};

// leftVar,indirectionLevel-->rightVar,indirectionLevel [lineNo]
class InitialGPUTest:public TestCase{

	StringRef gpu;
  long lineNoOfGPU;
public:

   InitialGPUTest(StringRef, long ,StringRef,long );

   static inline bool classof(InitialGPUTest const *g) { return true; }

   static inline bool classof(TestCase const *g) {

     if (g->getTypeID() == INITGPU)
       return true;
     else
      return false;
  }

  StringRef getGPU();


};
// leftVar,indirectionLevel-->rightVar,indirectionLevel [lineNo]
class IntermediateGPUTest:public TestCase{

	StringRef gpu;
  long lineNoOfGPU;
public:

    IntermediateGPUTest(StringRef,long,StringRef,long);

	static inline bool classof(IntermediateGPUTest const *g) { return true; }

    static inline bool classof(TestCase const *g) {

      if (g->getTypeID() == INTERGPU)
        return true;
      else
        return false;
    }

    StringRef getGPU();

};
class PointsToTest:public TestCase{
   
   StringRef name;
   set<StringRef> pointsToSet;
   bool pointsToOrNotPointsTo;
   bool ssaReplacedPointee;
   bool gotSameDuringSSAConversion;
public:

   PointsToTest(StringRef,long,StringRef,StringRef,bool);
   PointsToTest(StringRef, long, bool,bool);
   static inline bool classof(PointsToTest const *g) { return true; }

   static inline bool classof(TestCase const *g) {

     if (g->getTypeID() == POINTSTO)
       return true;
     else
      return false;
   }

  void setPointsToSet(StringRef);

  bool equalToUserPointsToSet(set<StringRef> actualSet);

  bool pointsToOrNotPointsToTest();
  bool gotSameDuringSSAConversionOrNot();
  bool ssaReplacedPointeeOrNot();
};

//In the summary of function, two gpus are in same block
class CoalesceTest:public TestCase{

	long lineNo1;
  long lineNo2;
  bool coalesceOrNotCoalesce;

public:

    CoalesceTest(StringRef,long,long,long,bool);

  	static inline bool classof(CoalesceTest const *g) { return true; }

    static inline bool classof(TestCase const *g) {

     if (g->getTypeID() == COALESCE)
       return true;
     else
      return false;
    }

    long getFirstLineNo();
    long getSecondLineNo();
    bool coalesceOrNotCoalesceTest();
};

#endif