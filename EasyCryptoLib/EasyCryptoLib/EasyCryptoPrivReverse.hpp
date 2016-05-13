//
//  EasyCryptoPrivReverse.hpp
//  EasyCryptoLib
//
//  Created by Antti Juustila on 4.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#ifndef EasyCryptoPrivReverse_hpp
#define EasyCryptoPrivReverse_hpp

#include <string>

#include "EasyCryptoPriv.hpp"

#pragma GCC visibility push(hidden)

namespace EasyCrypto {

class EasyCryptoPrivReverse : public EasyCryptoPriv
{
public:
   
   virtual void encrypt(const std::string & toEncrypt, std::string & toStoreTo);
   virtual void decrypt(const std::string & toDecrypt, std::string & toStoreTo);
   
   virtual const std::string & method() const;
   
private:
   static const std::string methodName;
};

} //namespace

#pragma GCC visibility pop

#endif /* EasyCryptoPrivReverse_hpp */
