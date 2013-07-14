// cl -nologo -Z7 -MDd -GR -EHsc testLoading.cxx -I %ROOTSYS%\include /link -debug -LIBPATH:%ROOTSYS%\lib libCore.lib

#include <memory>
#include <iostream>
#include <dlfcn.h>

#include <Gaudi/PluginService.h>
#include "Interfaces.h"

void call(MyInterface *p) {
   std::cout << std::showbase << std::hex << std::nouppercase << (unsigned long)p << std::endl;
   if (p) p->theMethod();
}

int main(int argc, char ** argv)
{
  dlopen("libComponent.so", RTLD_LAZY);

  std::string A("A");
  std::string B("B");

  std::cout << "Looking for classes..." << std::endl;
  std::auto_ptr<MyInterface> c1a( MyFactory::create("Class1", "c1a", &A) );
  std::auto_ptr<MyInterface> c2a( MyFactory::create("Class2", "c2a", &B) );
  call(c1a.get());
  call(c2a.get());

  std::cout << "Looking for IDs..." << std::endl;
  std::auto_ptr<MyInterface> c1b( MyFactory::create("1", "c1b", &B) );
  std::auto_ptr<MyInterface> c2b( MyFactory::create("2", "c2b", &A) );
  call(c1b.get());
  call(c2b.get());

  try {
    MyFactory::create("3", "c1b", &B);
  } catch (Gaudi::PluginService::Exception &e) {
    std::cout << "PluginService::Exception -> " << e.what() << std::endl;
  }

  std::cout << "Done!" << std::endl;
}
