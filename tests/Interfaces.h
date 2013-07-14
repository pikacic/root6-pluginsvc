#ifndef _INTERFACES_H_
#define _INTERFACES_H_

class MyInterface {
public:
   MyInterface() {}
   virtual ~MyInterface() {}

   virtual void theMethod() const = 0;
};

#include <Gaudi/PluginService.h>
#include <string>

typedef Gaudi::PluginService::Factory2<MyInterface*,
                                       const std::string&, std::string*>
        MyFactory;

#define DECLARE_MY_FACTORY(type) \
  DECLARE_FACTORY(type, MyFactory)
#define DECLARE_MY_FACTORY_WITH_ID(type, id) \
  DECLARE_FACTORY_WITH_ID(type, id, MyFactory)

#endif
