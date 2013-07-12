#include "PluginService.h"

namespace PluginService {

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
  }

  Registry& Registry::instance() {
    static Registry r;
    return r;
  }

  void Registry::add(const std::string& id, void *factory){
    m_map[id] = factory;
  }

  void* Registry::get(const std::string& id) {
    return m_map[id];
  }
}
