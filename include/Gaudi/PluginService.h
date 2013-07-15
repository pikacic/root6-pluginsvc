#ifndef _GAUDI_PLUGIN_SERVICE_H_
#define _GAUDI_PLUGIN_SERVICE_H_
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

#include <string>
#include <Gaudi/Details/PluginServiceDetails.h>

#define DECLARE_FACTORY_WITH_ID(type, id, factory) \
  _INTERNAL_DECLARE_FACTORY(type, id, factory, __LINE__)

#define DECLARE_FACTORY(type, factory) \
  DECLARE_FACTORY_WITH_ID(type, #type, factory)

namespace Gaudi { namespace PluginService {

  /// Class wrapping the signature for a factory without arguments.
  template <typename R>
  class Factory0 {
  public:
    typedef R  ReturnType;
    typedef R (*FuncType)();

    static ReturnType create(const std::string& id) {
      return (*(FuncType)Details::getCreator(id))();
    }
  };

  /// Class wrapping the signature for a factory with 1 argument.
  template <typename R, typename A1>
  class Factory1 {
  public:
    typedef R  ReturnType;
    typedef A1 Arg1Type;
    typedef R (*FuncType)(Arg1Type);

    static ReturnType create(const std::string& id,
                             Arg1Type a1) {
      return (*(FuncType)Details::getCreator(id))(a1);
    }
  };

  /// Class wrapping the signature for a factory with 2 arguments.
  template <typename R, typename A1, typename A2>
  class Factory2 {
  public:
    typedef R  ReturnType;
    typedef A1 Arg1Type;
    typedef A2 Arg2Type;
    typedef R (*FuncType)(Arg1Type, Arg2Type);

    static ReturnType create(const std::string& id,
                             Arg1Type a1,
                             Arg2Type a2) {
      return (*(FuncType)Details::getCreator(id))(a1, a2);
    }
  };

  class Exception: public std::exception {
  public:
    Exception(const std::string& msg);
    virtual ~Exception() throw();
    virtual const char* what() const throw();
  private:
    std::string m_msg;
  };
}}

#endif //_GAUDI_PLUGIN_SERVICE_H_
