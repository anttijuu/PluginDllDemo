cmake_minimum_required(VERSION 3.12)
project(EasyCryptoLibrary VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(LIB_NAME EasyCrypto)

add_library(${LIB_NAME} SHARED EasyCryptoLib.cpp EasyCryptoLibBad.cpp EasyCryptoPrivReverse.cpp EasyCryptoPrivMatrix.cpp EasyCryptoLib.hpp EasyCryptoLibBad.hpp EasyCryptoPrivReverse.hpp EasyCryptoPrivMatrix.hpp ECMasterHeader.hpp)

set_target_properties(${LIB_NAME} PROPERTIES COMPILE_FLAGS -fPIC)
set_target_properties(${LIB_NAME} PROPERTIES LINK_FLAGS "-Wl")
set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD 14)
set_target_properties(${LIB_NAME} PROPERTIES CMAKE_CXX_VISIBILITY_PRESET hidden)
set_target_properties(${LIB_NAME} PROPERTIES CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set_target_properties(${LIB_NAME} PROPERTIES DEFINE_SYMBOL "EC_DLL_EXPORTS" DEFINE_SYMBOL "EC_DLL")

set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "ECMasterHeader.hpp;EasyCryptoLib.hpp;EasyCryptoLibBad.hpp")

install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_NAME})
install(EXPORT ${LIB_NAME}Targets FILE ${LIB_NAME}Targets.cmake NAMESPACE EasyCrypto:: DESTINATION lib/cmake/${LIB_NAME})
install(FILES ${LIB_NAME}Config.cmake DESTINATION lib/cmake/${LIB_NAME})
export(TARGETS ${LIB_NAME} FILE ${LIB_NAME}Targets.cmake)
