/*
 EasyCryptoLibBad.h
 EasyCryptoLib

 Created by Antti Juustila on 4.5.2016.
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

#ifndef EasyCryptoLibBad_h
#define EasyCryptoLibBad_h

#include <string>
#include <memory>

#include "ECMasterHeader.hpp"


namespace EasyCrypto {

class EC_LOCAL EasyCryptoPrivReverse;
class EC_LOCAL EasyCryptoPrivMatrix;
   
class EC_API EasyCryptoLibBad
{
private:
   std::unique_ptr<EasyCryptoPrivMatrix> matCrypto;
   std::unique_ptr<EasyCryptoPrivReverse> revCrypto;
   
public:
   EasyCryptoLibBad();
   virtual ~EasyCryptoLibBad();
   
   enum Method {
      Reverse,
      Matrix,
   };
private:
   EC_LOCAL virtual void encryptWithMatrix(const std::string & toEncrypt, std::string & toStoreTo);
   EC_LOCAL virtual void encryptWithReverse(const std::string & toEncrypt, std::string & toStoreTo);
   
   EC_LOCAL virtual void decryptWithMatrix(const std::string & toEncrypt, std::string & toStoreTo);
   EC_LOCAL virtual void decryptWithReverse(const std::string & toEncrypt, std::string & toStoreTo);
   
public:
   virtual void encrypt(const std::string & toEncrypt, std::string & toStoreTo, Method m);
   virtual void decrypt(const std::string & toDecrypt, std::string & toStoreTo, Method m);
   
   std::string methods();

};

} // namespace



#endif /* EasyCryptoLibBad_h */
