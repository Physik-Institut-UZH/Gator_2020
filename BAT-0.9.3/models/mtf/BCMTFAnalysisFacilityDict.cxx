//
// File generated by /app/cern/root_v5.34.38/bin/rootcint at Tue Feb 11 16:59:06 2020

// Do NOT change. Changes will be lost next time file is generated
//

#define R__DICTIONARY_FILENAME BCMTFAnalysisFacilityDict
#include "RConfig.h" //rootcint 4834
#if !defined(R__ACCESS_IN_SYMBOL)
//Break the privacy of classes -- Disabled for the moment
#define private public
#define protected public
#endif

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;
#include "BCMTFAnalysisFacilityDict.h"

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
   void BCMTFAnalysisFacility_ShowMembers(void *obj, TMemberInspector &R__insp);
   static void BCMTFAnalysisFacility_Dictionary();
   static void delete_BCMTFAnalysisFacility(void *p);
   static void deleteArray_BCMTFAnalysisFacility(void *p);
   static void destruct_BCMTFAnalysisFacility(void *p);

   // Function generating the singleton type initializer
   static ROOT::TGenericClassInfo *GenerateInitInstanceLocal(const ::BCMTFAnalysisFacility*)
   {
      ::BCMTFAnalysisFacility *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::BCMTFAnalysisFacility),0);
      static ::ROOT::TGenericClassInfo 
         instance("BCMTFAnalysisFacility", "./BCMTFAnalysisFacility.h", 36,
                  typeid(::BCMTFAnalysisFacility), ::ROOT::DefineBehavior(ptr, ptr),
                  0, &BCMTFAnalysisFacility_Dictionary, isa_proxy, 0,
                  sizeof(::BCMTFAnalysisFacility) );
      instance.SetDelete(&delete_BCMTFAnalysisFacility);
      instance.SetDeleteArray(&deleteArray_BCMTFAnalysisFacility);
      instance.SetDestructor(&destruct_BCMTFAnalysisFacility);
      return &instance;
   }
   ROOT::TGenericClassInfo *GenerateInitInstance(const ::BCMTFAnalysisFacility*)
   {
      return GenerateInitInstanceLocal((::BCMTFAnalysisFacility*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::BCMTFAnalysisFacility*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void BCMTFAnalysisFacility_Dictionary() {
      ::ROOTDict::GenerateInitInstanceLocal((const ::BCMTFAnalysisFacility*)0x0)->GetClass();
   }

} // end of namespace ROOTDict

namespace ROOTDict {
   // Wrapper around operator delete
   static void delete_BCMTFAnalysisFacility(void *p) {
      delete ((::BCMTFAnalysisFacility*)p);
   }
   static void deleteArray_BCMTFAnalysisFacility(void *p) {
      delete [] ((::BCMTFAnalysisFacility*)p);
   }
   static void destruct_BCMTFAnalysisFacility(void *p) {
      typedef ::BCMTFAnalysisFacility current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOTDict for class ::BCMTFAnalysisFacility

/********************************************************
* BCMTFAnalysisFacilityDict.cxx
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

extern "C" void G__cpp_reset_tagtableBCMTFAnalysisFacilityDict();

extern "C" void G__set_cpp_environmentBCMTFAnalysisFacilityDict() {
  G__add_compiledheader("TObject.h");
  G__add_compiledheader("TMemberInspector.h");
  G__add_compiledheader("BCMTFAnalysisFacility.h");
  G__cpp_reset_tagtableBCMTFAnalysisFacilityDict();
}
#include <new>
extern "C" int G__cpp_dllrevBCMTFAnalysisFacilityDict() { return(30051515); }

/*********************************************************
* Member function Interface Method
*********************************************************/

/* BCMTFAnalysisFacility */
static int G__BCMTFAnalysisFacilityDict_221_0_1(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   BCMTFAnalysisFacility* p = NULL;
   char* gvp = (char*) G__getgvp();
   //m: 1
   if ((gvp == (char*)G__PVOID) || (gvp == 0)) {
     p = new BCMTFAnalysisFacility((BCMTF*) G__int(libp->para[0]));
   } else {
     p = new((void*) gvp) BCMTFAnalysisFacility((BCMTF*) G__int(libp->para[0]));
   }
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_BCMTFAnalysisFacility));
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_2(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 85, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->GetBCMTF());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_3(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((BCMTFAnalysisFacility*) G__getstructoffset())->SetBCMTF((BCMTF*) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_4(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((BCMTFAnalysisFacility*) G__getstructoffset())->SetFlagMarginalize((bool) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_5(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      G__letint(result7, 105, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->GetLogLevel());
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_6(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      ((BCMTFAnalysisFacility*) G__getstructoffset())->SetLogLevel((BCLog::LogLevel) G__int(libp->para[0]));
      G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_7(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   switch (libp->paran) {
   case 2:
      G__letint(result7, 105, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->PerformSingleChannelAnalyses((const char*) G__int(libp->para[0]), (const char*) G__int(libp->para[1])));
      break;
   case 1:
      G__letint(result7, 105, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->PerformSingleChannelAnalyses((const char*) G__int(libp->para[0])));
      break;
   }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_8(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   switch (libp->paran) {
   case 2:
      G__letint(result7, 105, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->PerformSingleSystematicAnalyses((const char*) G__int(libp->para[0]), (const char*) G__int(libp->para[1])));
      break;
   case 1:
      G__letint(result7, 105, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->PerformSingleSystematicAnalyses((const char*) G__int(libp->para[0])));
      break;
   }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_9(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   switch (libp->paran) {
   case 5:
      G__letint(result7, 105, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->PerformCalibrationAnalysis((const char*) G__int(libp->para[0]), *(vector<double>*) libp->para[1].ref
, (int) G__int(libp->para[2]), *(vector<double>*) libp->para[3].ref
, (int) G__int(libp->para[4])));
      break;
   case 4:
      G__letint(result7, 105, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->PerformCalibrationAnalysis((const char*) G__int(libp->para[0]), *(vector<double>*) libp->para[1].ref
, (int) G__int(libp->para[2]), *(vector<double>*) libp->para[3].ref));
      break;
   }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_10(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   switch (libp->paran) {
   case 2:
      {
         vector<TH1D>* pobj;
         vector<TH1D> xobj = ((BCMTFAnalysisFacility*) G__getstructoffset())->BuildEnsemble(*(vector<double>*) libp->para[0].ref, *((string*) G__int(libp->para[1])));
         pobj = new vector<TH1D>(xobj);
         result7->obj.i = (long) ((void*) pobj);
         result7->ref = result7->obj.i;
         G__store_tempobject(*result7);
      }
      break;
   case 1:
      {
         vector<TH1D>* pobj;
         vector<TH1D> xobj = ((BCMTFAnalysisFacility*) G__getstructoffset())->BuildEnsemble(*(vector<double>*) libp->para[0].ref);
         pobj = new vector<TH1D>(xobj);
         result7->obj.i = (long) ((void*) pobj);
         result7->ref = result7->obj.i;
         G__store_tempobject(*result7);
      }
      break;
   }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_11(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   switch (libp->paran) {
   case 3:
      G__letint(result7, 85, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->BuildEnsembles(*(vector<double>*) libp->para[0].ref, (int) G__int(libp->para[1])
, *((string*) G__int(libp->para[2]))));
      break;
   case 2:
      G__letint(result7, 85, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->BuildEnsembles(*(vector<double>*) libp->para[0].ref, (int) G__int(libp->para[1])));
      break;
   }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_12(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   switch (libp->paran) {
   case 3:
      G__letint(result7, 85, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->BuildEnsembles((TTree*) G__int(libp->para[0]), (int) G__int(libp->para[1])
, *((string*) G__int(libp->para[2]))));
      break;
   case 2:
      G__letint(result7, 85, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->BuildEnsembles((TTree*) G__int(libp->para[0]), (int) G__int(libp->para[1])));
      break;
   }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_13(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   switch (libp->paran) {
   case 3:
      G__letint(result7, 85, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->PerformEnsembleTest(*(vector<double>*) libp->para[0].ref, (int) G__int(libp->para[1])
, *((string*) G__int(libp->para[2]))));
      break;
   case 2:
      G__letint(result7, 85, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->PerformEnsembleTest(*(vector<double>*) libp->para[0].ref, (int) G__int(libp->para[1])));
      break;
   }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_14(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   switch (libp->paran) {
   case 4:
      G__letint(result7, 85, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->PerformEnsembleTest((TTree*) G__int(libp->para[0]), (int) G__int(libp->para[1])
, (int) G__int(libp->para[2]), *((string*) G__int(libp->para[3]))));
      break;
   case 3:
      G__letint(result7, 85, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->PerformEnsembleTest((TTree*) G__int(libp->para[0]), (int) G__int(libp->para[1])
, (int) G__int(libp->para[2])));
      break;
   case 2:
      G__letint(result7, 85, (long) ((BCMTFAnalysisFacility*) G__getstructoffset())->PerformEnsembleTest((TTree*) G__int(libp->para[0]), (int) G__int(libp->para[1])));
      break;
   }
   return(1 || funcname || hash || result7 || libp) ;
}

static int G__BCMTFAnalysisFacilityDict_221_0_15(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
      {
         vector<TH1D>* pobj;
         vector<TH1D> xobj = ((BCMTFAnalysisFacility*) G__getstructoffset())->MatrixToHistograms(*(vector<std::vector<double> >*) libp->para[0].ref);
         pobj = new vector<TH1D>(xobj);
         result7->obj.i = (long) ((void*) pobj);
         result7->ref = result7->obj.i;
         G__store_tempobject(*result7);
      }
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic copy constructor
static int G__BCMTFAnalysisFacilityDict_221_0_16(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)

{
   BCMTFAnalysisFacility* p;
   void* tmp = (void*) G__int(libp->para[0]);
   p = new BCMTFAnalysisFacility(*(BCMTFAnalysisFacility*) tmp);
   result7->obj.i = (long) p;
   result7->ref = (long) p;
   G__set_tagnum(result7,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_BCMTFAnalysisFacility));
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic destructor
typedef BCMTFAnalysisFacility G__TBCMTFAnalysisFacility;
static int G__BCMTFAnalysisFacilityDict_221_0_17(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
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
       delete[] (BCMTFAnalysisFacility*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       for (int i = n - 1; i >= 0; --i) {
         ((BCMTFAnalysisFacility*) (soff+(sizeof(BCMTFAnalysisFacility)*i)))->~G__TBCMTFAnalysisFacility();
       }
       G__setgvp((long)gvp);
     }
   } else {
     if (gvp == (char*)G__PVOID) {
       delete (BCMTFAnalysisFacility*) soff;
     } else {
       G__setgvp((long) G__PVOID);
       ((BCMTFAnalysisFacility*) (soff))->~G__TBCMTFAnalysisFacility();
       G__setgvp((long)gvp);
     }
   }
   G__setnull(result7);
   return(1 || funcname || hash || result7 || libp) ;
}

// automatic assignment operator
static int G__BCMTFAnalysisFacilityDict_221_0_18(G__value* result7, G__CONST char* funcname, struct G__param* libp, int hash)
{
   BCMTFAnalysisFacility* dest = (BCMTFAnalysisFacility*) G__getstructoffset();
   *dest = *(BCMTFAnalysisFacility*) libp->para[0].ref;
   const BCMTFAnalysisFacility& obj = *dest;
   result7->ref = (long) (&obj);
   result7->obj.i = (long) (&obj);
   return(1 || funcname || hash || result7 || libp) ;
}


/* Setting up global function */

/*********************************************************
* Member function Stub
*********************************************************/

/* BCMTFAnalysisFacility */

/*********************************************************
* Global function Stub
*********************************************************/

/*********************************************************
* Get size of pointer to member function
*********************************************************/
class G__Sizep2memfuncBCMTFAnalysisFacilityDict {
 public:
  G__Sizep2memfuncBCMTFAnalysisFacilityDict(): p(&G__Sizep2memfuncBCMTFAnalysisFacilityDict::sizep2memfunc) {}
    size_t sizep2memfunc() { return(sizeof(p)); }
  private:
    size_t (G__Sizep2memfuncBCMTFAnalysisFacilityDict::*p)();
};

size_t G__get_sizep2memfuncBCMTFAnalysisFacilityDict()
{
  G__Sizep2memfuncBCMTFAnalysisFacilityDict a;
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
extern "C" void G__cpp_setup_inheritanceBCMTFAnalysisFacilityDict() {

   /* Setting up class inheritance */
}

/*********************************************************
* typedef information setup/
*********************************************************/
extern "C" void G__cpp_setup_typetableBCMTFAnalysisFacilityDict() {

   /* Setting up typedef entry */
   G__search_typename2("vector<ROOT::TSchemaHelper>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TVirtualArray*>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Float_t>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_TVectorTlEfloatgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("TVectorT<Double_t>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_TVectorTlEdoublegR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<TH1D>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlETH1DcOallocatorlETH1DgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlETH1DcOallocatorlETH1DgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlETH1DcOallocatorlETH1DgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlETH1DcOallocatorlETH1DgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlETH1DcOallocatorlETH1DgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<std::vector<double> >",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<vector<double> >",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<const_iterator>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("reverse_iterator<iterator>",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgRcLcLiteratorgR),0,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgR));
   G__setnewtype(-1,NULL,0);
   G__search_typename2("vector<vector<double,allocator<double> > >",117,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgR),0,-1);
   G__setnewtype(-1,NULL,0);
}

/*********************************************************
* Data Member information setup/
*********************************************************/

   /* Setting up class,struct,union tag member variable */

   /* BCMTFAnalysisFacility */
static void G__setup_memvarBCMTFAnalysisFacility(void) {
   G__tag_memvar_setup(G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_BCMTFAnalysisFacility));
   { BCMTFAnalysisFacility *p; p=(BCMTFAnalysisFacility*)0x1000; if (p) { }
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_BCMTF),-1,-1,4,"fMTF=",0,(char*)NULL);
   G__memvar_setup((void*)0,85,0,0,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_TRandom3),-1,-1,4,"fRandom=",0,(char*)NULL);
   G__memvar_setup((void*)0,103,0,0,-1,-1,-1,4,"fFlagMarginalize=",0,(char*)NULL);
   G__memvar_setup((void*)0,105,0,0,G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_BCLogcLcLLogLevel),-1,-1,4,"fLogLevel=",0,(char*)NULL);
   }
   G__tag_memvar_reset();
}

extern "C" void G__cpp_setup_memvarBCMTFAnalysisFacilityDict() {
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
static void G__setup_memfuncBCMTFAnalysisFacility(void) {
   /* BCMTFAnalysisFacility */
   G__tag_memfunc_setup(G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_BCMTFAnalysisFacility));
   G__memfunc_setup("BCMTFAnalysisFacility",2021,G__BCMTFAnalysisFacilityDict_221_0_1, 105, G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_BCMTFAnalysisFacility), -1, 0, 1, 1, 1, 0, "U 'BCMTF' - 0 - mtf", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetBCMTF",652,G__BCMTFAnalysisFacilityDict_221_0_2, 85, G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_BCMTF), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetBCMTF",664,G__BCMTFAnalysisFacilityDict_221_0_3, 121, -1, -1, 0, 1, 1, 1, 0, "U 'BCMTF' - 0 - mtf", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetFlagMarginalize",1817,G__BCMTFAnalysisFacilityDict_221_0_4, 121, -1, -1, 0, 1, 1, 1, 0, "g - - 0 - flag", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("GetLogLevel",1082,G__BCMTFAnalysisFacilityDict_221_0_5, 105, G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_BCLogcLcLLogLevel), -1, 0, 0, 1, 1, 0, "", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("SetLogLevel",1094,G__BCMTFAnalysisFacilityDict_221_0_6, 121, -1, -1, 0, 1, 1, 1, 0, "i 'BCLog::LogLevel' - 0 - level", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("PerformSingleChannelAnalyses",2870,G__BCMTFAnalysisFacilityDict_221_0_7, 105, -1, -1, 0, 2, 1, 1, 0, 
"C - - 10 - dirname C - - 10 '\"\"' options", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("PerformSingleSystematicAnalyses",3235,G__BCMTFAnalysisFacilityDict_221_0_8, 105, -1, -1, 0, 2, 1, 1, 0, 
"C - - 10 - dirname C - - 10 '\"\"' options", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("PerformCalibrationAnalysis",2695,G__BCMTFAnalysisFacilityDict_221_0_9, 105, -1, -1, 0, 5, 1, 1, 0, 
"C - - 10 - dirname u 'vector<double,allocator<double> >' 'vector<double>' 11 - default_parameters "
"i - - 0 - index u 'vector<double,allocator<double> >' 'vector<double>' 11 - parametervalues "
"i - - 0 '1000' nensembles", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("BuildEnsemble",1307,G__BCMTFAnalysisFacilityDict_221_0_10, 117, G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlETH1DcOallocatorlETH1DgRsPgR), G__defined_typename("vector<TH1D>"), 0, 2, 1, 1, 0, 
"u 'vector<double,allocator<double> >' 'vector<double>' 11 - parameters u 'string' - 0 '\"\"' options", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("BuildEnsembles",1422,G__BCMTFAnalysisFacilityDict_221_0_11, 85, G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_TTree), -1, 0, 3, 1, 1, 0, 
"u 'vector<double,allocator<double> >' 'vector<double>' 11 - parameters i - - 0 - nensembles "
"u 'string' - 0 '\"\"' options", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("BuildEnsembles",1422,G__BCMTFAnalysisFacilityDict_221_0_12, 85, G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_TTree), -1, 0, 3, 1, 1, 0, 
"U 'TTree' - 0 - tree i - - 0 - nensembles "
"u 'string' - 0 '\"\"' options", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("PerformEnsembleTest",1958,G__BCMTFAnalysisFacilityDict_221_0_13, 85, G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_TTree), -1, 0, 3, 1, 1, 0, 
"u 'vector<double,allocator<double> >' 'vector<double>' 11 - parameters i - - 0 - nensembles "
"u 'string' - 0 '\"\"' options", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("PerformEnsembleTest",1958,G__BCMTFAnalysisFacilityDict_221_0_14, 85, G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_TTree), -1, 0, 4, 1, 1, 0, 
"U 'TTree' - 0 - tree i - - 0 - nensembles "
"i - - 0 '0' start u 'string' - 0 '\"\"' options", (char*)NULL, (void*) NULL, 0);
   G__memfunc_setup("MatrixToHistograms",1881,G__BCMTFAnalysisFacilityDict_221_0_15, 117, G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_vectorlETH1DcOallocatorlETH1DgRsPgR), G__defined_typename("vector<TH1D>"), 0, 1, 1, 1, 0, "u 'vector<vector<double,allocator<double> >,allocator<vector<double,allocator<double> > > >' 'vector<std::vector<double> >' 11 - matrix", (char*)NULL, (void*) NULL, 0);
   // automatic copy constructor
   G__memfunc_setup("BCMTFAnalysisFacility", 2021, G__BCMTFAnalysisFacilityDict_221_0_16, (int) ('i'), 
G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_BCMTFAnalysisFacility), -1, 0, 1, 1, 1, 0, "u 'BCMTFAnalysisFacility' - 11 - -", (char*) NULL, (void*) NULL, 0);
   // automatic destructor
   G__memfunc_setup("~BCMTFAnalysisFacility", 2147, G__BCMTFAnalysisFacilityDict_221_0_17, (int) ('y'), -1, -1, 0, 0, 1, 1, 0, "", (char*) NULL, (void*) NULL, 0);
   // automatic assignment operator
   G__memfunc_setup("operator=", 937, G__BCMTFAnalysisFacilityDict_221_0_18, (int) ('u'), G__get_linked_tagnum(&G__BCMTFAnalysisFacilityDictLN_BCMTFAnalysisFacility), -1, 1, 1, 1, 1, 0, "u 'BCMTFAnalysisFacility' - 11 - -", (char*) NULL, (void*) NULL, 0);
   G__tag_memfunc_reset();
}


/*********************************************************
* Member function information setup
*********************************************************/
extern "C" void G__cpp_setup_memfuncBCMTFAnalysisFacilityDict() {
}

/*********************************************************
* Global variable information setup for each class
*********************************************************/
static void G__cpp_setup_global0() {

   /* Setting up global variables */
   G__resetplocal();

}

static void G__cpp_setup_global1() {
}

static void G__cpp_setup_global2() {

   G__resetglobalenv();
}
extern "C" void G__cpp_setup_globalBCMTFAnalysisFacilityDict() {
  G__cpp_setup_global0();
  G__cpp_setup_global1();
  G__cpp_setup_global2();
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
}

static void G__cpp_setup_func22() {
}

static void G__cpp_setup_func23() {
}

static void G__cpp_setup_func24() {

   G__resetifuncposition();
}

extern "C" void G__cpp_setup_funcBCMTFAnalysisFacilityDict() {
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
  G__cpp_setup_func22();
  G__cpp_setup_func23();
  G__cpp_setup_func24();
}

/*********************************************************
* Class,struct,union,enum tag information setup
*********************************************************/
/* Setup class/struct taginfo */
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR = { "vector<double,allocator<double> >" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_string = { "string" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR = { "vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR = { "reverse_iterator<vector<ROOT::TSchemaHelper,allocator<ROOT::TSchemaHelper> >::iterator>" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR = { "vector<TVirtualArray*,allocator<TVirtualArray*> >" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TVirtualArray*,allocator<TVirtualArray*> >::iterator>" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_TVectorTlEfloatgR = { "TVectorT<float>" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_TVectorTlEdoublegR = { "TVectorT<double>" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_BCLog = { "BCLog" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_BCLogcLcLLogLevel = { "BCLog::LogLevel" , 101 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_BCMTF = { "BCMTF" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_TTree = { "TTree" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_TRandom3 = { "TRandom3" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_BCMTFAnalysisFacility = { "BCMTFAnalysisFacility" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_vectorlETH1DcOallocatorlETH1DgRsPgR = { "vector<TH1D,allocator<TH1D> >" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlETH1DcOallocatorlETH1DgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<TH1D,allocator<TH1D> >::iterator>" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_vectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgR = { "vector<vector<double,allocator<double> >,allocator<vector<double,allocator<double> > > >" , 99 , -1 };
G__linked_taginfo G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgRcLcLiteratorgR = { "reverse_iterator<vector<vector<double,allocator<double> >,allocator<vector<double,allocator<double> > > >::iterator>" , 99 , -1 };

/* Reset class/struct taginfo */
extern "C" void G__cpp_reset_tagtableBCMTFAnalysisFacilityDict() {
  G__BCMTFAnalysisFacilityDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_string.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_TVectorTlEfloatgR.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_TVectorTlEdoublegR.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_BCLog.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_BCLogcLcLLogLevel.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_BCMTF.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_TTree.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_TRandom3.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_BCMTFAnalysisFacility.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_vectorlETH1DcOallocatorlETH1DgRsPgR.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlETH1DcOallocatorlETH1DgRsPgRcLcLiteratorgR.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_vectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgR.tagnum = -1 ;
  G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgRcLcLiteratorgR.tagnum = -1 ;
}


extern "C" void G__cpp_setup_tagtableBCMTFAnalysisFacilityDict() {

   /* Setting up class,struct,union tag entry */
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_vectorlEdoublecOallocatorlEdoublegRsPgR);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_string);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_vectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgR);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlEROOTcLcLTSchemaHelpercOallocatorlEROOTcLcLTSchemaHelpergRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_vectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgR);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlETVirtualArraymUcOallocatorlETVirtualArraymUgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_TVectorTlEfloatgR);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_TVectorTlEdoublegR);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_BCLog);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_BCLogcLcLLogLevel);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_BCMTF);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_TTree);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_TRandom3);
   G__tagtable_setup(G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_BCMTFAnalysisFacility),sizeof(BCMTFAnalysisFacility),-1,33792,(char*)NULL,G__setup_memvarBCMTFAnalysisFacility,G__setup_memfuncBCMTFAnalysisFacility);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_vectorlETH1DcOallocatorlETH1DgRsPgR);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlETH1DcOallocatorlETH1DgRsPgRcLcLiteratorgR);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_vectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgR);
   G__get_linked_tagnum_fwd(&G__BCMTFAnalysisFacilityDictLN_reverse_iteratorlEvectorlEvectorlEdoublecOallocatorlEdoublegRsPgRcOallocatorlEvectorlEdoublecOallocatorlEdoublegRsPgRsPgRsPgRcLcLiteratorgR);
}
extern "C" void G__cpp_setupBCMTFAnalysisFacilityDict(void) {
  G__check_setup_version(30051515,"G__cpp_setupBCMTFAnalysisFacilityDict()");
  G__set_cpp_environmentBCMTFAnalysisFacilityDict();
  G__cpp_setup_tagtableBCMTFAnalysisFacilityDict();

  G__cpp_setup_inheritanceBCMTFAnalysisFacilityDict();

  G__cpp_setup_typetableBCMTFAnalysisFacilityDict();

  G__cpp_setup_memvarBCMTFAnalysisFacilityDict();

  G__cpp_setup_memfuncBCMTFAnalysisFacilityDict();
  G__cpp_setup_globalBCMTFAnalysisFacilityDict();
  G__cpp_setup_funcBCMTFAnalysisFacilityDict();

   if(0==G__getsizep2memfunc()) G__get_sizep2memfuncBCMTFAnalysisFacilityDict();
  return;
}
class G__cpp_setup_initBCMTFAnalysisFacilityDict {
  public:
    G__cpp_setup_initBCMTFAnalysisFacilityDict() { G__add_setup_func("BCMTFAnalysisFacilityDict",(G__incsetup)(&G__cpp_setupBCMTFAnalysisFacilityDict)); G__call_setup_funcs(); }
   ~G__cpp_setup_initBCMTFAnalysisFacilityDict() { G__remove_setup_func("BCMTFAnalysisFacilityDict"); }
};
G__cpp_setup_initBCMTFAnalysisFacilityDict G__cpp_setup_initializerBCMTFAnalysisFacilityDict;
