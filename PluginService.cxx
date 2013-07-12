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
  namespace Details {
    void* getCreator(const std::string& id) {
      return (void*)gROOT->ProcessLine(
          TString::Format("__pf__::Create%s::creator();", id.c_str()));
    }
  }
}
