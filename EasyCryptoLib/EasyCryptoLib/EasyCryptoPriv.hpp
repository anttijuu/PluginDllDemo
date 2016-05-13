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

namespace EasyCrypto {

/*
 An interface class for all cryptographic implementations.
 
 @author Antti Juustila
 @version 1.0.0
 */
class EasyCryptoPriv
{
public:
   /**
    Encrypts a piece of text.
    @param toEncrypt Text to encrypt.
    @param toStoreTo The string where the encrypted text is stored into.
    */
   virtual void encrypt(const std::string & toEncrypt, std::string & toStoreTo) = 0;
   /**
    Decrypts a piece of text.
    @param toDecrypt Text to decrypt.
    @param toStoreTo The string where the decrypted text is stored into.
    */
   virtual void decrypt(const std::string & toDecrypt, std::string & toStoreTo) = 0;
   /**
    To query the encryption/decryption method name this object is using.
    @returns The name of the en/decryption method:
    */
   virtual const std::string & method() const = 0;
   
   virtual ~EasyCryptoPriv() {};
};
   
} // namespace

#pragma GCC visibility pop

#endif // __EasyCryptoPriv_hpp