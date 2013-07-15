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

#include <Gaudi/PluginService.h>

#include <dlfcn.h>
#include <dirent.h>

#include <cstdlib>
#include <iostream>
#include <fstream>

#ifdef NDEBUG
#define DEBUGMSG(x)
#else
#define DEBUGSTRM std::cerr << "PluginService:DEBUG: "
#define DEBUGMSG(x) DEBUGSTRM << x << std::endl;
#endif

namespace Gaudi { namespace PluginService {

  Exception::Exception(const std::string& msg): m_msg(msg) {}
  Exception::~Exception() throw() {}
  const char*  Exception::what() const throw() {
    return m_msg.c_str();
  }

  namespace Details {
    void* getCreator(const std::string& id) {
      void *ptr = Registry::instance().get(id);
      if (!ptr)
        throw Exception(std::string("cannot find factory ") + id);
      return ptr;
    }

    Registry& Registry::instance() {
      static Registry r;
      return r;
    }

    Registry::Registry() {
#ifdef WIN32
      const char* envVar = "PATH";
      const char sep = ';';
#else
      const char* envVar = "LD_LIBRARY_PATH";
      const char sep = ':';
#endif
      char *search_path = ::getenv(envVar);
      if (search_path) {
        DEBUGMSG((std::string("searching factories in ") + envVar))
        std::string path(search_path);
        std::string::size_type pos = 0;
        std::string::size_type newpos = 0;
        while (pos != std::string::npos) {
          std::string dirName;
          // get the next entry in the path
          newpos = path.find(sep, pos);
          if (newpos != std::string::npos) {
            dirName = path.substr(pos, newpos - pos);
            pos = newpos+1;
          } else {
            dirName = path.substr(pos);
            pos = newpos;
          }
          DEBUGMSG((std::string(" looking into ") + dirName))
          // look for files called "*.factories" in the directory
          DIR *dir = opendir(dirName.c_str());
          if (dir) {
            struct dirent * entry;
            while ((entry = readdir(dir))) {
              std::string name(entry->d_name);
              std::string::size_type extpos = name.find(".components");

              if ((extpos != std::string::npos) &&
                  ((extpos+11) == name.size()) &&
                  ((entry->d_type == DT_REG) || (entry->d_type == DT_LNK))) {
                DEBUGMSG((std::string("  reading ") + name))
                std::ifstream factories((dirName + '/' + name).c_str());
                std::string lib, fact;
#ifndef NDEBUG
                int factoriesCount = 0;
#endif
                while (!factories.eof()) {
                  std::getline(factories, lib, ':');
                  if (factories.fail()) break;
                  std::getline(factories, fact);
                  if (factories.fail()) break;
                  m_factories.insert(std::make_pair(fact, FactoryInfo(lib)));
#ifndef NDEBUG
                  ++factoriesCount;
#endif
                }
#ifndef NDEBUG
                DEBUGSTRM << "  found " << factoriesCount\
                          << " factories" << std::endl;
#endif
              }
            }
            closedir(dir);
          }
        }
      }
    }

    void Registry::add(const std::string& id, void *factory){
      FactoryMap::iterator entry = m_factories.find(id);
      if (entry == m_factories.end())
      {
        // this factory was not known yet
        m_factories.insert(std::make_pair(id, FactoryInfo("unknown", factory)));
      } else {
        entry->second.ptr = factory;
      }
    }

    void* Registry::get(const std::string& id) const {
      FactoryMap::const_iterator f = m_factories.find(id);
      if (f != m_factories.end())
      {
        if (!f->second.ptr) {
          if (!dlopen(f->second.library.c_str(), RTLD_NOW | RTLD_LOCAL)) {
            return 0;
          }
          f = m_factories.find(id); // ensure that the iterator is valid
        }
        return f->second.ptr;
      }
      return 0; // factory not found
    }

    std::set<Registry::KeyType> Registry::loadedFactories() const {
      std::set<KeyType> l;
      for (FactoryMap::const_iterator f = m_factories.begin();
           f != m_factories.end(); ++f)
      {
        if (f->second.ptr)
          l.insert(f->first);
      }
      return l;
    }

  }
}}
