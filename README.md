# README #

This system was a course project in the Study Program for Information Processing Science, University of Oulu. Course module where this project was used focused on libraries and APIs.

Themes handled through this project are:

* dynamic (shared) libraries in C++ and the binary compatibility issues there (demo);
* API headers, building a library and distributing it;
* an API exposed over the internet, using udp sockets/boost and JSON;
* tools for making cross-platform libraries using different compilers; CMake

Project includes a "bad" API to the library, and also a better one, which is more robust concerning API changes and binary compatibility.

Student task is to study the binary compatibility issues, develop a new crypto method (as stupid as possible) and design the JSON API for the networked solution.

## TODO

* Works on macOS and Ubuntu, check that also works on Windows
* Perhaps create an unit test framework for the library and server and forget the client; use Catch or something.
* Also demonstrate static libraries?

## Who to talk to

(c) Antti Juustila 2019