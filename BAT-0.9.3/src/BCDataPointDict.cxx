//
// File generated by /app/cern/root_v5.34.38/bin/rootcint at Tue Feb 11 16:57:01 2020

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME BCDataPointDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "BCDataPointDict.h"

#include "TClass.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"

// Direct notice to TROOT of the dictionary's loading.
namespace {
   static struct DictInit {
      DictInit() {
         ROOT::RegisterModule();
      }
   } __TheDictionaryInitializer;
}

// START OF SHADOWS

namespace ROOTShadow {
   namespace Shadow {
   } // of namespace Shadow
} // of namespace ROOTShadow
// END OF SHADOWS

namespace ROOTDict {
   void BCDataPoint_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void BCDataPoint_Dictionary();
   static void delete_BCDataPoint(void *p);
   static void deleteArray_BCDataPoint(void *p);
   static void destruct_BCDataPoint(void *p);

   // Function generating the singleton type initializer
   static ROOT::TGenericClassInfo *GenerateInitInstanceLocal(const ::BCDataPoint*)
   {
      ::BCDataPoint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::BCDataPoint),0);
      static ::ROOT::TGenericClassInfo 
         instance("BCDataPoint", "./../BAT/BCDataPoint.h", 32,
                  typeid(::BCDataPoint), ::ROOT::DefineBehavior(ptr, ptr),
                  0, &BCDataPoint_Dictionary, isa_proxy, 0,
                  sizeof(::BCDataPoint) );
      instance.SetDelete(&delete_BCDataPoint);
      instance.SetDeleteArray(&deleteArray_BCDataPoint);
      instance.SetDestructor(&destruct_BCDataPoint);
      return &instance;
   }
   ROOT::TGenericClassInfo *GenerateInitInstance(const ::BCDataPoint*)
   {
      return GenerateInitInstanceLocal((::BCDataPoint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::BCDataPoint*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void BCDataPoint_Dictionary() {
      ::ROOTDict::GenerateInitInstanceLocal((const ::BCDataPoint*)0x0)->GetClass();
   }

} // end of namespace ROOTDict

namespace ROOTDict {
   // Wrapper around operator delete
   static void delete_BCDataPoint(void *p) {
      delete ((::BCDataPoint*)p);
   }
   static void deleteArray_BCDataPoint(void *p) {
      delete [] ((::BCDataPoint*)p);
   }
   static void destruct_BCDataPoint(void *p) {
      typedef ::BCDataPoint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOTDict for class ::BCDataPoint

/********************************************************
* BCDataPointDict.cxx
* CAUTION: DON'T CHANGE THIS FILE. THIS FILE IS AUTOMATICALLY GENERATED
*          FROM HEADER FILES LISTED IN G__setup_cpp_environmentXXX().
*          CHANGE THOSE HEADER FILES AND REGENERATE THIS FILE.
********************************************************/

#ifdef G__MEMTEST
#undef malloc
#undef free
#endif

#if defined(__GNUC__) && __GNUC__ >= 4 && ((__GNUC_MINOR__ == 2 && __GNUC_PATCHLEVEL__ >= 1) || (__GNUC_MINOR__ >= 3))
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

extern "C" void G__cpp_reset_tagtableBCDataPointDict();

extern "C" void G__set_cpp_environmentBCDataPointDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("../BAT/BCDataPoint.h");
  G__cpp_reset_tagtableBCDataPointDict();
}
#include <new>
extern "C" int G__cpp_dllrevBCDataPointDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* BCDataPoint */
static int G__BCDataPointDict_168_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   BCDataPoint* p = NULL;
   char* gvp = (char*) G__getgvp();
   //m: 1
   if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
     p = new BCDataPoint((int) G__int(libp->para[0]));
   } else {
     p = new((void*) gvp) BCDataPoint((int) G__int(libp->para[0]));
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__BCDataPointDictLN_BCDataPoint));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCDataPointDict_168_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   BCDataPoint* p = NULL;
   char* gvp = (char*) G__getgvp();
   //m: 1
   if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
     p = new BCDataPoint(*(vector<double>*) libp->para[0].ref);
   } else {
     p = new((void*) gvp) BCDataPoint(*(vector<double>*) libp->para[0].ref);
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__BCDataPointDictLN_BCDataPoint));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCDataPointDict_168_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((const BCDataPoint*) G__getstructoffset())->GetValue((unsigned int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCDataPointDict_168_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      {
         const vector<double>& obj = ((const BCDataPoint*) G__getstructoffset())->GetValues();
         result7->ref = (long) (&obj);
         result7->obj.i = (long) (&obj);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCDataPointDict_168_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 104, (long) ((const BCDataPoint*) G__getstructoffset())->GetNValues());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCDataPointDict_168_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((BCDataPoint*) G__getstructoffset())->SetValue((unsigned int) G__int(libp->para[0]), (double) G__double(libp->para[1]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCDataPointDict_168_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((BCDataPoint*) G__getstructoffset())->SetValues(*(vector<double>*) libp->para[0].ref);
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__BCDataPointDict_168_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   BCDataPoint* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new BCDataPoint(*(BCDataPoint*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__BCDataPointDictLN_BCDataPoint));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef BCDataPoint G__TBCDataPoint;
static int G__BCDataPointDict_168_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   char* gvp = (char*) G__getgvp();
   long soff = G__getstructoffset();
   int n = G__getaryconstruct();
   //
   //has_a_delete: 0
   //has_own_delete1arg: 0
   //has_own_delete2arg: 0
   //
   if (!soff) {
     return(1);
   }
   if (n) {
     if (gvp == (char*)G__PVOID) {
       delete[] (BCDataPoint*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((BCDataPoint*) (soff+(sizeof(BCDataPoint)*i)))->~G__TBCDataPoint();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (BCDataPoint*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((BCDataPoint*) (soff))->~G__TBCDataPoint();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__BCDataPointDict_168_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   BCDataPoint* dest = (BCDataPoint*) G__getstructoffset();
   *dest = *(BCDataPoint*) libp->para[0].ref;
   const BCDataPoint& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* BCDataPoint */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncBCDataPointDict {
 public:
  G__Sizep2memfuncBCDataPointDict(): p(&G__Sizep2memfuncBCDataPointDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncBCDataPointDict::*p)();
};

size_t G__get_sizep2memfuncBCDataPointDict()
{
  G__Sizep2memfuncBCDataPointDict a;
  G__setsizep2memfunc((int)a.sizep2memfunc());
  return((size_t)a.sizep2memfunc());
}


/*********************************************************
* virtual base class offset calculation interface
*********************************************************/

   /* Setting up class inheritance */

/*********************************************************
* Inheritance information setup/
*********************************************************/
extern "C" void G__cpp_setup_inheritanceBCDataPointDict() {

   /* Setting up class inheritance */
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableBCDataPointDict() {

   /* Setting up typedef entry */
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__BCDataPointDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BCDataPointDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCDataPointDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BCDataPointDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCDataPointDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__BCDataPointDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BCDataPointDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCDataPointDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BCDataPointDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCDataPointDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* BCDataPoint */
static void G__setup_memvarBCDataPoint(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__BCDataPointDictLN_BCDataPoint));
   { BCDataPoint *p; p=(BCDataPoint*)0x1000; if (p) { }
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__BCDataPointDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR),G__defined_typename("vector<double>"),-1,4,"fData=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarBCDataPointDict() {
}
/***********************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
************************************************************
***********************************************************/

/*********************************************************
* Member function information setup for each class
*********************************************************/
static void G__setup_memfuncBCDataPoint(void) {
   /* BCDataPoint */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__BCDataPointDictLN_BCDataPoint));
   G__memfunc_setup("BCDataPoint",1033,G__BCDataPointDict_168_0_1, 105, G__get_linked_tagnum(&G__BCDataPointDictLN_BCDataPoint), -1, 0, 1, 1, 1, 0, "i - - 0 - nvariables", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("BCDataPoint",1033,G__BCDataPointDict_168_0_2, 105, G__get_linked_tagnum(&G__BCDataPointDictLN_BCDataPoint), -1, 0, 1, 1, 1, 0, "u 'vector<double,allocator<double> >' 'vector<double>' 11 - x", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetValue",797,G__BCDataPointDict_168_0_3, 100, -1, -1, 0, 1, 1, 1, 8, "h - - 0 - -", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetValues",912,G__BCDataPointDict_168_0_4, 117, G__get_linked_tagnum(&G__BCDataPointDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR), G__defined_typename("vector<double>"), 1, 0, 1, 1, 9, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetNValues",990,G__BCDataPointDict_168_0_5, 104, -1, -1, 0, 0, 1, 1, 8, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetValue",809,G__BCDataPointDict_168_0_6, 121, -1, -1, 0, 2, 1, 1, 0, 
"h - - 0 - - d - - 0 - value", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetValues",924,G__BCDataPointDict_168_0_7, 121, -1, -1, 0, 1, 1, 1, 0, "u 'vector<double,allocator<double> >' 'vector<double>' 11 - values", (char*)NULL, (void*) NULL, 0);
   // automatic copy constructor
   G__memfunc_setup("BCDataPoint", 1033, G__BCDataPointDict_168_0_8, (int) ('i'), G__get_linked_tagnum(&G__BCDataPointDictLN_BCDataPoint), -1, 0, 1, 1, 1, 0, "u 'BCDataPoint' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~BCDataPoint", 1159, G__BCDataPointDict_168_0_9, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 0);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__BCDataPointDict_168_0_10, (int) ('u'), G__get_linked_tagnum(&G__BCDataPointDictLN_BCDataPoint), -1, 1, 1, 1, 1, 0, "u 'BCDataPoint' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncBCDataPointDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalBCDataPointDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
}

/*********************************************************
* Global function information setup for each class
*********************************************************/
static void G__cpp_setup_func0() {
   G__lastifuncposition();

}

static void G__cpp_setup_func1() {
}

static void G__cpp_setup_func2() {
}

static void G__cpp_setup_func3() {
}

static void G__cpp_setup_func4() {
}

static void G__cpp_setup_func5() {
}

static void G__cpp_setup_func6() {
}

static void G__cpp_setup_func7() {
}

static void G__cpp_setup_func8() {
}

static void G__cpp_setup_func9() {
}

static void G__cpp_setup_func10() {
}

static void G__cpp_setup_func11() {
}

static void G__cpp_setup_func12() {
}

static void G__cpp_setup_func13() {
}

static void G__cpp_setup_func14() {
}

static void G__cpp_setup_func15() {
}

static void G__cpp_setup_func16() {
}

static void G__cpp_setup_func17() {
}

static void G__cpp_setup_func18() {
}

static void G__cpp_setup_func19() {
}

static void G__cpp_setup_func20() {
}

static void G__cpp_setup_func21() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcBCDataPointDict() {
  G__cpp_setup_func0();
  G__cpp_setup_func1();
  G__cpp_setup_func2();
  G__cpp_setup_func3();
  G__cpp_setup_func4();
  G__cpp_setup_func5();
  G__cpp_setup_func6();
  G__cpp_setup_func7();
  G__cpp_setup_func8();
  G__cpp_setup_func9();
  G__cpp_setup_func10();
  G__cpp_setup_func11();
  G__cpp_setup_func12();
  G__cpp_setup_func13();
  G__cpp_setup_func14();
  G__cpp_setup_func15();
  G__cpp_setup_func16();
  G__cpp_setup_func17();
  G__cpp_setup_func18();
  G__cpp_setup_func19();
  G__cpp_setup_func20();
  G__cpp_setup_func21();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__BCDataPointDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR = { "vector<double,allocator<double> >" , 99 , -1 };
G__linked_taginfo G__BCDataPointDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__BCDataPointDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__BCDataPointDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__BCDataPointDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__BCDataPointDictLN_BCDataPoint = { "BCDataPoint" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableBCDataPointDict() {
  G__BCDataPointDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR.tagnum = -1 ;
  G__BCDataPointDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__BCDataPointDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__BCDataPointDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__BCDataPointDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__BCDataPointDictLN_BCDataPoint.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableBCDataPointDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__BCDataPointDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR);
   G__get_linked_tagnum_fwd(&G__BCDataPointDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__BCDataPointDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__BCDataPointDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__BCDataPointDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__BCDataPointDictLN_BCDataPoint),sizeof(BCDataPoint),-1,32768,(char*)NULL,G__setup_memvarBCDataPoint,G__setup_memfuncBCDataPoint);
}
extern "C" void G__cpp_setupBCDataPointDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupBCDataPointDict()");
  G__set_cpp_environmentBCDataPointDict();
  G__cpp_setup_tagtableBCDataPointDict();

  G__cpp_setup_inheritanceBCDataPointDict();

  G__cpp_setup_typetableBCDataPointDict();

  G__cpp_setup_memvarBCDataPointDict();

  G__cpp_setup_memfuncBCDataPointDict();
  G__cpp_setup_globalBCDataPointDict();
  G__cpp_setup_funcBCDataPointDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncBCDataPointDict();
  return;
}
class G__cpp_setup_initBCDataPointDict {
  public:
    G__cpp_setup_initBCDataPointDict() { G__add_setup_func("BCDataPointDict",(G__incsetup)(&G__cpp_setupBCDataPointDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initBCDataPointDict() { G__remove_setup_func("BCDataPointDict"); }
};
G__cpp_setup_initBCDataPointDict G__cpp_setup_initializerBCDataPointDict;
