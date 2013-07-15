#include <Gaudi/PluginService.h>

#include <dlfcn.h>

namespace Gaudi { namespace PluginService {

  Exception::Exception(const std::string& msg): m_msg(msg) {}
  Exception::~Exception() throw() {}
  const char*  Exception::what() const throw() {
    return m_msg.c_str();
  }

  namespace Details {
    void* getCreator(const std::string& id) {
      void *ptr = Registry::instance().get(id);
      if (!ptr)
        throw Exception(std::string("cannot find factory ") + id);
      return ptr;
    }

    Registry& Registry::instance() {
      static Registry r;
      return r;
    }

    Registry::Registry() {
#warning "fake implementation for testing"
      FactoryInfo fi("libComponent.so");
      m_factories.insert(std::make_pair(std::string("Class1"), fi));
      m_factories.insert(std::make_pair(std::string("Class2"), fi));
      m_factories.insert(std::make_pair(std::string("1"), fi));
      m_factories.insert(std::make_pair(std::string("2"), fi));
    }

    void Registry::add(const std::string& id, void *factory){
      FactoryMap::iterator entry = m_factories.find(id);
      if (entry == m_factories.end())
      {
        // this factory was not known yet
        m_factories.insert(std::make_pair(id, FactoryInfo("unknown", factory)));
      } else {
        entry->second.ptr = factory;
      }
    }

    void* Registry::get(const std::string& id) const {
      FactoryMap::const_iterator f = m_factories.find(id);
      if (f != m_factories.end())
      {
        if (!f->second.ptr) {
          if (!dlopen(f->second.library.c_str(), RTLD_NOW | RTLD_LOCAL)) {
            return 0;
          }
          f = m_factories.find(id); // ensure that the iterator is valid
        }
        return f->second.ptr;
      }
      return 0; // factory not found
    }

    std::set<Registry::KeyType> Registry::loadedFactories() const {
      std::set<KeyType> l;
      for (FactoryMap::const_iterator f = m_factories.begin();
           f != m_factories.end(); ++f)
      {
        if (f->second.ptr)
          l.insert(f->first);
      }
      return l;
    }

  }
}}
