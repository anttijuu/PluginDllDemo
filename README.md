# README #

This system was a course project in the Study Program for Information Processing Science, University of Oulu. Course module where this project was used focused on libraries and APIs.

Themes handled through this project are:

* dynamic (shared) libraries in C++ and the binary compatibility issues there (demo);
* API headers, building a library and distributing it;
* an API exposed over the internet, using udp sockets/boost and JSON;
* tools for making cross-platform libraries using different compilers; CMake

Project includes a "bad" API to the library, and also a better one, which is more robust concerning API changes and binary compatibility.

Student task is to study the binary compatibility issues, develop a new crypto method (as stupid as possible) and design the JSON API for the networked solution.

## Dependencies

* Boost-system
* jsoncpp

You need to download and install boost and build the system library at least. Also download jsoncpp, run the amalgamate.py script and install the header to /usr/local/include and the cpp file to each project's source code directory.

## Building

First build the library:

1. cd EasyCryptoLib
2. mkdir build
3. cd build
4. cmake ..
5. make
6. sudo make install

Then build the server:

1. cd EasyCryptoServer
2. mkdir build
3. cd build
4. cmake ..
5. make

And then build the client

1. cd EasyCryptoClient
2. mkdir build
3. cd build
4. cmake ..
5. make

After this, go to server build dir and start the server. After this, start the client, providing the server ip address and port as a parameter.

## TODO

* Works on macOS and Ubuntu, check that also works on Windows
* Perhaps create an unit test framework for the library and server and forget the client; use Catch or something.
* Also demonstrate static libraries?

## Who to talk to

(c) Antti Juustila 2019