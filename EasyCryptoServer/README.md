# EasyCryptoServer #

EasyCryptoServer is a server app with a console UI, providing encryption services for client apps over UDP using JSON as transport data format.

## Dependencies

* Boost system library
* nlohmann::json library
* EasyCryptoLib shared library using plugin dlls

## Installing Boost and nlohmann::json

You need to download and install [boost](https://boost.org) and build the system library at least (1.70 or newer do not require this). See instructions from Boost readme. Basically you must:

1. run the boostrap command and then 
1. the b2 command. After this, 
1. run b2 again with sudo and install to install boost headers and libs in the usual place in *nix machines: `/usr/local/include` and `/usr/local/lib`. 

**On Windows**, you need to tell where to install and later use the Boost library headers:

```
bootstrap.bat
.\b2 --cxxflags="-std=c++17" --with-system --prefix=C:\bin
.\b2 --cxxflags="-std=c++17" --with-system --prefix=C:\bin install
```
After this, you should see Boost headers in `C:\bin\include`.

Note that when using Boost 1.69 or newer, building the system library build is no longer needed.

Also get nlohmann::json from github in a separate directory of your workspace (*not* in EasyCryptoServer directory) and install it (on *nixes):

```
git clone https://github.com/nlohmann/json
cd json
mkdir ninja
cd ninja
cmake -GNinja ..
ninja
sudo ninja install
```
**Again on Windows** you need to tell where to install the library:

```
git clone https://github.com/nlohmann/json
cd json
mkdir ninja
cd ninja
cmake -GNinja -DCMAKE_INSTALL_PREFIX=C:\bin ..
ninja
ninja install
```
Now you should have all the external components EasyCryptoServer needs installed and configured for use.


## Building EasyCryptoServer

First build and install the external libs (Boost and nlohmann::json) and the EasyCryptoLib library. Instructions for EasyCryptoLib can be found in the library's readme.

Then build the server using CMake and Ninja (*nixes):

```
cd EasyCryptoServer
mkdir build && cd build
cmake -GNinja ..
ninja
``` 

**Now on Windows** you need to tell where to find the installed libraries (Boost, nlohmann::json and EasyCryptoLib):

```
cd EasyCryptoServer
mkdir build
cd build
cmake -GNinja -DCMAKE_PREFIX_PATH=C:\bin ..
ninja
```

Note that there is no need to install the server using `ninja install` since the executable may be executed from the build directory. Obviously if you want, you can copy the binary to C:\bin\bin if you wish and execute it from there.

After this, you can start the server: `./CryptoServer 10000` listening to messages using port 10000. 

If the parameter is not given a default port `10000` is used. Obviously the client apps need to connect to this port so mind the number when starting the client apps.


## License

The app is published under LGPL.  Please see the provided [LICENSE](LICENSE) file.

(C) Antti Juustila, 2016-2020 All rights reserved.
antti dot juustila at oulu.fi
