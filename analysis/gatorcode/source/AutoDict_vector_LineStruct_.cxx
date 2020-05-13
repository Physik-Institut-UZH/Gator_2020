#include "vector"
#include "./include/GatorStructs.h"
#ifdef __CINT__ 
#pragma link C++ nestedclasses;
#pragma link C++ nestedtypedefs;
#pragma link C++ class vector<LineStruct>+;
#pragma link C++ class vector<LineStruct>::*;
#ifdef G__VECTOR_HAS_CLASS_ITERATOR
#pragma link C++ operators vector<LineStruct>::iterator;
#pragma link C++ operators vector<LineStruct>::const_iterator;
#pragma link C++ operators vector<LineStruct>::reverse_iterator;
#endif
#endif
