cmake_minimum_required(VERSION 3.14)
project(EasyCryptoPluginMatrix VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(LIB_NAME EasyCryptoMatrix)

find_package(Boost 1.72.0 REQUIRED system filesystem)

add_library(${LIB_NAME} SHARED EasyCryptoPlugin.cpp EasyCryptoPlugin.hpp)

set_property(TARGET ${LIB_NAME} PROPERTY INTERFACE_LIB_VERSION 1.0.0)
set_property(TARGET ${LIB_NAME} APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING LIB_VERSION
)
set_property(TARGET ${LIB_NAME} PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${LIB_NAME} PROPERTIES CMAKE_CXX_VISIBILITY_PRESET hidden)
set_target_properties(${LIB_NAME} PROPERTIES CMAKE_VISIBILITY_INLINES_HIDDEN YES)

target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/.> $<INSTALL_INTERFACE:include/${LIB_NAME}> ${Boost_INCLUDE_DIRS})

target_link_libraries(${LIB_NAME} PRIVATE Boost::system Boost::filesystem)

install(TARGETS ${LIB_NAME} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/ECPlugins LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/ECPlugins RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/ECPlugins)
