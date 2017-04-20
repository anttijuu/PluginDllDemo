cmake_minimum_required(VERSION 3.0)
project(EasyCrypto)
set(INCLUDE_INSTALL_DIR /usr/local/include)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_CXX_FLAGS "--std=gnu++11 -shared -fPIC -g -Wall -pthread -I$(IDIR) -DEC_DLL -DEC_DLL_EXPORTS ${CMAKE_CXX_FLAGS}")
add_library(${PROJECT_NAME} SHARED EasyCryptoLib.cpp EasyCryptoLibBad.cpp EasyCryptoPrivMatrix.cpp EasyCryptoPrivReverse.cpp)
install (TARGETS EasyCrypto
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)
file(GLOB HEADERS ECMasterHeader.hpp EasyCryptoLib.hpp EasyCryptoLibBad.hpp)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})
