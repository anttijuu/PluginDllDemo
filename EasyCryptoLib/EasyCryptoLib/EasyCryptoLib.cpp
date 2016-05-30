/*
 *  EasyCryptoLib.cpp
 *  EasyCryptoLib
 *
 *  Created by Antti Juustila on 3.5.2016.
 *  Copyright © 2016 Antti Juustila. All rights reserved.
 *
 */

#include <iostream>
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
//      std::unique_ptr<EasyCryptoPriv> theImpl2(new EasyCryptoPrivMatrix());
//      methods = methods + "," + theImpl2->method();
      return methods;
   }
   
   void EasyCryptoLib::encrypt(const std::string & toEncrypt, std::string & toStoreTo, const std::string & method) {
      if (method == "reverse") {
         std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivReverse());
         theImpl->encrypt(toEncrypt, toStoreTo);
//      } else if (method == "matrix") {
//         std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivMatrix());
//         theImpl->encrypt(toEncrypt, toStoreTo);
      }
   }
   
   
   void EasyCryptoLib::decrypt(const std::string & toDecrypt, std::string & toStoreTo, const std::string & method) {
      if (method == "reverse") {
         std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivReverse());
         theImpl->decrypt(toDecrypt, toStoreTo);
//      }else if (method == "matrix") {
//         std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivMatrix());
//         theImpl->decrypt(toDecrypt, toStoreTo);
      }
   }
   
} // namespace
