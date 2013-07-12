#include "PluginService.h"

#include "TROOT.h"

#include "Cintex/Cintex.h"

namespace {
  class CintexEnabler {
  public:
    CintexEnabler() {
      ROOT::Cintex::Cintex::Enable();
    }
  } _enabler;
}

namespace PluginService {

  Exception::Exception(const std::string& msg): m_msg(msg) {}
  Exception::~Exception() throw() {}
  const char*  Exception::what() const throw() {
    return m_msg.c_str();
  }

  namespace Details {
    void* getCreator(const std::string& id) {
      void *ptr = (void*)gROOT->ProcessLine(
          TString::Format("__pf__::Create%s::creator();", id.c_str()));
      if (!ptr)
        throw Exception(std::string("cannot find factory ") + id);
      return ptr;
    }
  }
}
