//
//  main.cpp
//  CryptoClientConsole
//
//  Created by Antti Juustila on 4.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#include <iostream>

#include <EasyCryptoLib.hpp>
#include <EasyCryptoLibBad.hpp>

void usingGoodLib();
void usingBadLib();

int main(int argc, const char * argv[]) {
   
   bool userWantsIt = false;
   do {
      usingGoodLib();
      usingBadLib();
      
      std::string result;
      std::cout << "Press y and enter to continue, or just enter to quit: ";
      std::getline(std::cin, result);
      if (result.compare("y") == 0) {
         userWantsIt = true;
      } else {
         userWantsIt = false;
      }
   } while (userWantsIt);
   std::cout << "Thanks and bye! " << std::endl;
   
   return 0;
}


void usingGoodLib() {
   std::cout << std::endl << "Welcome to Good EasyCrypto(tm)!" << std::endl;
   std::cout << "Enter text to encrypt: ";
   
   std::string userString;
   std::string result;
   std::getline(std::cin, userString);
   
   using namespace EasyCrypto;
   
   EasyCryptoLib::encrypt(userString, result, "reverse");
   std::cout << "Text encrypted with Reverse method: ";
   std::cout << result << std::endl;
   std::cout << "Decrypting back to original: ";
   EasyCryptoLib::decrypt(result, userString, "reverse");
   std::cout << userString << std::endl << std::endl;
   
//   EasyCryptoLib::encrypt(userString, result, "matrix");
//   std::cout << "Text encrypted with Matrix method: ";
//   std::cout << result << std::endl;
//   std::cout << "Decrypting back to original: ";
//   EasyCryptoLib::decrypt(result, userString, "matrix");
//   std::cout << userString << std::endl << std::endl;
   
}

void usingBadLib() {
   std::cout << "==============================" << std::endl;
   std::cout << "Welcome to Bad EasyCrypto(tm)!" << std::endl;
   std::cout << "Enter text to encrypt: ";
   
   std::string userString;
   std::string result;
   std::getline(std::cin, userString);
   
   using namespace EasyCrypto;
   
   std::unique_ptr<EasyCryptoLibBad> crypter(new EasyCryptoLibBad());
   
   crypter->encrypt(userString, result, EasyCryptoLibBad::Method::Reverse);
   std::cout << "Text encrypted with Reverse method: ";
   std::cout << result << std::endl;
   std::cout << "Decrypting back to original: ";
   crypter->decrypt(result, userString, EasyCryptoLibBad::Method::Reverse);
   std::cout << userString << std::endl << std::endl;
   
//   crypter->encrypt(userString, result, EasyCryptoLibBad::Method::Matrix);
//   std::cout << "Text encrypted with Matrix method: ";
//   std::cout << result << std::endl;
//   std::cout << "Decrypting back to original: ";
//   crypter->decrypt(result, userString, EasyCryptoLibBad::Method::Matrix);
//   std::cout << userString << std::endl << std::endl;
   
}
