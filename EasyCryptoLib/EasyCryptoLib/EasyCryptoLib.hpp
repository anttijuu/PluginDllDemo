/*
 EasyCryptoLib.hpp
 EasyCryptoLib
 
 Created by Antti Juustila on 3.5.2016.
 Copyright © 2016 Antti Juustila.
 
 This file is part of EasyCryptoLib.
 
 EasyCryptoLib is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 EasyCryptoLib is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with EasyCryptoLib.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef EasyCryptoLib_
#define EasyCryptoLib_

#include <string>

/* The classes below are exported from the dynamic link library */
#pragma GCC visibility push(default)


namespace EasyCrypto {
   

/**
 This class is the public interface to the crypting library. The library
 supports multiple encrypting methods and also decrypts the encrypted text back
 to plain text.<br />
 All the methods in this class are static, so there is no need to instantiate the class.
 Implementation creates necessary internal objects which do the actual encrypting
 and decrypting.<br />
 Build the code in the library as a dynamic library. In Mac OS X, they are called .dylib's
 and in Linux, shared libraries (.so). In Windows, they are DLLs. For client app development,
 provide this header file, with the library binary file (.dylib, .so or .dll) file, and nothing more.
 Client app developers use these two files when using the functionality of the library.
 @author Antti Juustila
 @version 1.0.0
 */
class EasyCryptoLib
{
public:
   enum Result {
      ESuccess,
      EError,
      ENotSupported
   };
   /**
    Encrypts the given plaintext and stores it to the parameter to be used by the caller.
    @param toEncrypt Text to encrypt.
    @param toStoreTo A string to store the ecrypted text to.
    @param m The method of encryption.
    */
   static Result encrypt(const std::string & toEncrypt, std::string & toStoreTo, const std::string & method);
   /**
    Decrypts the given encrypted text and stores it to the parameter to be used by the caller.
    @param toDecrypt Text to decrypt.
    @param toStoreTo A string to store the derypted plain text to.
    @param m The method of decryption.
    */
   static Result decrypt(const std::string & toDecrypt, std::string & toStoreTo, const std::string & method);
   
   /** To query the version of the library.
    @returns The library version number in the form "1.0.0".
    */
   static const std::string & version();
   /** To query the supported en/decryption methods of the library.
    @returns The supported methods in the form "matrix,reverse".
    */
   static std::string methods();
};

} // namespace

#pragma GCC visibility pop

#endif
