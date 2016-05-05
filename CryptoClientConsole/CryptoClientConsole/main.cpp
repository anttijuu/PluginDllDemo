//
//  main.cpp
//  CryptoClientConsole
//
//  Created by Antti Juustila on 4.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#include <iostream>

#include "EasyCryptoLib.hpp"
#include "EasyCryptoLibBad.hpp"

void usingGoodLib();
void usingBadLib();

int main(int argc, const char * argv[]) {

	usingGoodLib();
	usingBadLib();
	
	return 0;
}


void usingGoodLib() {
	std::cout << "Welcome to Good EasyCrypto(tm)!" << std::endl;
	std::cout << "Enter text to encrypt: ";
	
	std::string userString;
	std::string result;
	std::getline(std::cin, userString);
	
	EasyCrypto::encrypt(userString, result, EasyCrypto::Method::Reverse);
	std::cout << "Text encrypted with Reverse method: ";
	std::cout << result << std::endl;
	std::cout << "Decrypting back to original: ";
	EasyCrypto::decrypt(result, userString, EasyCrypto::Method::Reverse);
	std::cout << userString << std::endl << std::endl;
	
	EasyCrypto::encrypt(userString, result, EasyCrypto::Method::Matrix);
	std::cout << "Text encrypted with Matrix method: ";
	std::cout << result << std::endl;
	std::cout << "Decrypting back to original: ";
	EasyCrypto::decrypt(result, userString, EasyCrypto::Method::Matrix);
   std::cout << userString << std::endl << std::endl;
	
}

void usingBadLib() {
   std::cout << "==============================" << std::endl;
   std::cout << "Welcome to Bad EasyCrypto(tm)!" << std::endl;
	std::cout << "Enter text to encrypt: ";
	
	std::string userString;
	std::string result;
	std::getline(std::cin, userString);
	
   std::unique_ptr<EasyCryptoLibBad> crypter(new EasyCryptoLibBad());
	
	crypter->encrypt(userString, result, EasyCryptoLibBad::Method::Reverse);
	std::cout << "Text encrypted with Reverse method: ";
	std::cout << result << std::endl;
	std::cout << "Decrypting back to original: ";
	crypter->decrypt(result, userString, EasyCryptoLibBad::Method::Reverse);
	std::cout << userString << std::endl << std::endl;
	
	crypter->encrypt(userString, result, EasyCryptoLibBad::Method::Matrix);
	std::cout << "Text encrypted with Matrix method: ";
	std::cout << result << std::endl;
	std::cout << "Decrypting back to original: ";
	crypter->decrypt(result, userString, EasyCryptoLibBad::Method::Matrix);
	std::cout << userString << std::endl << std::endl;
		
}
