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

    void Registry::add(const std::string& id, void *factory){
      m_map[id] = factory;
    }

    void* Registry::get(const std::string& id) const {
      FactoryMap::const_iterator f = m_map.find(id);
      if (f != m_map.end())
      {
        return f->second;
      }
      else
      {
        // see if we can find a library providing that id
        std::string lib = locate(id);
        if (!lib.empty() && m_loadedLibs.find(lib) == m_loadedLibs.end())
        { // if there is one and we didn't load it yet, let's load it
          if (dlopen(lib.c_str(), RTLD_NOW | RTLD_LOCAL)) {
            // if we managed to load it, try again
            const_cast<Registry*>(this)->m_loadedLibs.insert(lib);
            return get(id);
          }
          else
          {
            // we could not load the library, so we give up
            return 0;
          }
        }
      }
      return 0; // factory not found
    }

    std::string Registry::locate(const std::string& id) const {
#warning "fake implementation for testing"
      return "libComponent.so";
    }
  }
}}
