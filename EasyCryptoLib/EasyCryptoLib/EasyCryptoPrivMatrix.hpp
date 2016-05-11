//
//  EasyCryptoPrivMatrix.hpp
//  EasyCryptoLib
//
//  Created by Antti Juustila on 4.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#ifndef EasyCryptoPrivMatrix_hpp
#define EasyCryptoPrivMatrix_hpp

#include <string>

#include "EasyCryptoPriv.hpp"

#pragma GCC visibility push(hidden)

class EasyCryptoPrivMatrix : public EasyCryptoPriv
{
public:
   
   virtual void encrypt(const std::string & toEncrypt, std::string & toStoreTo);
   virtual void decrypt(const std::string & toDecrypt, std::string & toStoreTo);
   virtual const std::string & method() const;
   
private:
   static const std::string methodName;
};

#pragma GCC visibility pop

#endif /* EasyCryptoPrivMatrix_hpp */
