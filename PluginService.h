#ifndef _PLUGIN_SERVICE_H_
#define _PLUGIN_SERVICE_H_

#include <string>

#define DECLARE_FACTORY_WITH_ID(id, type, signature) \
  namespace __pf__ { \
    class Create##id { \
    public: \
      typedef signature s_t; \
      typedef PluginService::Details::Factory<type> f_t; \
      static s_t::FuncType creator() { return &f_t::create<s_t>; } \
    }; \
  }

#define DECLARE_FACTORY(type, signature) \
  DECLARE_FACTORY_WITH_ID(type, type, signature)


namespace PluginService {

  /// Class wrapping the signature for a factory without arguments.
  template <typename R>
  class FactorySignature0 {
  public:
    typedef R  ReturnType;
    typedef R (*FuncType)();
  };

  /// Class wrapping the signature for a factory with 1 argument.
  template <typename R, typename A1>
  class FactorySignature1 {
  public:
    typedef R  ReturnType;
    typedef A1 Arg1Type;
    typedef R (*FuncType)(Arg1Type);
  };

  /// Class wrapping the signature for a factory with 2 arguments.
  template <typename R, typename A1, typename A2>
  class FactorySignature2 {
  public:
    typedef R  ReturnType;
    typedef A1 Arg1Type;
    typedef A2 Arg2Type;
    typedef R (*FuncType)(Arg1Type, Arg2Type);
  };

  /// Internal na
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

  /// Entry point to the factories.
  ///
  /// Example:,
  /// @code{
  ///
  ///   typedef PluginService::FactorySignature1<Interface*, std::string>
  ///           MySignature;
  ///   PluginSvc::Factory::create<MySignature>("factory_id")("argument");
  ///
  /// @}
  class Factory {
  public:

    template <typename S>
    static typename S::ReturnType create(const std::string& id) {
      return (*(typename S::FuncType)Details::getCreator(id))();
    }

    template <typename S>
    static typename S::ReturnType create(const std::string& id,
                                         typename S::Arg1Type a1) {
      return (*(typename S::FuncType)Details::getCreator(id))(a1);
    }

    template <typename S>
    static typename S::ReturnType create(const std::string& id,
                                         typename S::Arg1Type a1,
                                         typename S::Arg2Type a2) {
      return (*(typename S::FuncType)Details::getCreator(id))(a1, a2);
    }

  };

}

#endif //_PLUGIN_FACTORY_H
