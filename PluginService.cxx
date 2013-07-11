#include "PluginService.h"

#include "TROOT.h"

namespace PluginService {
  void* getFactory(const std::string& id) {
    return (void*)gROOT->ProcessLine(TString::Format("__pf__::Create%s::call;", id.c_str()));
  }
}
