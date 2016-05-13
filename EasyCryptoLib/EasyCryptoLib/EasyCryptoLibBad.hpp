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
#include <memory>

class EasyCryptoPrivReverse;
class EasyCryptoPrivMatrix;

/* The classes below are exported */
#pragma GCC visibility push(default)

// TODO: add version number query

class EasyCryptoLibBad
{
private:
   std::unique_ptr<EasyCryptoPrivReverse> revCrypto;
   std::unique_ptr<EasyCryptoPrivMatrix> matCrypto;
   
public:
   EasyCryptoLibBad();
   virtual ~EasyCryptoLibBad();
   
   enum Method {
      Reverse,
      Matrix,
   };
   virtual void encryptWithReverse(const std::string & toEncrypt, std::string & toStoreTo);
   virtual void encryptWithMatrix(const std::string & toEncrypt, std::string & toStoreTo);
   
   virtual void decryptWithReverse(const std::string & toEncrypt, std::string & toStoreTo);
   virtual void decryptWithMatrix(const std::string & toEncrypt, std::string & toStoreTo);
   
   virtual void encrypt(const std::string & toEncrypt, std::string & toStoreTo, Method m);
   virtual void decrypt(const std::string & toDecrypt, std::string & toStoreTo, Method m);
   
};


#pragma GCC visibility pop


#endif /* EasyCryptoLibBad_h */
