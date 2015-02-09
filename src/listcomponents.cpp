/*****************************************************************************\
* (c) Copyright 2013 CERN                                                     *
*                                                                             *
* This software is distributed under the terms of the GNU General Public      *
* Licence version 3 (GPL Version 3), copied verbatim in the file "LICENCE".   *
*                                                                             *
* In applying this licence, CERN does not waive the privileges and immunities *
* granted to it by virtue of its status as an Intergovernmental Organization  *
* or submit itself to any jurisdiction.                                       *
\*****************************************************************************/

/// @author Marco Clemencic <marco.clemencic@cern.ch>
/// @author Benedikt Hegner <benedikt.hegner@cern.ch>

#include <iostream>
#include <string>
#include <set>

#include <getopt.h>
#include <dlfcn.h>

#include <Gaudi/PluginService.h>

int main(int argc, char* argv[]) {
  auto& reg = Gaudi::PluginService::Details::Registry::instance();

  // cache to keep track of the loaded factories
  auto loaded = reg.loadedFactories();

  // loop over the list of libraries passed on the command line
  // and search for the not initially loaded ones
  for (int i = 1; i < argc; ++i) {
    if (dlopen(argv[i], RTLD_LAZY | RTLD_LOCAL)) {
      for(auto f : reg.loadedFactories() ){
        if (loaded.find(f) == loaded.end()) {
	  std::cout << argv[i] << ":" << f << std::endl;
        } else {
          auto& info = reg.getInfo(f);
          std::cerr << "WARNING: factory for '" << f << "already found in " << info.library << std::endl; 
        }
      }     
    } else {
      std::cerr << "ERROR: failed to load " << argv[i] << std::endl;
    }
  }
  return 0;
}
