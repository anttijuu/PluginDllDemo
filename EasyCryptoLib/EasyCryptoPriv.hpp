/*
 EasyCryptoLibPriv.hpp
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

#ifndef __EasyCryptoPriv_hpp
#define __EasyCryptoPriv_hpp

#include <string>

#include "ECMasterHeader.hpp"


namespace EasyCrypto {

/*
 An interface class for all cryptographic implementations.
 
 @author Antti Juustila
 @version 1.0.0
 */
class EC_LOCAL EasyCryptoPriv
{
public:
   /*
    Encrypts a piece of text.
    @param toEncrypt Text to encrypt.
    @param toStoreTo The string where the encrypted text is stored into.
    */
   virtual void encrypt(const std::string & toEncrypt, std::string & toStoreTo) = 0;
   /*
    Decrypts a piece of text.
    @param toDecrypt Text to decrypt.
    @param toStoreTo The string where the decrypted text is stored into.
    */
   virtual void decrypt(const std::string & toDecrypt, std::string & toStoreTo) = 0;
   /*
    To query the encryption/decryption method name this object is using.
    @returns The name of the en/decryption method:
    */
   virtual const std::string & method() const = 0;
   
   virtual ~EasyCryptoPriv() {};
};
   
} // namespace


#endif // __EasyCryptoPriv_hpp
