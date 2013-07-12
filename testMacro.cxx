#include "testMacro.h"

//#if defined(__MAKECINT__) || defined (G__DICTIONARY)

DECLARE_MY_FACTORY(Class1)
DECLARE_MY_FACTORY(Class2)

DECLARE_MY_FACTORY_WITH_ID(1, Class1)
DECLARE_MY_FACTORY_WITH_ID(2, Class2)

//#endif
