#ifndef _TESTMACRO_H_
#define _TESTMACRO_H_

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

#include "Interfaces.h"
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
