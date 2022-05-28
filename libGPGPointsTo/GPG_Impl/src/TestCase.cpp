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



#include "TestCase.h"


TestCase::TestCase(StringRef fName, long lno,TestType t){

  fileName = fName;
	lineNo = lno;
	type = t;
}

StringRef TestCase::getFileName(){
	return fileName;
}

long TestCase::getLineNo(){
	return lineNo;
}

InitialGPUTest::InitialGPUTest(StringRef fName, long lno,StringRef g, long linegpu):TestCase(fName,lno,INITGPU){

	gpu = g;
	lineNoOfGPU = linegpu;
}

StringRef InitialGPUTest::getGPU(){
	return gpu;
}

IntermediateGPUTest::IntermediateGPUTest(StringRef fName,long lno,StringRef g, long linegpu):TestCase(fName,lno,INTERGPU){
	gpu = g;
	lineNoOfGPU = linegpu;
}

StringRef IntermediateGPUTest::getGPU(){
	return gpu;
}

PointsToTest::PointsToTest(StringRef fName,long lno,StringRef n,StringRef csList,bool pOrNp):TestCase(fName,lno,POINTSTO){
	name = n;
	pointsToOrNotPointsTo= pOrNp;
	ssaReplacedPointee = false;
	setPointsToSet(csList);
}

PointsToTest::PointsToTest(StringRef fName,long lno,bool pOrNp, bool yOrN):TestCase(fName,lno,POINTSTO){
	pointsToOrNotPointsTo= pOrNp;
	gotSameDuringSSAConversion = yOrN;
	ssaReplacedPointee = true;
}
bool PointsToTest::pointsToOrNotPointsToTest(){
    return pointsToOrNotPointsTo;
}

bool PointsToTest::equalToUserPointsToSet(set<StringRef> actualSet){

    //Util util;
    //util.print(actualSet);
    set<StringRef> mergeSet;
     
    if(pointsToSet.size()!=actualSet.size())  return false;

    for(auto aItr = actualSet.begin();aItr!=actualSet.end();aItr++)
    	 mergeSet.insert(*aItr);

    for(auto pItr = pointsToSet.begin();pItr!=pointsToSet.end();pItr++)
    	 mergeSet.insert(*pItr);

    //util.print(mergeSet);
    //outs()<<mergeSet.size()<<"      m\n";
    if(mergeSet.size()==actualSet.size())  return true;
    else                                   return false;	

}
void PointsToTest::setPointsToSet(StringRef commaSepPointsSet){

   char *temp;
   int elemStartPos = 0;
   SmallVector<StringRef,100> v;

   temp = new char[commaSepPointsSet.size()+1];
   
   commaSepPointsSet.split(v,",");
 
   //outs()<<commaSepPointsSet<<" t\n";
   for(auto vItr = v.begin();vItr!=v.end();vItr++)
   	    pointsToSet.insert(*vItr);
   //Util util;
   //util.print(pointsToSet);
}

bool PointsToTest::gotSameDuringSSAConversionOrNot(){
	return gotSameDuringSSAConversion;
}
bool PointsToTest::ssaReplacedPointeeOrNot(){
	return ssaReplacedPointee;
}

CoalesceTest::CoalesceTest(StringRef fName,long lno,long lno1,long lno2,bool cOrNc):TestCase(fName,lno,COALESCE){
	lineNo1 = lno1;
	lineNo2 = lno2;
	coalesceOrNotCoalesce= cOrNc;
}
long CoalesceTest::getFirstLineNo(){
	return lineNo1;
}
long CoalesceTest::getSecondLineNo(){
    return lineNo2;
}

bool CoalesceTest::coalesceOrNotCoalesceTest(){
	return coalesceOrNotCoalesce;
}

