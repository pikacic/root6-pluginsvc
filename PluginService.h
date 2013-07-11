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

#include <string>

namespace PluginService {
  void* getFactory(const std::string& id);

    template <class R, class A1>
    R make(const std::string id, A1 a1) {
      typedef R (*factory_t)(A1);
      factory_t f = (factory_t)getFactory(id);
      return (*f)(a1);
    }

    template <class R, class A1, class A2>
    R make(const std::string id, A1 a1, A2 a2) {
      typedef R (*factory_t)(A1, A2);
      factory_t f = (factory_t)getFactory(id);
      return (*f)(a1, a2);
    }
}

#endif //_PLUGIN_FACTORY_H
