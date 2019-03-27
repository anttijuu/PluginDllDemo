cmake_minimum_required(VERSION 3.12)
project(EasyCryptoLibrary VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(LIB_NAME EasyCrypto)
set(EasyCrypto_VERSION 1.0.0)

find_package(Boost 1.69.0 REQUIRED system filesystem)

add_library(${LIB_NAME} SHARED EasyCryptoLib.cpp EasyCryptoLib.hpp EasyCryptoPluginAPI.hpp EasyCryptoExceptions.hpp)

target_link_libraries(${LIB_NAME} PUBLIC ${Boost_LIBRARIES})

set_property(TARGET ${LIB_NAME} PROPERTY VERSION ${EasyCrypto_VERSION})
set_property(TARGET ${LIB_NAME} PROPERTY SOVERSION 1)
set_property(TARGET ${LIB_NAME} PROPERTY INTERFACE_EasyCrypto_MAJOR_VERSION 1)
set_property(TARGET ${LIB_NAME} APPEND PROPERTY
   COMPATIBLE_INTERFACE_STRING EasyCrypto_MAJOR_VERSION
)

set_property(TARGET ${LIB_NAME} PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
set_target_properties(${LIB_NAME} PROPERTIES LINK_FLAGS "-Wl")
set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD 14)
set_target_properties(${LIB_NAME} PROPERTIES CMAKE_CXX_VISIBILITY_PRESET hidden)
set_target_properties(${LIB_NAME} PROPERTIES CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "EasyCryptoLib.hpp;EasyCryptoPluginAPI.hpp")
target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/.> $<INSTALL_INTERFACE:include/${LIB_NAME}> ${Boost_INCLUDE_DIRS})

write_basic_package_version_file(
   "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
   VERSION ${EasyCrypto_VERSION}
   COMPATIBILITY AnyNewerVersion)

install(TARGETS ${LIB_NAME} EXPORT ${LIB_NAME}Targets ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${LIB_NAME})

export(EXPORT ${LIB_NAME}Targets
   FILE "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Targets.cmake"
   NAMESPACE EasyCrypto::
)
configure_file(cmake/${LIB_NAME}Config.cmake
   "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}Config.cmake"
   COPYONLY
)
set(ConfigPackageLocation lib/cmake/${LIB_NAME})

install(EXPORT ${LIB_NAME}Targets FILE ${LIB_NAME}Targets.cmake NAMESPACE EasyCrypto:: DESTINATION ${ConfigPackageLocation})

install(FILES cmake/${LIB_NAME}Config.cmake
   "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
   DESTINATION ${ConfigPackageLocation} COMPONENT Devel)
