#ifndef _PLUGIN_FACTORY_H_
#define _PLUGIN_FACTORY_H_

#ifdef __MAKECINT__

#define _PLUGINSVC_FACTORY_WITH_ID1(type, id, ret, arg1) \
   namespace __pf__ { \
      class Create##id { \
      public: \
        static ret call(arg1 A);                \
      }; \
   }
#define _PLUGINSVC_FACTORY_WITH_ID2(type, id, ret, arg1, arg2) \
   namespace __pf__ { \
      class Create##id { \
      public: \
        static ret call(arg1 A, arg2 B);                \
      }; \
   }

#else // __MAKECINT__

#define _PLUGINSVC_FACTORY_WITH_ID1(type, id, ret, arg1) \
   namespace __pf__ { \
      class Create##id { \
      public: \
        static ret call(arg1 A) { \
         return (ret) new type(A); \
        } \
      }; \
   }
#define _PLUGINSVC_FACTORY_WITH_ID2(type, id, ret, arg1, arg2) \
   namespace __pf__ { \
      class Create##id { \
      public: \
        static ret call(arg1 A, arg2 B) { \
          return (ret) new type(A, B);          \
        } \
      }; \
   }

#endif // __MAKECINT__

#define _PLUGINSVC_FACTORY1(type, ret, arg1) \
   _PLUGINSVC_FACTORY_WITH_ID1(type, type, ret, arg1)
#define _PLUGINSVC_FACTORY2(type, ret, arg1, arg2) \
   _PLUGINSVC_FACTORY_WITH_ID2(type, type, ret, arg1, arg2)

#define CALL1(A, B, ArgVal1) \
   (A)gROOT->ProcessLine(TString::Format("__pf__::Create%s::call(%s);", #B, #ArgVal1))
#define CALL2(A, B, ArgVal1, ArgVal2) \
   (A)gROOT->ProcessLine(TString::Format("__pf__::Create%s::call(%s, %s);", #B, #ArgVal1, #ArgVal2))

#endif //_PLUGIN_FACTORY_H
