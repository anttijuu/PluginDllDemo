# EasyCryptoLib
Version 1.0
2019-05-14
(c) Antti Juustila

The source code here implements a dynamic library called EasyCryptoLib, which is capable of encrypting and decrypting text using several methods of cryption. Methods supported in the current version are "reverse" and  "matrix". Crypto methods are implemented as separate plugin dll's using Boost::DLL library.

The library is implemented using C++17 and utilises the Standard Template Library as well as Boost version 1.70.

The library is tested to work on Ubuntu as well as Mac OS X 10.14.

## Building

Building is done using CMake. See the included CMakeLists.txt files for the library and the plugin dll's.

The interface to the EasyCryptoLib consists of two files:

* EasyCryptoLib.hpp, the header file used by client apps
* EasyCrytoLib.dylib/.so/.dll, a shared (dynamic) library clients use at runtime

Assumption is that after building, the interface consisting of these two files is copied to a shared include and library directory in the system and used from there by the client applications. Using CMake, this is done like this

1. mkdir build
2. cd build
3. cmake ..
4. make
5. sudo make install

Note that you need to build and install the crypto plugin dll's separately. Build commands are as above, given in the plugin dll directories.

In Ubuntu and Mac, the directory for the shared hpp file is /usr/local/include, and the directory for the shared library file is /usr/local/lib.

NOTE: The version provided here also includes, for demonstration purposes, a file EasyCryptoLibBad.hpp and code for this interface class is also included in the shared library file. Please remove this interface class before seriously using the library, and rebuild and install the public interface using the  commands as described above.

Please see the provided LICENSE file for copyright.

Oulu, May 14th, 2019
Antti Juustila
antti.juustila@oulu.fi

