// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME classDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
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
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "classEASIROCDisplay.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_EASIROCDisplay(void *p);
   static void deleteArray_EASIROCDisplay(void *p);
   static void destruct_EASIROCDisplay(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EASIROCDisplay*)
   {
      ::EASIROCDisplay *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EASIROCDisplay >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EASIROCDisplay", ::EASIROCDisplay::Class_Version(), "classEASIROCDisplay.h", 24,
                  typeid(::EASIROCDisplay), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EASIROCDisplay::Dictionary, isa_proxy, 4,
                  sizeof(::EASIROCDisplay) );
      instance.SetDelete(&delete_EASIROCDisplay);
      instance.SetDeleteArray(&deleteArray_EASIROCDisplay);
      instance.SetDestructor(&destruct_EASIROCDisplay);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EASIROCDisplay*)
   {
      return GenerateInitInstanceLocal((::EASIROCDisplay*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EASIROCDisplay*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr EASIROCDisplay::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EASIROCDisplay::Class_Name()
{
   return "EASIROCDisplay";
}

//______________________________________________________________________________
const char *EASIROCDisplay::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EASIROCDisplay*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EASIROCDisplay::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EASIROCDisplay*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EASIROCDisplay::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EASIROCDisplay*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EASIROCDisplay::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EASIROCDisplay*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void EASIROCDisplay::Streamer(TBuffer &R__b)
{
   // Stream an object of class EASIROCDisplay.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EASIROCDisplay::Class(),this);
   } else {
      R__b.WriteClassBuffer(EASIROCDisplay::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_EASIROCDisplay(void *p) {
      delete ((::EASIROCDisplay*)p);
   }
   static void deleteArray_EASIROCDisplay(void *p) {
      delete [] ((::EASIROCDisplay*)p);
   }
   static void destruct_EASIROCDisplay(void *p) {
      typedef ::EASIROCDisplay current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EASIROCDisplay

namespace {
  void TriggerDictionaryInitialization_classDict_Impl() {
    static const char* headers[] = {
"classEASIROCDisplay.h",
0
    };
    static const char* includePaths[] = {
"/Users/tomohisa/mySoft/root/root_v6.14.00.macosx64-10.13-clang91/include",
"/Users/tomohisa/mySoft/easiroc/class/testDisplay_v190721sub/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "classDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$classEASIROCDisplay.h")))  EASIROCDisplay;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "classDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "classEASIROCDisplay.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"EASIROCDisplay", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("classDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_classDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_classDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_classDict() {
  TriggerDictionaryInitialization_classDict_Impl();
}
