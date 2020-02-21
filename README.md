# EasyCrypto #

The EasyCrypto system demonstrates:

1. a shared plugin dll library implemented using Boost.DLL,
2. a client/server system using UDP protocol to exchange JSON messages for encrypt/decrypt,
3. API design, both in library and over the network.

Each plugin dll implements one encryption/decryption method. Plugins can be added to the system without rebooting it.

Notice that this is developed for *educational* purposes only. No real encryption is implemented nor designed into the system. No security or other essential non-functional requirements have been considered.

Current version has been tested on macOS 10.15 only. Earlier version has been tested to work on Ubuntu also. Since based on standard C++, boost and build using CMake, the system should be relatively easy to build and run on Windows too. I am currently in the process of making sure this works also in Windows 10.

This [YouTube video](https://youtu.be/zBy_anMAVbA) demonstrates how you can add functionality to a running server by dropping a new plugin dll in the directory where plugins are located.


## Tools and dependencies

Tools you need:

* git to clone the project to your computer
* C++17 compiler
* CMake
* Ninja build tool

And the following external libraries:

* Boost-system and filesystem libraries, using Boost 1.72 or newer.
* nlohmann::json

## Building EasyCrypto

Assuming you already have the external libraries and tools installed, build the components of the system in this order:

1. EasyCryptoLib -- it needs to be build and installed first. See readme in this directory for details.
1. EasyCryptoReversePlugin -- a toy encryption method, reversing the text.1. EasyCryptoServer -- a server app that uses EasyCryptoLib to provide crypto services to client apps.
1. EasyCryptoClient -- a client app communicating with the server over UDP using JSON as a transport data format.

Currently the Matrix plugin does not build, while I am researching how to encrypt Unicode.

Each directory has a readme instructing how to build and install (libs) the component.

![EasyCrypto Deployment](EasyCryptoDeployment.png)

After this, go to server build dir and start the server: `./CryptoServer 10000` listening to messages using port 10000. After this, start the client: `./CryptoClient localhost 10000`, providing the server address and port as a parameter.

Query the *capabilities* of the encryption server. It will reply with the supported encryption methods (currently "matrix" and "reverse"). Use them both to see how they work.

Remove either of the plugin dll:s from the /usr/local/lib/ECPlugins directory while the server is running. Then again query the supported methods. You can see that the server replied with one method missing. Put the dll back in the directory and again query the supported methods. 

![EasyCrypto plugin dll loading](EasyCryptoInitSequence.png)

Implmement additional new encryption methods using either matrix or reverse dll as an example. Install the plugin dll to see a new method taken into use.


## TODO

* Works on macOS and Ubuntu, check that also works on Windows. In Win 10 with Visual Studio dev tools should be easy since Visual Studio nowadays support bash shells and importing projects from cmake files.
* Modify the main and plugin dll libraries to use basic data types only for better binary compatibility across compilers and platforms. 
* Check if there are any issues with various char sets and languages (yes, there are).

## License

The system is published under LGPL.  Please see the provided [LICENSE](LICENSE) file.

(C) Antti Juustila, 2016-2020 All rights reserved.
antti dot juustila at oulu.fi
