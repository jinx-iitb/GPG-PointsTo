#ifndef IndirectionList_H_
#define IndirectionList_H_
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
#include <string>
#include <vector>

using namespace std;
// single pointer or list of fields
enum IndType { SINGLE, LIST };

class Indirection {

  // number of dereferences.
  int indirectionLevel;

  bool stackOrHeap;

  IndType typeId;

public:
  Indirection(IndType);

  Indirection(int, bool, IndType);

  ~Indirection();

  bool isStackOrHeap();

  int getIndirectionLevel();

  void setIndirectionLevel(int);

  void setStorageStackOrHeap(bool);

  virtual void print();

  static inline bool classof(Indirection const *iL) { return true; }

  IndType getTypeID() const { return typeId; }
  
  // ------------------------------------------ My Implementation ----------------------------------//
  Indirection* ListAppend(Indirection *);
  std::pair<int,vector<int>> ListRemainder(Indirection*);
  // -----------------------------------------------------------------------------------------------//
};

class IndirectionList : public Indirection {

  // position of struct member in the structure
  // p->f->f->f ...->f (max 100 assumed)
  // positions of fields are stored
  //int fieldList[100];
  std::vector<int> fieldList;
  int maxFields;

public:
  IndirectionList();

  IndirectionList(int, bool, int, vector<int>);

  IndirectionList(int, bool);

  ~IndirectionList();

  void print();

  static inline bool classof(IndirectionList const *iL) { return true; }

  static inline bool classof(Indirection const *i) {

    if (i->getTypeID() == LIST)
      return true;
    else
      return false;
  }

  int getNumberOfFields();

  vector<int> getFieldList();

  void addFields(int, vector<int>);

  string toString();
};

#endif
