//
//  EasyCryptoPrivReverse.cpp
//  EasyCryptoLib
//
//  Created by Antti Juustila on 4.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#include "EasyCryptoPrivReverse.hpp"

void EasyCryptoPrivReverse::encrypt(const std::string & toEncrypt, std::string & toStoreTo) {
	toStoreTo = toEncrypt;
	std::reverse(toStoreTo.begin(), toStoreTo.end());
};

void EasyCryptoPrivReverse::decrypt(const std::string & toDecrypt, std::string & toStoreTo) {
	encrypt(toDecrypt, toStoreTo);
}