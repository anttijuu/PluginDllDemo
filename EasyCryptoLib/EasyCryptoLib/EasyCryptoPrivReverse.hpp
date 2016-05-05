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

class EasyCryptoPrivReverse : public EasyCryptoPriv
{
	public:
	virtual void encrypt(const std::string & toEncrypt, std::string & toStoreTo);
	virtual void decrypt(const std::string & toDecrypt, std::string & toStoreTo);
};

#pragma GCC visibility pop

#endif /* EasyCryptoPrivReverse_hpp */
