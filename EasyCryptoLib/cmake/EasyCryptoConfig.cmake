include(CMakeFindDependencyMacro)

find_dependency(Boost 1.69.0)

include("${CMAKE_CURRENT_LIST_DIR}/EasyCryptoTargets.cmake")
