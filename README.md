# README #

This system was a course project in the Study Program for Information Processing Science, University of Oulu. Course module where this project was used focused on libraries and APIs.

Themes handled through this project are:

* dynamic (shared) libraries in C++ and the binary compatibility issues there (demo);
* API headers, building a library and distributing it;
* an API exposed over the internet, using udp sockets/boost and JSON;
* tools for making cross-platform libraries using different compilers in different OSes; CMake

Project includes a "bad" API to the library, and also a better one, which is more robust concerning API changes and binary compatibility.

Student task is to study the binary compatibility issues, develop a new crypto method (as stupid as possible) and design the JSON API for the networked solution, implement and test it with the client and server.

## Instructions to Teachers

First of all, in the introduction, it is up to the teacher to demonstrate how a library can be changed so that it breaks binary compatibility causing an app to use the library to crash if app has not been build against the new lib and the API of the lib is not well designed.

How to do this demo:

1. Comment out Matrix encryption from the project totally (comment source files out from Lib project CMakeLists.txt) and comment out usage of the Matrix from the EasyCryptoLib.cpp and EasyCryptoBad.hpp/.cpp. Note that you should do this **before the demo event** since this takes time.
2. Build the lib and install it (see Building below)
3. Build the CryptoClientConsole app
4. Use the good and bad lib API from the CryptoClientConsole app
5. Now "add" new functionality to the Lib by taking the Matrix method back in by removing comments. If you forget to remove some comments you will probably see build errors so be careful.
6. build the Lib and install it (see Building below)
7. DO NOT BUILD the CryptoClientConsole app. This simulates the situation that some *other* developer has updated their app which *also* uses the Lib, has updated it but *CryptoClientConsole app has not yet been rebuild* against the new Lib (because the devs are slow or on vacation, what ever). You need to explain this to students obviously.
7. Run the CryptoClientConsole app to see how when using the EasyCryptoBad API, the console app crashes, but NOT using the EasyCryptoLib (good) api.

Then discuss why using the bad API class the app crashed, and discuss (using the course slides) why library developers must be very aware of binary compatibility issues when updating a published library.

Then teacher gives the *edited* source code (see below) to the students who will then a) implement a third encryption class and b) design and implement a JSON protocol and message structure (API) to enable a client app using the Lib over the network assisted by a server. 

### Editing the code before giving it to the students

**IMPORTANT** On the client app side, teacher must remove the implementation of handleXxxx and other methods in the Client code marked with comments:

```
   // Remove all code below in this method from code given to students.
```

**IMPORTANT** On the server app side, teacher must remove the implementation of handling client responses. Look for comments starting `// Remove` for the code that must be removed before giving the code to the students.

Also check code to remove from the header files of Client and Server.

Only then the skeleton code of Client, Lib and Server can be given to the students. Do *not* share the code from Bitbucket or similar, since the git *version history* enables the students to go back to the version which *includes* these implementations. Copy the CMake and source files only, excluding the hidden .git directories where the version history is also located.

It is then the student's responsibility to: 

1. design the protocol of JSON message structures that are send and received by the client and server to enable encryption/decryption distributed way, and
2. implement constructing and parsing the messages using jsoncpp library, and
3. implement the request handling in client and server side so that everything works, and
4. add the third encryption method to the library without breaking binary compatibility (the bad library API can be dropped at this point since it is just an example of how *not* to do things). Method could be e.g. rot13 or similar. 


## Dependencies

* Boost-system
* jsoncpp

You need to download and install [boost](https://boost.org) and build the system library at least (1.69 or newer do not require this). See instructions from Boost readme. Basically you must 1) run the boostrap command and then 2) the b2 command. After this, 3) run b2 again with sudo and install to install boost headers and libs in the usual place `/usr/local/include` and `/usr/local/lib`. 

Note that when using Boost 1.69 or newer, building the system library is no longer needed.

Also get jsoncpp from github in the root dir of your workspace (*not* in EasyCrypto directory):

```
git clone https://github.com/open-source-parsers/jsoncpp
```

Then run the amalgamate.py script and install (from the generated `dist`directory) the header subdirectory `json` to `/usr/local/include` and copy the `jsoncpp.cpp` file both to the Client and Server directories of EasyCrypto project.

## Building EasyCrypto

Assuming you already have boost and jsoncpp installed (see Dependencies above), and [cmake](https://cmake.org) too.

First build the library:

1. cd EasyCryptoLib
2. mkdir build
3. cd build
4. cmake ..
5. make
6. sudo make install

After this the library is "published" to `/usr/local/include` and `/usr/local/lib` and can be used by the apps.

What you want to teach to the students is that if the lib is not open source, you only share the *public headers* and the *binary lib* file to other developers (.so, .dll, .dylib), not all the source code. And when you deliver the system to the user, you only deliver the lib binary (.so, .dll, .dylib) and the app binary -- end users do not care about headers.

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

After this, go to server build dir and start the server: `./CryptoServer 10000` listening to messages using port 10000. After this, start the client: `./CryptoClient localhost 10000`, providing the server address and port as a parameter.

## TODO

* Works on macOS and Ubuntu, check that also works on Windows. In Win 10 with Visual Studio dev tools should be easy since Visual Studio nowadays support bash shells and importing projects from cmake files.
* Perhaps create an unit test framework for the library and server and forget the client; use Catch or something.
* Also demonstrate static libraries?

## Who to talk to

(c) Antti Juustila 2019
