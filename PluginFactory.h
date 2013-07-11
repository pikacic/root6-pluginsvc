#ifndef _PLUGIN_FACTORY_H_
#define _PLUGIN_FACTORY_H_

#ifdef __MAKECINT__
#define _PLUGINSVC_FACTORY_WITH_ID1(type, id, ret, arg1) \
   namespace __pf__ { \
      ret Create##id(arg1 A); \
   }
#define _PLUGINSVC_FACTORY_WITH_ID2(type, id, ret, arg1, arg2) \
   namespace __pf__ { \
      ret Create##id(arg1 A, arg2 B); \
      } \
   }
#define _PLUGINSVC_FACTORY_WITH_ID3(type, id, ret, arg1, arg2, arg3) \
   namespace __pf__ { \
      ret Create##id(arg1 A, arg2 B, arg3 C); \
      } \
   }
#define _PLUGINSVC_FACTORY_WITH_ID4(type, id, ret, arg1, arg2, arg3, arg4) \
   namespace __pf__ { \
      ret Create##id(arg1 A, arg2 B, arg3 C, arg4 D); \
      } \
   }
#define _PLUGINSVC_FACTORY_WITH_ID4(type, id, ret, arg1, arg2, arg3, arg4) \
   namespace __pf__ { \
      ret Create##id(arg1 A, arg2 B, arg3 C, arg4 D); \
      } \
   }
#define _PLUGINSVC_FACTORY_WITH_ID5(type, id, ret, arg1, arg2, arg3, arg4, arg5) \
   namespace __pf__ { \
      ret Create##id(arg1 A, arg2 B, arg3 C, arg4 D, arg5 E); \
      } \
   }
#else // __MAKECINT__
#define _PLUGINSVC_FACTORY_WITH_ID1(type, id, ret, arg1) \
   namespace __pf__ { \
      ret Create##id(arg1 A) { \
         return (ret) new type(A); \
      } \
   }
#define _PLUGINSVC_FACTORY_WITH_ID2(type, id, ret, arg1, arg2) \
   namespace __pf__ { \
      ret Create##id(arg1 A, arg2 B) { \
         return (ret) new type(A, B); \
      } \
   }
#define _PLUGINSVC_FACTORY_WITH_ID3(type, id, ret, arg1, arg2, arg3) \
   namespace __pf__ { \
      ret Create##id(arg1 A, arg2 B, arg3 C) { \
         return (ret) new type(A, B, C); \
      } \
   }
#define _PLUGINSVC_FACTORY_WITH_ID4(type, id, ret, arg1, arg2, arg3, arg4) \
   namespace __pf__ { \
      ret Create##id(arg1 A, arg2 B, arg3 C, arg4 D) { \
         return (ret) new type(A, B, C, D); \
      } \
   }
#define _PLUGINSVC_FACTORY_WITH_ID4(type, id, ret, arg1, arg2, arg3, arg4) \
   namespace __pf__ { \
      ret Create##id(arg1 A, arg2 B, arg3 C, arg4 D) { \
         return (ret) new type(A, B, C, D); \
      } \
   }
#define _PLUGINSVC_FACTORY_WITH_ID5(type, id, ret, arg1, arg2, arg3, arg4, arg5) \
   namespace __pf__ { \
      ret Create##id(arg1 A, arg2 B, arg3 C, arg4 D, arg5 E) { \
         return (ret) new type(A, B, C, D, E); \
      } \
   }
#endif // __MAKECINT__

#define _PLUGINSVC_FACTORY1(type, ret, arg1) \
   _PLUGINSVC_FACTORY_WITH_ID1(type, type, ret, arg1)
#define _PLUGINSVC_FACTORY2(type, ret, arg1, arg2) \
   _PLUGINSVC_FACTORY_WITH_ID2(type, type, ret, arg1, arg2)
#define _PLUGINSVC_FACTORY3(type, ret, arg1, arg2, arg3) \
   _PLUGINSVC_FACTORY_WITH_ID3(type, type, ret, arg1, arg2, arg3)
#define _PLUGINSVC_FACTORY4(type, ret, arg1, arg2, arg3, arg4) \
   _PLUGINSVC_FACTORY_WITH_ID4(type, type, ret, arg1, arg2, arg3, arg4)
#define _PLUGINSVC_FACTORY5(type, ret, arg1, arg2, arg3, arg4, arg5) \
   _PLUGINSVC_FACTORY_WITH_ID5(type, type, ret, arg1, arg2, arg3, arg4, arg5)

#define CALL1(A, B, ArgVal1) \
   (A)gROOT->ProcessLine(TString::Format("__pf__::Create%s(%s);", #B, #ArgVal1))
#define CALL2(A, B, ArgVal1, ArgVal2) \
   (A)gROOT->ProcessLine(TString::Format("__pf__::Create%s(%s, %s);", #B, #ArgVal1, #ArgVal2))
#define CALL3(A, B, ArgVal1, ArgVal2, ArgVal3) \
   (A)gROOT->ProcessLine(TString::Format("__pf__::Create%s(%s, %s, %s);", #B, #ArgVal1, #ArgVal2, #ArgVal3))
#define CALL4(A, B, ArgVal1, ArgVal2, ArgVal3, ArgVal4) \
   (A)gROOT->ProcessLine(TString::Format("__pf__::Create%s(%s, %s, %s, %s);", #B, #ArgVal1, #ArgVal2, #ArgVal3, #ArgVal4))
#define CALL5(A, B, ArgVal1, ArgVal2, ArgVal3, ArgVal4, ArgVal5) \
   (A)gROOT->ProcessLine(TString::Format("__pf__::Create%s(%s, %s, %s, %s, %s);", #B, #ArgVal1, #ArgVal2, #ArgVal3, #ArgVal4, #ArgVal5))

#endif //_PLUGIN_FACTORY_H
