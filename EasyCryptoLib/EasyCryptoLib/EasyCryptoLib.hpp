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

/* The classes below are exported from the dynamic link library */
#pragma GCC visibility push(default)

/**
 This header file is the public interface to the crypting library. The library 
 supports multiple encrypting methods and also decrypts the encrypted text back
 to plain text.<br />
 All the methods in this class are static, so there is no need to instantiate the class.
 Implementation creates necessary internal objects which do the actual encrypting
 and decrypting.<br />
 Build the code in the library as a dylib (dll). For client app development,
 provide this header file, with the .dylib (.dll) file, and nothing more.
 Client app developers use these two files when using the functionality of the library.
 @author Antti Juustila
 */
class EasyCrypto
{
public:
   /*! Different supported crypto methods */
   enum Method {
      Reverse, /*!< Simply reverses the provided text. */
      Matrix   /*!< Splits the text into a matrix of characters and transforms the matrix. */
   };
   
   /*
    Encrypts the given plaintext and stores it to the parameter to be used by the caller.
    @param toEncrypt Text to encrypt.
    @param toStoreTo A string to store the ecrypted text to.
    @param m The method of encryption.
    */
   static void encrypt(const std::string & toEncrypt, std::string & toStoreTo, Method m);
   /*
    Decrypts the given encrypted text and stores it to the parameter to be used by the caller.
    @param toDecrypt Text to decrypt.
    @param toStoreTo A string to store the derypted plain text to.
    @param m The method of decryption.
    */
   static void decrypt(const std::string & toDecrypt, std::string & toStoreTo, Method m);
   
   /** To query the version of the library.
    @returns The library version number in the form "1.0.0".
    */
   static const std::string & version();
   /** To query the supported en/decryption methods of the library.
    @returns The supported methods in the form "matrix,reverse".
    */
   static const std::string & methods();
};

#pragma GCC visibility pop

#endif
