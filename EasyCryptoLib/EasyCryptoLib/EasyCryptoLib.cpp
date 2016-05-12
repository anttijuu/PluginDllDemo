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

const std::string & EasyCrypto::version() {
   static const std::string versionNumber("1.0.0");
   return versionNumber;
}

const std::string & EasyCrypto::methods() {
   static const std::string methodsStr("matrix,reverse");
   return methodsStr;
}

void EasyCrypto::encrypt(const std::string & toEncrypt, std::string & toStoreTo, Method m) {
   switch (m) {
      case Method::Reverse: {
         std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivReverse());
         theImpl->encrypt(toEncrypt, toStoreTo);
         break;
      }
      case Method::Matrix: {
         std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivMatrix());
         theImpl->encrypt(toEncrypt, toStoreTo);
         break;
      }
   }
}

void EasyCrypto::decrypt(const std::string & toDecrypt, std::string & toStoreTo, Method m) {
   switch (m) {
      case Method::Reverse: {
         std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivReverse());
         theImpl->decrypt(toDecrypt, toStoreTo);
         break;
      }
      case Method::Matrix: {
         std::unique_ptr<EasyCryptoPriv> theImpl(new EasyCryptoPrivMatrix());
         theImpl->decrypt(toDecrypt, toStoreTo);
         break;
      }
   }
}

