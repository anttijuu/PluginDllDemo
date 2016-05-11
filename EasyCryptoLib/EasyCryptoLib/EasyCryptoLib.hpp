/*
 *  EasyCryptoLib.hpp
 *  EasyCryptoLib
 *
 *  Created by Antti Juustila on 3.5.2016.
 *  Copyright © 2016 Antti Juustila. All rights reserved.
 *
 */

#ifndef EasyCryptoLib_
#define EasyCryptoLib_

#include <string>

/* The classes below are exported */
#pragma GCC visibility push(default)

// TODO: add version number query
class EasyCrypto
{
public:
   enum Method {
      Reverse,
      Matrix
   };
   
   static void encrypt(const std::string & toEncrypt, std::string & toStoreTo, Method m);
   static void decrypt(const std::string & toDecrypt, std::string & toStoreTo, Method m);
};

#pragma GCC visibility pop

#endif
