/*
 EasyCryptoPrivMatrix.cpp
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

#include <cmath>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "EasyCryptoPrivMatrix.hpp"

namespace EasyCrypto {
    
    std::string EasyCryptoPrivMatrix::method() {
        return "matrix";
    }
    
    void EasyCryptoPrivMatrix::encrypt(const std::string & toEncrypt, std::string & toStoreTo) {
        if (toEncrypt.length() < 1) {
            throw std::runtime_error("Empty string");
        }
        
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
            for (unsigned int inner = outer+matrixWidth; inner < toRotate.length(); inner += matrixWidth) {
                toStoreTo += toRotate.substr(inner,1);
            }
        }
        if (tmp.length() > 0) {
            toStoreTo += tmp;
        }
    }
    
    void EasyCryptoPrivMatrix::decrypt(const std::string & toDecrypt, std::string & toStoreTo) {
        if (toDecrypt.length() < 1) {
            throw std::runtime_error("Empty string");
        }
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
            for (unsigned int inner = outer+matrixWidth; inner < toRotate.length(); inner += matrixWidth) {
                toStoreTo += toRotate.substr(inner,1);
            }
        }
        if (tmp.length() > 0) {
            toStoreTo = tmp + toStoreTo;
        }
    }
        
} // namespace
