/*
 EasyCryptoLibBad.cpp
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

#include "EasyCryptoLibBad.hpp"
#include "EasyCryptoPrivReverse.hpp"
#include "EasyCryptoPrivMatrix.hpp"
#include "EasyCryptoExceptions.hpp"

namespace EasyCrypto {
    
    
    EasyCryptoLibBad::EasyCryptoLibBad()
    : matCrypto(new EasyCryptoPrivMatrix()),
    revCrypto(new EasyCryptoPrivReverse())
    {
    }
    
    EasyCryptoLibBad::~EasyCryptoLibBad() {
    }
    
    std::string EasyCryptoLibBad::methods() {
        std::string methods;
        methods = revCrypto->method();
        methods = methods + "," + matCrypto->method();
        return methods;
    }
    
    
    EC_LOCAL void EasyCryptoLibBad::encryptWithReverse(const std::string & toEncrypt, std::string & toStoreTo) {
        revCrypto->encrypt(toEncrypt, toStoreTo);
    }
    
    EC_LOCAL void EasyCryptoLibBad::encryptWithMatrix(const std::string & toEncrypt, std::string & toStoreTo) {
        matCrypto->encrypt(toEncrypt, toStoreTo);
    }
    
    EC_LOCAL void EasyCryptoLibBad::decryptWithReverse(const std::string & toEncrypt, std::string & toStoreTo) {
        revCrypto->decrypt(toEncrypt, toStoreTo);
    }
    
    EC_LOCAL void EasyCryptoLibBad::decryptWithMatrix(const std::string & toEncrypt, std::string & toStoreTo) {
        matCrypto->decrypt(toEncrypt, toStoreTo);
    }
    
    
    void EasyCryptoLibBad::encrypt(const std::string & toEncrypt, std::string & toStoreTo, Method m) {
        if (m == Method::Reverse) {
            encryptWithReverse(toEncrypt, toStoreTo);
        } else if (m == Method::Matrix) {
            encryptWithMatrix(toEncrypt, toStoreTo);
        } else {
            throw not_supported();
        }
    }
    
    void EasyCryptoLibBad::decrypt(const std::string & toDecrypt, std::string & toStoreTo, Method m) {
        if (m == Method::Reverse) {
            decryptWithReverse(toDecrypt, toStoreTo);
        } else if (m == Method::Matrix) {
            decryptWithMatrix(toDecrypt, toStoreTo);
        } else {
            throw not_supported();
        }
    }
    
    
} // namespace
