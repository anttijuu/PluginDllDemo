/*
 *  EasyCryptoLib.cpp
 *  EasyCryptoLib
 *
 *  Created by Antti Juustila on 3.5.2016.
 *  Copyright © 2016 Antti Juustila. All rights reserved.
 *
 */

#include <iostream>

#include "EasyCryptoLib.hpp"
#include "EasyCryptoPrivReverse.hpp"
#include "EasyCryptoPrivMatrix.hpp"

void EasyCrypto::encrypt(const std::string & toEncrypt, std::string & toStoreTo, Method m) {
   EasyCryptoPriv * theImpl = nullptr;
   switch (m) {
      case Method::Reverse: {
         theImpl = new EasyCryptoPrivReverse();
         theImpl->encrypt(toEncrypt, toStoreTo);
         delete theImpl;
         break;
      }
      case Method::Matrix: {
         toStoreTo = "Not supported";
         theImpl = new EasyCryptoPrivMatrix();
         theImpl->encrypt(toEncrypt, toStoreTo);
         delete theImpl;
         break;
      }
   }
}

void EasyCrypto::decrypt(const std::string & toDecrypt, std::string & toStoreTo, Method m) {
   EasyCryptoPriv * theImpl = nullptr;
   switch (m) {
      case Method::Reverse: {
         theImpl = new EasyCryptoPrivReverse();
         theImpl->decrypt(toDecrypt, toStoreTo);
         delete theImpl;
         break;
      }
      case Method::Matrix: {
         toStoreTo = "Not supported";
         theImpl = new EasyCryptoPrivMatrix();
         theImpl->decrypt(toDecrypt, toStoreTo);
         delete theImpl;
         break;
      }
   }
}

