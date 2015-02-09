PluginService 
=============

Basic plugin service for C++ classes

Quick Start
-----------

### How to define your own plugin

Create an interface class for your plugin:

    class MyPluginInterface { ... }

Define a factory for this plugin:

    #include <Gaudi/PluginService.h>
    #include <string>
    typedef Gaudi::PluginService::Factory<MyPluginInterface*, {constructor signature} > MyPluginFactory;

Simplify your life by defining a macro for plugin registration:

    #define REGISTER_MY_PLUGIN(type) \
      DECLARE_FACTORY(type, MyPluginFactory)

Create your concrete classes inheriting from the interface:

    class ConcretePlugin : public MyPluginInterface{ ... }

And announce it

    REGISTER_MY_PLUGIN(ConcretePlugin)

