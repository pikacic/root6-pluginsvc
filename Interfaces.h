#ifndef _INTERFACES_H_
#define _INTERFACES_H_

class MyInterface {
public:
   MyInterface() {}
   virtual ~MyInterface() {}

   virtual void theMethod() const = 0;
};

#include "PluginService.h"
#include <string>

typedef PluginService::FactorySignature2<MyInterface*,
                                         const std::string&, std::string*>
        MyFactorySignature;

#define DECLARE_MY_FACTORY(type) \
  DECLARE_FACTORY(type, MyFactorySignature)
#define DECLARE_MY_FACTORY_WITH_ID(id, type) \
  DECLARE_FACTORY_WITH_ID(id, type, MyFactorySignature)

#endif
