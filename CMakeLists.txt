cmake_minimum_required(VERSION 2.8)

include_directories(include)

set(CMAKE_BUILD_TYPE Release)

add_library(PluginService SHARED src/PluginService.cpp)
target_link_libraries(PluginService ${CMAKE_DL_LIBS})

add_executable(listfactories src/listfactories.cpp src/PluginService.cpp)
target_link_libraries(listfactories ${CMAKE_DL_LIBS})

add_custom_command(OUTPUT test.components
                   COMMAND listfactories libComponent.so > test.components
                   DEPENDS Component listfactories)
add_custom_target(FactoriesList ALL DEPENDS test.components)

add_library(Component MODULE tests/testMacro.cpp)
target_link_libraries(Component PluginService)

add_executable(testLoading tests/testLoading.cpp)
target_link_libraries(testLoading PluginService)
