#ifndef _PLUGIN_SERVICE_H_
#define _PLUGIN_SERVICE_H_

#include <string>
#include <map>

#define PLUGINSVC_CNAME(name, serial) _register_ ## name ## _ ## serial

#define DECLARE_FACTORY_WITH_ID(type, id, factory) _DECLARE_FACTORY_INTERNAL(type, id, factory, __LINE__)

#define _DECLARE_FACTORY_INTERNAL(type, id, factory, serial) \
  namespace { \
    class PLUGINSVC_CNAME(type, serial) { \
    public: \
      typedef factory s_t; \
      typedef PluginService::Details::Factory<type> f_t; \
      static s_t::FuncType creator() { return &f_t::create<s_t>; } \
      PLUGINSVC_CNAME(type, serial) () { \
        PluginService::Registry::instance().add(id, (void*)creator()); \
      } \
    } PLUGINSVC_CNAME(s_ ## type, serial); \
  }

#define DECLARE_FACTORY(type, factory) \
  DECLARE_FACTORY_WITH_ID(type, #type, factory)


namespace PluginService {

  namespace Details {
    /// Class providing default factory functions.
    ///
    /// The template argument T is the class to be created, while the methods
    /// template argument S is the specific factory signature.
    template <class T>
    class Factory {
    public:

      template <typename S>
      static typename S::ReturnType create() {
        return new T();
      }

      template <typename S>
      static typename S::ReturnType create(typename S::Arg1Type a1) {
        return new T(a1);
      }

      template <typename S>
      static typename S::ReturnType create(typename S::Arg1Type a1,
                                           typename S::Arg2Type a2) {
        return new T(a1, a2);
      }

    };

    /// Function used to load a specific factory function.
    /// @return the pointer to the factory function.
    void* getCreator(const std::string& id);
  }

  /// Class wrapping the signature for a factory without arguments.
  template <typename R>
  class Factory0 {
  public:
    typedef R  ReturnType;
    typedef R (*FuncType)();

    static ReturnType create(const std::string& id) {
      return (*(FuncType)Details::getCreator(id))();
    }
  };

  /// Class wrapping the signature for a factory with 1 argument.
  template <typename R, typename A1>
  class Factory1 {
  public:
    typedef R  ReturnType;
    typedef A1 Arg1Type;
    typedef R (*FuncType)(Arg1Type);

    static ReturnType create(const std::string& id,
                             Arg1Type a1) {
      return (*(FuncType)Details::getCreator(id))(a1);
    }
  };

  /// Class wrapping the signature for a factory with 2 arguments.
  template <typename R, typename A1, typename A2>
  class Factory2 {
  public:
    typedef R  ReturnType;
    typedef A1 Arg1Type;
    typedef A2 Arg2Type;
    typedef R (*FuncType)(Arg1Type, Arg2Type);

    static ReturnType create(const std::string& id,
                             Arg1Type a1,
                             Arg2Type a2) {
      return (*(FuncType)Details::getCreator(id))(a1, a2);
    }
  };

  class Exception: public std::exception {
  public:
    Exception(const std::string& msg);
    virtual ~Exception() throw();
    virtual const char* what() const throw();
  private:
    std::string m_msg;
  };

  class Registry {
  public:
    typedef std::map<std::string, void*> FactoryMap;

    static Registry& instance();

    void add(const std::string& id, void *factory);

    void* get(const std::string& id);

  private:
    Registry() {}

    FactoryMap m_map;
  };
}

#endif //_PLUGIN_FACTORY_H
