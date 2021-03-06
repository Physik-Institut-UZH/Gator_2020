//
// File generated by /app/cern/root_v5.34.38/bin/rootcint at Tue Feb 11 16:59:50 2020

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME BCMVCMeasurementDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "BCMVCMeasurementDict.h"

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
   void BCMVCMeasurement_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void BCMVCMeasurement_Dictionary();
   static void delete_BCMVCMeasurement(void *p);
   static void deleteArray_BCMVCMeasurement(void *p);
   static void destruct_BCMVCMeasurement(void *p);

   // Function generating the singleton type initializer
   static ROOT::TGenericClassInfo *GenerateInitInstanceLocal(const ::BCMVCMeasurement*)
   {
      ::BCMVCMeasurement *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::BCMVCMeasurement),0);
      static ::ROOT::TGenericClassInfo 
         instance("BCMVCMeasurement", "./BCMVCMeasurement.h", 19,
                  typeid(::BCMVCMeasurement), ::ROOT::DefineBehavior(ptr, ptr),
                  0, &BCMVCMeasurement_Dictionary, isa_proxy, 0,
                  sizeof(::BCMVCMeasurement) );
      instance.SetDelete(&delete_BCMVCMeasurement);
      instance.SetDeleteArray(&deleteArray_BCMVCMeasurement);
      instance.SetDestructor(&destruct_BCMVCMeasurement);
      return &instance;
   }
   ROOT::TGenericClassInfo *GenerateInitInstance(const ::BCMVCMeasurement*)
   {
      return GenerateInitInstanceLocal((::BCMVCMeasurement*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::BCMVCMeasurement*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void BCMVCMeasurement_Dictionary() {
      ::ROOTDict::GenerateInitInstanceLocal((const ::BCMVCMeasurement*)0x0)->GetClass();
   }

} // end of namespace ROOTDict

namespace ROOTDict {
   // Wrapper around operator delete
   static void delete_BCMVCMeasurement(void *p) {
      delete ((::BCMVCMeasurement*)p);
   }
   static void deleteArray_BCMVCMeasurement(void *p) {
      delete [] ((::BCMVCMeasurement*)p);
   }
   static void destruct_BCMVCMeasurement(void *p) {
      typedef ::BCMVCMeasurement current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOTDict for class ::BCMVCMeasurement

/********************************************************
* BCMVCMeasurementDict.cxx
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

extern "C" void G__cpp_reset_tagtableBCMVCMeasurementDict();

extern "C" void G__set_cpp_environmentBCMVCMeasurementDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("BCMVCMeasurement.h");
  G__cpp_reset_tagtableBCMVCMeasurementDict();
}
#include <new>
extern "C" int G__cpp_dllrevBCMVCMeasurementDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* BCMVCMeasurement */
static int G__BCMVCMeasurementDict_168_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   BCMVCMeasurement* p = NULL;
   char* gvp = (char*) G__getgvp();
   //m: 1
   if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
     p = new BCMVCMeasurement(*((string*) G__int(libp->para[0])));
   } else {
     p = new((void*) gvp) BCMVCMeasurement(*((string*) G__int(libp->para[0])));
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_BCMVCMeasurement));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMVCMeasurementDict_168_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      {
         string* pobj;
         string xobj = ((BCMVCMeasurement*) G__getstructoffset())->GetName();
         pobj = new string(xobj);
         result7->obj.i = (long) ((void*) pobj);
         result7->ref = result7->obj.i;
         G__store_tempobject(*result7);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMVCMeasurementDict_168_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((BCMVCMeasurement*) G__getstructoffset())->GetObservable());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMVCMeasurementDict_168_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((BCMVCMeasurement*) G__getstructoffset())->GetCentralValue());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMVCMeasurementDict_168_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      {
         vector<double>* pobj;
         vector<double> xobj = ((BCMVCMeasurement*) G__getstructoffset())->GetUncertainties();
         pobj = new vector<double>(xobj);
         result7->obj.i = (long) ((void*) pobj);
         result7->ref = result7->obj.i;
         G__store_tempobject(*result7);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMVCMeasurementDict_168_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((BCMVCMeasurement*) G__getstructoffset())->GetUncertainty((int) G__int(libp->para[0])));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMVCMeasurementDict_168_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letdouble(result7, 100, (double) ((BCMVCMeasurement*) G__getstructoffset())->GetTotalUncertainty());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMVCMeasurementDict_168_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 103, (long) ((BCMVCMeasurement*) G__getstructoffset())->GetFlagActive());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMVCMeasurementDict_168_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((BCMVCMeasurement*) G__getstructoffset())->SetObservable((int) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMVCMeasurementDict_168_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((BCMVCMeasurement*) G__getstructoffset())->SetCentralValue((double) G__double(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMVCMeasurementDict_168_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((BCMVCMeasurement*) G__getstructoffset())->SetUncertainties(*((vector<double>*) G__int(libp->para[0])));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMVCMeasurementDict_168_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((BCMVCMeasurement*) G__getstructoffset())->SetFlagActive((bool) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__BCMVCMeasurementDict_168_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   BCMVCMeasurement* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new BCMVCMeasurement(*(BCMVCMeasurement*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_BCMVCMeasurement));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef BCMVCMeasurement G__TBCMVCMeasurement;
static int G__BCMVCMeasurementDict_168_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
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
       delete[] (BCMVCMeasurement*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((BCMVCMeasurement*) (soff+(sizeof(BCMVCMeasurement)*i)))->~G__TBCMVCMeasurement();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (BCMVCMeasurement*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((BCMVCMeasurement*) (soff))->~G__TBCMVCMeasurement();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__BCMVCMeasurementDict_168_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   BCMVCMeasurement* dest = (BCMVCMeasurement*) G__getstructoffset();
   *dest = *(BCMVCMeasurement*) libp->para[0].ref;
   const BCMVCMeasurement& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* BCMVCMeasurement */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncBCMVCMeasurementDict {
 public:
  G__Sizep2memfuncBCMVCMeasurementDict(): p(&G__Sizep2memfuncBCMVCMeasurementDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncBCMVCMeasurementDict::*p)();
};

size_t G__get_sizep2memfuncBCMVCMeasurementDict()
{
  G__Sizep2memfuncBCMVCMeasurementDict a;
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
extern "C" void G__cpp_setup_inheritanceBCMVCMeasurementDict() {

   /* Setting up class inheritance */
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableBCMVCMeasurementDict() {

   /* Setting up typedef entry */
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* BCMVCMeasurement */
static void G__setup_memvarBCMVCMeasurement(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_BCMVCMeasurement));
   { BCMVCMeasurement *p; p=(BCMVCMeasurement*)0x1000; if (p) { }
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_string),-1,-1,4,"fName=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,-1,-1,-1,4,"fObservable=",0,(char*)NULL);
   G__memvar_setup((void*)0,100,0,0,-1,-1,-1,4,"fCentralValue=",0,(char*)NULL);
   G__memvar_setup((void*)0,117,0,0,G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR),G__defined_typename("vector<double>"),-1,4,"fUncertainties=",0,(char*)NULL);
   G__memvar_setup((void*)0,103,0,0,-1,-1,-1,4,"fFlagActive=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarBCMVCMeasurementDict() {
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
static void G__setup_memfuncBCMVCMeasurement(void) {
   /* BCMVCMeasurement */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_BCMVCMeasurement));
   G__memfunc_setup("BCMVCMeasurement",1521,G__BCMVCMeasurementDict_168_0_1, 105, G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_BCMVCMeasurement), -1, 0, 1, 1, 1, 0, "u 'string' - 0 - name", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetName",673,G__BCMVCMeasurementDict_168_0_2, 117, G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_string), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetObservable",1317,G__BCMVCMeasurementDict_168_0_3, 105, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetCentralValue",1510,G__BCMVCMeasurementDict_168_0_4, 100, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetUncertainties",1662,G__BCMVCMeasurementDict_168_0_5, 117, G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR), G__defined_typename("vector<double>"), 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetUncertainty",1462,G__BCMVCMeasurementDict_168_0_6, 100, -1, -1, 0, 1, 1, 1, 0, "i - - 0 - index", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetTotalUncertainty",1978,G__BCMVCMeasurementDict_168_0_7, 100, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetFlagActive",1270,G__BCMVCMeasurementDict_168_0_8, 103, -1, -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetObservable",1329,G__BCMVCMeasurementDict_168_0_9, 121, -1, -1, 0, 1, 1, 1, 0, "i - - 0 - index", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetCentralValue",1522,G__BCMVCMeasurementDict_168_0_10, 121, -1, -1, 0, 1, 1, 1, 0, "d - - 0 - value", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetUncertainties",1674,G__BCMVCMeasurementDict_168_0_11, 121, -1, -1, 0, 1, 1, 1, 0, "u 'vector<double,allocator<double> >' 'vector<double>' 0 - uncertainties", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetFlagActive",1282,G__BCMVCMeasurementDict_168_0_12, 121, -1, -1, 0, 1, 1, 1, 0, "g - - 0 - flag", (char*)NULL, (void*) NULL, 0);
   // automatic copy constructor
   G__memfunc_setup("BCMVCMeasurement", 1521, G__BCMVCMeasurementDict_168_0_13, (int) ('i'), G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_BCMVCMeasurement), -1, 0, 1, 1, 1, 0, "u 'BCMVCMeasurement' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~BCMVCMeasurement", 1647, G__BCMVCMeasurementDict_168_0_14, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 0);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__BCMVCMeasurementDict_168_0_15, (int) ('u'), G__get_linked_tagnum(&G__BCMVCMeasurementDictLN_BCMVCMeasurement), -1, 1, 1, 1, 1, 0, "u 'BCMVCMeasurement' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncBCMVCMeasurementDict() {
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
extern "C" void G__cpp_setup_globalBCMVCMeasurementDict() {
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

extern "C" void G__cpp_setup_funcBCMVCMeasurementDict() {
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
G__linked_taginfo G__BCMVCMeasurementDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR = { "vector<double,allocator<double> >" , 99 , -1 };
G__linked_taginfo G__BCMVCMeasurementDictLN_string = { "string" , 99 , -1 };
G__linked_taginfo G__BCMVCMeasurementDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__BCMVCMeasurementDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__BCMVCMeasurementDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__BCMVCMeasurementDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__BCMVCMeasurementDictLN_BCMVCMeasurement = { "BCMVCMeasurement" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableBCMVCMeasurementDict() {
  G__BCMVCMeasurementDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR.tagnum = -1 ;
  G__BCMVCMeasurementDictLN_string.tagnum = -1 ;
  G__BCMVCMeasurementDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__BCMVCMeasurementDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__BCMVCMeasurementDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__BCMVCMeasurementDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__BCMVCMeasurementDictLN_BCMVCMeasurement.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableBCMVCMeasurementDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__BCMVCMeasurementDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR);
   G__get_linked_tagnum_fwd(&G__BCMVCMeasurementDictLN_string);
   G__get_linked_tagnum_fwd(&G__BCMVCMeasurementDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__BCMVCMeasurementDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__BCMVCMeasurementDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__BCMVCMeasurementDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__BCMVCMeasurementDictLN_BCMVCMeasurement),sizeof(BCMVCMeasurement),-1,33792,(char*)NULL,G__setup_memvarBCMVCMeasurement,G__setup_memfuncBCMVCMeasurement);
}
extern "C" void G__cpp_setupBCMVCMeasurementDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupBCMVCMeasurementDict()");
  G__set_cpp_environmentBCMVCMeasurementDict();
  G__cpp_setup_tagtableBCMVCMeasurementDict();

  G__cpp_setup_inheritanceBCMVCMeasurementDict();

  G__cpp_setup_typetableBCMVCMeasurementDict();

  G__cpp_setup_memvarBCMVCMeasurementDict();

  G__cpp_setup_memfuncBCMVCMeasurementDict();
  G__cpp_setup_globalBCMVCMeasurementDict();
  G__cpp_setup_funcBCMVCMeasurementDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncBCMVCMeasurementDict();
  return;
}
class G__cpp_setup_initBCMVCMeasurementDict {
  public:
    G__cpp_setup_initBCMVCMeasurementDict() { G__add_setup_func("BCMVCMeasurementDict",(G__incsetup)(&G__cpp_setupBCMVCMeasurementDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initBCMVCMeasurementDict() { G__remove_setup_func("BCMVCMeasurementDict"); }
};
G__cpp_setup_initBCMVCMeasurementDict G__cpp_setup_initializerBCMVCMeasurementDict;

