#ifndef _INTERFACES_H_
#define _INTERFACES_H_
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

class MyInterface {
public:
   MyInterface() {}
   virtual ~MyInterface() {}

   virtual void theMethod() const = 0;
};

#include <Gaudi/PluginService.h>
#include <string>

typedef Gaudi::PluginService::Factory<MyInterface*,
                                       const std::string&, std::string*>
        MyFactory;

#define DECLARE_MY_FACTORY(type) \
  DECLARE_FACTORY(type, MyFactory)
#define DECLARE_MY_FACTORY_WITH_ID(type, id) \
  DECLARE_FACTORY_WITH_ID(type, id, MyFactory)

#endif
