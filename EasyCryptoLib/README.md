# EasyCryptoLib

The source code here implements a dynamic library called EasyCryptoLib, which is capable of encrypting and decrypting text using several methods of cryption. Methods supported in the current version are "reverse" and  "matrix". Crypto methods are implemented as separate plugin dll's using Boost::DLL library.

The library is implemented using C++17 and utilises the Standard Template Library as well as Boost version 1.70.

The library is tested to work on Ubuntu as well as Mac OS X 10.15.

## Building

Building is done using CMake and Ninja. See the included CMakeLists.txt files for the library and the plugin dll's.

The interface to the EasyCryptoLib consists of two files:

* EasyCryptoLib.hpp, the header file used by client apps
* EasyCrytoLib.dylib/.so/.dll, a shared (dynamic) library clients use at runtime

Assumption is that after building, the interface consisting of these two files is copied to a shared include and library directory in the system and used from there by the client applications. Using CMake, this is done like this

```
mkdir ninja
cd ninja
cmake -GNinja
ninja
sudo ninja install
```
On Windows, you might want to say where the lib is installed (headers, .dll and .lib) to be available to apps using the lib:

```
mkdir ninja
cd ninja
cmake -GNinja -DCMAKE_INSTALL_PREFIX=C:\bin ..  
ninja
ninja install
```

Note that you need to build and install the crypto plugin dll's separately. Build commands are as above, given in the plugin dll directories.

In Ubuntu and Mac, the directory for the shared hpp file is /usr/local/include, and the directory for the shared library file is /usr/local/lib.

## Using the library from apps

After building and installing the lib, in the client app CMakeLists.txt, use `find_package` to find the library:

```
find_package(EasyCryptoPlugin REQUIRED)
```

And then set the include and link options:

```
target_include_directories(${APP_NAME} PUBLIC EasyCryptoPlugin::EasyCryptoPlugin ... )
target_link_libraries(${APP_NAME} EasyCryptoPlugin::EasyCryptoPlugin ...)
```
In the client app source files (.cpp usually), include the public header API of the library, and then use the library public API:

```
#include <EasyCryptoPlugin/EasyCryptoLib.hpp>

...
EasyCryptoLib::Result r = EasyCryptoLib::encrypt(plainText, encrypted, method);
```
See EasyCryptoServer code how this is done.

## License

The library is published under LGPL.  Please see the provided [LICENSE](LICENSE) file.

Author bears no responsibility of using this code to any purpose.

(c) Antti Juustila 2016-2020, All rights reserved.
