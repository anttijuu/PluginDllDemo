//
//  EasyCryptoLibBad.cpp
//  EasyCryptoLib
//
//  Created by Antti Juustila on 4.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#include "EasyCryptoLibBad.hpp"
#include "EasyCryptoPrivReverse.hpp"
#include "EasyCryptoPrivMatrix.hpp"

namespace EasyCrypto {


EasyCryptoLibBad::EasyCryptoLibBad()
   : revCrypto(new EasyCryptoPrivReverse()) // , matCrypto(new EasyCryptoPrivMatrix())
{
}

EasyCryptoLibBad::~EasyCryptoLibBad() {
}
   
std::string EasyCryptoLibBad::methods() {
   std::string methods;
   methods = revCrypto->method();
//   methods = methods + "," + matCrypto->method();
   return methods;
}


void EasyCryptoLibBad::encryptWithReverse(const std::string & toEncrypt, std::string & toStoreTo) {
   revCrypto->encrypt(toEncrypt, toStoreTo);
}

//void EasyCryptoLibBad::encryptWithMatrix(const std::string & toEncrypt, std::string & toStoreTo) {
//   matCrypto->encrypt(toEncrypt, toStoreTo);
//}

void EasyCryptoLibBad::decryptWithReverse(const std::string & toEncrypt, std::string & toStoreTo) {
   revCrypto->decrypt(toEncrypt, toStoreTo);
}

//void EasyCryptoLibBad::decryptWithMatrix(const std::string & toEncrypt, std::string & toStoreTo) {
//   matCrypto->decrypt(toEncrypt, toStoreTo);
//}


void EasyCryptoLibBad::encrypt(const std::string & toEncrypt, std::string & toStoreTo, Method m) {
   if (m == Method::Reverse) {
      encryptWithReverse(toEncrypt, toStoreTo);
//   } else if (m == Method::Matrix) {
//      encryptWithMatrix(toEncrypt, toStoreTo);
   }
}

void EasyCryptoLibBad::decrypt(const std::string & toDecrypt, std::string & toStoreTo, Method m) {
   if (m == Method::Reverse) {
      decryptWithReverse(toDecrypt, toStoreTo);
//   } else if (m == Method::Matrix) {
//      decryptWithMatrix(toDecrypt, toStoreTo);
   }
}


} // namespace