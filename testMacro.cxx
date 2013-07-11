#include "testMacro.h"

#if defined(__MAKECINT__) || defined (G__DICTIONARY)
_PLUGINSVC_FACTORY2(Class1, MyInterface*, std::string, std::string*);
_PLUGINSVC_FACTORY2(Class2, MyInterface*, std::string, std::string*);

_PLUGINSVC_FACTORY_WITH_ID2(Class1, 1, MyInterface*, std::string, std::string*);
_PLUGINSVC_FACTORY_WITH_ID2(Class2, 2, MyInterface*, std::string, std::string*);
#endif
