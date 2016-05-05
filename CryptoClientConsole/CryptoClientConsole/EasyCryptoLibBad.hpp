//
//  EasyCryptoLibBad.h
//  EasyCryptoLib
//
//  Created by Antti Juustila on 4.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#ifndef EasyCryptoLibBad_h
#define EasyCryptoLibBad_h

#include <string>

class EasyCryptoPrivReverse;
class EasyCryptoPrivMatrix;

class EasyCryptoLibBad
{
private:
	EasyCryptoPrivReverse *revCrypto;
	// EasyCryptoPrivMatrix *matCrypto;
	
public:
	EasyCryptoLibBad();
	~EasyCryptoLibBad();
	
	enum Method {
		Reverse,
		Matrix,
	};
	virtual void encryptWithReverse(const std::string & toEncrypt, std::string & toStoreTo);
	// virtual void encryptWithMatrix(const std::string & toEncrypt, std::string & toStoreTo);
	
	virtual void decryptWithReverse(const std::string & toEncrypt, std::string & toStoreTo);
	// virtual void decryptWithMatrix(const std::string & toEncrypt, std::string & toStoreTo);
	
	virtual void encrypt(const std::string & toEncrypt, std::string & toStoreTo, Method m);
	virtual void decrypt(const std::string & toDecrypt, std::string & toStoreTo, Method m);
	
};



#endif /* EasyCryptoLibBad_h */
