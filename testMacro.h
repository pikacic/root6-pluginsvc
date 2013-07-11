#ifndef _TESTMACRO_H_
#define _TESTMACRO_H_

#include "Riostream.h"
#include "Interfaces.h"
#include "PluginFactory.h"

class Class1: public MyInterface {
public:
   Class1(const std::string &name): m_name(name) {}
   virtual ~Class1() {}

   virtual void theMethod() const {
      std::cout << "I'm Class1 instance called " << m_name.c_str() << std::endl;
   }

private:
   std::string m_name;
};

class Class2: public MyInterface {
public:
   Class2(const std::string &name): m_name(name) {}

   virtual ~Class2() {}

   virtual void theMethod() const {
      std::cout << "I'm Class2 instance called " << m_name.c_str() << std::endl;
   }

private:
   std::string m_name;
};

#if defined(__MAKECINT__) || defined (G__DICTIONARY)
_PLUGINSVC_FACTORY1(Class1, MyInterface*, std::string);
_PLUGINSVC_FACTORY1(Class2, MyInterface*, std::string);

_PLUGINSVC_FACTORY_WITH_ID1(Class1, 1, MyInterface*, std::string);
_PLUGINSVC_FACTORY_WITH_ID1(Class2, 2, MyInterface*, std::string);
#endif

#endif
