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

#include <memory>
#include <iostream>

#include <Gaudi/PluginService.h>
#include "Interfaces.h"

void call(MyInterface *p) {
   std::cout << std::showbase << std::hex << std::nouppercase << (unsigned long)p << std::endl;
   if (p) p->theMethod();
}

int main(int argc, char ** argv)
{
  Gaudi::PluginService::Details::logger().setLevel(Gaudi::PluginService::Details::Logger::Debug);
  const auto& registry = Gaudi::PluginService::Details::Registry::instance();
  
  std::string A("A");
  std::string B("B");

  std::cout << "Looking for classes..." << std::endl;
  auto c1a = std::unique_ptr<MyInterface>( MyInterface::Factory::create("Class1", "c1a", &A) );
  auto c2a = std::unique_ptr<MyInterface>( MyInterface::Factory::create("Class2", "c2a", &B) );
  call(c1a.get());
  call(c2a.get());

  std::cout << "Looking for IDs..." << std::endl;
  auto c1b = std::unique_ptr<MyInterface>( MyInterface::Factory::create("1", "c1b", &B) );
  auto c2b = std::unique_ptr<MyInterface>( MyInterface::Factory::create("2", "c2b", &A) );
  call(c1b.get());
  call(c2b.get());

  try {
    MyInterface::Factory::create("3", "c1b", &B);
  } catch (Gaudi::PluginService::Exception &e) {
    std::cout << "PluginService::Exception -> " << e.what() << std::endl;
  }

  std::cout << "Done!" << std::endl;
}
