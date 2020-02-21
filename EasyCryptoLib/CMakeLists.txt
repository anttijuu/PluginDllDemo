cmake_minimum_required(VERSION 3.14)
project(EasyCryptoLibrary VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(LIB_NAME EasyCryptoPlugin)
set(EasyCrypto_VERSION 1.0.0)


# Add a "doc" target to generate API documentation with Doxygen.
# Doxygen is _not_ a component that ProcessorNode uses, but a _tool_
# used in library document generation as part of the build process.
# After "cmake ..", execute "make doc" to create docs.
# When using Ninja, do "cmake -GNinja .." and "ninja doc" to create the docs.
# There will be a docs directory in the build dir, containing the docs.
find_package(Doxygen)
if (DOXYGEN_FOUND)
   configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxyfile @ONLY)
   add_custom_target(doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM
   )
endif(DOXYGEN_FOUND)

# Then find Boost and set up the lib project.
find_package(Boost 1.72.0 REQUIRED system filesystem)

add_library(${LIB_NAME} SHARED EasyCryptoLib.cpp include/${LIB_NAME}/EasyCryptoLib.hpp include/${LIB_NAME}/EasyCryptoPluginAPI.hpp include/${LIB_NAME}/EasyCryptoDefines.hpp)

target_link_libraries(${LIB_NAME} Boost::filesystem Boost::system)

set_property(TARGET ${LIB_NAME} PROPERTY VERSION ${EasyCrypto_VERSION})
set_property(TARGET ${LIB_NAME} PROPERTY SOVERSION 1)
set_property(TARGET ${LIB_NAME} PROPERTY INTERFACE_EasyCrypto_MAJOR_VERSION 1)
set_property(TARGET ${LIB_NAME} APPEND PROPERTY
   COMPATIBLE_INTERFACE_STRING EasyCrypto_MAJOR_VERSION
)

set_property(TARGET ${LIB_NAME} PROPERTY INTERFACE_POSITION_INDEPENDENT_CODE ON)
set_target_properties(${LIB_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${LIB_NAME} PROPERTIES CMAKE_CXX_VISIBILITY_PRESET hidden)
set_target_properties(${LIB_NAME} PROPERTIES CMAKE_CXX_VISIBILITY hidden)
set_target_properties(${LIB_NAME} PROPERTIES CMAKE_VISIBILITY_INLINES_HIDDEN YES)

set_target_properties(${LIB_NAME} PROPERTIES PUBLIC_HEADER "include/${LIB_NAME}/EasyCryptoLib.hpp;include/${LIB_NAME}/EasyCryptoPluginAPI.hpp;include/${LIB_NAME}/EasyCryptoDefines.hpp")
target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/> $<INSTALL_INTERFACE:include/${LIB_NAME}> ${Boost_INCLUDE_DIRS})

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

install(EXPORT ${LIB_NAME}Targets FILE ${LIB_NAME}Targets.cmake NAMESPACE EasyCryptoPlugin:: DESTINATION ${ConfigPackageLocation})

install(FILES cmake/${LIB_NAME}Config.cmake
   "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}/${LIB_NAME}ConfigVersion.cmake"
   DESTINATION ${ConfigPackageLocation} COMPONENT Devel)
