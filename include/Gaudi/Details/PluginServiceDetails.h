#ifndef _GAUDI_PLUGIN_SERVICE_DETAILS_H_
#define _GAUDI_PLUGIN_SERVICE_DETAILS_H_

#include <string>
#include <map>
#include <set>

namespace Gaudi { namespace PluginService {

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

    /// In-memory database of the loaded factories.
    class Registry {
    public:
      /// Type used for the database implementation.
      typedef std::map<std::string, void*> FactoryMap;

      /// Retrieve the singleton instance of Registry.
      static Registry& instance();

      /// Add a factory to the database.
      void add(const std::string& id, void *factory);

      /// Retrieve the factory for the given id.
      void* get(const std::string& id) const;

      /// Return a list of all the known factories
      std::set<FactoryMap::key_type> knownFactories() const;

    private:
      /// Private constructor for the singleton pattern.
      Registry() {}

      /// Find the library providing a given factory and returns it's name.
      std::string locate(const std::string& id) const;

      /// Internal storage for factories.
      FactoryMap m_map;

      /// List of libraries already loaded.
      /// Needed to avoid infinite loops if a library declares to have a factory
      /// but it is not true.
      std::set<std::string> m_loadedLibs;

    };
  }
}}

#define _INTERNAL_FACTORY_REGISTER_CNAME(name, serial) \
  _register_ ## name ## _ ## serial

#define _INTERNAL_DECLARE_FACTORY(type, id, factory, serial) \
  namespace { \
    class _INTERNAL_FACTORY_REGISTER_CNAME(type, serial) { \
    public: \
      typedef factory s_t; \
      typedef Gaudi::PluginService::Details::Factory<type> f_t; \
      static s_t::FuncType creator() { return &f_t::create<s_t>; } \
      _INTERNAL_FACTORY_REGISTER_CNAME(type, serial) () { \
        Gaudi::PluginService::Details::Registry::instance().add(id, \
            (void*)creator()); \
      } \
    } _INTERNAL_FACTORY_REGISTER_CNAME(s_ ## type, serial); \
  }

#endif //_GAUDI_PLUGIN_SERVICE_DETAILS_H_
