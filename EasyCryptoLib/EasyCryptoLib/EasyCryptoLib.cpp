/*
 EasyCryptoLib.cpp
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

#include <memory>

#include "EasyCryptoLib.hpp"
#include "EasyCryptoPrivReverse.hpp"
#include "EasyCryptoPrivMatrix.hpp"

namespace EasyCrypto {
   
   const std::string & EasyCryptoLib::version() {
      static const std::string versionNumber("1.0.0");
      return versionNumber;
   }
   
   std::string EasyCryptoLib::methods() {
      std::string methods;
      std::unique_ptr<EasyCryptoPriv> theImpl1(new EasyCryptoPrivReverse());
      methods = theImpl1->method();
      std::unique_ptr<EasyCryptoPriv> theImpl2(new EasyCryptoPrivMatrix());
      methods = methods + "," + theImpl2->method();
      return methods;
   }
   
   EasyCryptoLib::Result EasyCryptoLib::encrypt(const std::string & toEncrypt, std::string & toStoreTo, const std::string & method) {
      try {
         if (method == "reverse") {
            std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivReverse());
            theImpl->encrypt(toEncrypt, toStoreTo);
            return ESuccess;
         } else if (method == "matrix") {
            std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivMatrix());
            theImpl->encrypt(toEncrypt, toStoreTo);
            return ESuccess;
         }
      } catch (std::exception & e) {
         return EError;
      }
      return ENotSupported;
   }
   
   
   EasyCryptoLib::Result EasyCryptoLib::decrypt(const std::string & toDecrypt, std::string & toStoreTo, const std::string & method) {
      try {
         if (method == "reverse") {
            std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivReverse());
            theImpl->decrypt(toDecrypt, toStoreTo);
            return ESuccess;
         }else if (method == "matrix") {
            std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivMatrix());
            theImpl->decrypt(toDecrypt, toStoreTo);
            return ESuccess;
         }
      } catch (std::exception & e) {
         return EError;
      }
      return ENotSupported;
   }
   
} // namespace
