#ifndef _TESTMACRO_H_
#define _TESTMACRO_H_

#include "Interfaces.h"
#include "PluginService.h"

#include <iostream>

class Class1: public MyInterface {
public:
   Class1(const std::string &name, std::string* shared): m_name(name), m_shared(shared) {}

   virtual ~Class1() {}

   virtual void theMethod() const {
      std::cout << "I'm Class1 instance called " << m_name.c_str()
                << " sharing " << *m_shared << std::endl;
   }

private:
   std::string m_name;
   std::string* m_shared;
};

class Class2: public MyInterface {
public:
   Class2(const std::string &name, std::string* shared): m_name(name), m_shared(shared) {}

   virtual ~Class2() {}

   virtual void theMethod() const {
      std::cout << "I'm Class2 instance called " << m_name.c_str()
                << " sharing " << *m_shared << std::endl;
   }

private:
   std::string m_name;
   std::string* m_shared;
};

#endif
