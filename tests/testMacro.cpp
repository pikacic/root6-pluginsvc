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

#include "testMacro.h"

DECLARE_MY_FACTORY(Class1)
DECLARE_MY_FACTORY(Class2)

DECLARE_MY_FACTORY_WITH_ID(Class1, "1")
DECLARE_MY_FACTORY_WITH_ID(Class2, "2")
