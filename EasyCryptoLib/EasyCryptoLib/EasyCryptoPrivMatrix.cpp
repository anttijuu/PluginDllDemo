//
//  EasyCryptoPrivMatrix.cpp
//  EasyCryptoLib
//
//  Created by Antti Juustila on 4.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#include <cmath>
#include <iostream>
#include <algorithm>

#include "EasyCryptoPrivMatrix.hpp"

namespace EasyCrypto {

const std::string EasyCryptoPrivMatrix::methodName("matrix");

const std::string & EasyCryptoPrivMatrix::method() const {
   return methodName;
}

void EasyCryptoPrivMatrix::encrypt(const std::string & toEncrypt, std::string & toStoreTo) {
   toStoreTo = "";
   int matrixWidth = std::floor(std::sqrt(toEncrypt.length()));
   
   std::string toRotate;
   std::string tmp;
   int extraCount = std::abs(std::pow(matrixWidth, 2) - toEncrypt.length());
   if (extraCount > 0) {
      tmp = toEncrypt.substr(0,extraCount);
      std::reverse(tmp.begin(), tmp.end());
      toRotate = toEncrypt.substr(extraCount);
   } else {
      toRotate = toEncrypt;
   }
   for (int outer = 0; outer < matrixWidth; outer++) {
      toStoreTo += toRotate.substr(outer,1);
      for (int inner = outer+matrixWidth; inner < toRotate.length(); inner += matrixWidth) {
         toStoreTo += toRotate.substr(inner,1);
      }
   }
   if (tmp.length() > 0) {
      toStoreTo += tmp;
   }
}

void EasyCryptoPrivMatrix::decrypt(const std::string & toDecrypt, std::string & toStoreTo) {
   toStoreTo = "";
   int matrixWidth = std::floor(std::sqrt(toDecrypt.length()));
   
   std::string toRotate;
   std::string tmp;
   int extraCount = std::abs(std::pow(matrixWidth, 2) - toDecrypt.length());
   if (extraCount > 0) {
      tmp = toDecrypt.substr(toDecrypt.length()-extraCount,extraCount);
      std::reverse(tmp.begin(), tmp.end());
      toRotate = toDecrypt.substr(0, toDecrypt.length()-extraCount);
   } else {
      toRotate = toDecrypt;
   }
   for (int outer = 0; outer < matrixWidth; outer++) {
      toStoreTo += toRotate.substr(outer,1);
      for (int inner = outer+matrixWidth; inner < toRotate.length(); inner += matrixWidth) {
         toStoreTo += toRotate.substr(inner,1);
      }
   }
   if (tmp.length() > 0) {
      toStoreTo = tmp + toStoreTo;
   }
}
   
} // namespace
