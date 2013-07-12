cmake_minimum_required(VERSION 2.8)

add_library(PluginService SHARED PluginService.cxx )
target_link_libraries(PluginService ${CMAKE_DL_LIBS})

add_library(Component MODULE testMacro.cxx)
target_link_libraries(Component PluginService)

add_executable(testLoading testLoading.cxx)
target_link_libraries(testLoading PluginService)
