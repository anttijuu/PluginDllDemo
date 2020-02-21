include(CMakeFindDependencyMacro)

find_dependency(Boost 1.72.0)

include("${CMAKE_CURRENT_LIST_DIR}/EasyCryptoPluginTargets.cmake")
