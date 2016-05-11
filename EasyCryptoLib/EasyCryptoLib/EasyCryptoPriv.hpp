/*
 *  EasyCryptoLibPriv.hpp
 *  EasyCryptoLib
 *
 *  Created by Antti Juustila on 3.5.2016.
 *  Copyright © 2016 Antti Juustila. All rights reserved.
 *
 */

#ifndef __EasyCryptoPriv_hpp
#define __EasyCryptoPriv_hpp

#include <string>

/* The classes below are not exported */
#pragma GCC visibility push(hidden)

class EasyCryptoPriv
{
public:
   virtual void encrypt(const std::string & toEncrypt, std::string & toStoreTo) = 0;
   virtual void decrypt(const std::string & toDecrypt, std::string & toStoreTo) = 0;
   virtual const std::string & method() const = 0;
   
   virtual ~EasyCryptoPriv() {};
};

#pragma GCC visibility pop

#endif // __EasyCryptoPriv_hpp