cmake_minimum_required(VERSION 3.0)
project(EasyCrypto)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_CXX_FLAGS "-shared -fPIC -g -Wall -std=c++11 -stdlib=libc++ ${CMAKE_CXX_FLAGS}")
add_library(${PROJECT_NAME} SHARED EasyCryptoLib.cpp EasyCryptoLibBad.cpp EasyCryptoPrivMatrix.cpp EasyCryptoPrivReverse.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES DEFINE_SYMBOL "EC_DLL_EXPORTS" DEFINE_SYMBOL "EC_DLL")
install (TARGETS EasyCrypto
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)
file(GLOB HEADERS ECMasterHeader.hpp EasyCryptoLib.hpp EasyCryptoLibBad.hpp)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
