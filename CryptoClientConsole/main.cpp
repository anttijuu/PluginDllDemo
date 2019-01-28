//
//  main.cpp
//  CryptoClientConsole
//
//  Created by Antti Juustila on 4.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#include <iostream>

#include <EasyCrypto/EasyCryptoLib.hpp>
#include <EasyCrypto/EasyCryptoLibBad.hpp>

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

    using namespace EasyCrypto;
    
    std::cout << "The supported crypto methods are: " << EasyCryptoLib::methods() << std::endl;
    
    std::cout << std::endl << "Enter text to encrypt: ";
    
    std::string userString;
    std::string result;
    std::getline(std::cin, userString);
    
    
    // Using reverse method
    EasyCryptoLib::Result r = EasyCryptoLib::encrypt(userString, result, "reverse");
    switch (r) {
        case EasyCryptoLib::ESuccess: {
            std::cout << "Text encrypted with Reverse method: ";
            std::cout << result << std::endl;
            break;
        }
        case EasyCryptoLib::EError: {
            std::cout << "Error with reverse method!" << std::endl;
            break;
        }
        case EasyCryptoLib::ENotSupported: {
            std::cout << "Method not supported!" << std::endl;
            break;
        }
    }
    std::cout << "Decrypting back to original: ";
    r = EasyCryptoLib::decrypt(result, userString, "reverse");
    switch (r) {
        case EasyCryptoLib::ESuccess: {
            std::cout << userString << std::endl << std::endl;
            break;
        }
        case EasyCryptoLib::EError: {
            std::cout << "Error!" << std::endl;
            break;
        }
        case EasyCryptoLib::ENotSupported: {
            std::cout << "Not supported!" << std::endl;
            break;
        }
    }
    
    // Using matrix method
    r = EasyCryptoLib::encrypt(userString, result, "matrix");
    switch (r) {
        case EasyCryptoLib::ESuccess: {
            std::cout << "Text encrypted with Matrix method: ";
            std::cout << result << std::endl;
            break;
        }
        case EasyCryptoLib::EError: {
            std::cout << "Error with matrix method!" << std::endl;
            break;
        }
        case EasyCryptoLib::ENotSupported: {
            std::cout << "Not supported!" << std::endl;
            break;
        }
    }
    
    std::cout << "Decrypting back to original: ";
    r = EasyCryptoLib::decrypt(result, userString, "matrix");
    switch (r) {
        case EasyCryptoLib::ESuccess: {
            std::cout << "Text decrypted with Matrix method: ";
            std::cout << userString << std::endl << std::endl;
            break;
        }
        case EasyCryptoLib::EError: {
            std::cout << "Error with matrix method!" << std::endl;
            break;
        }
        case EasyCryptoLib::ENotSupported: {
            std::cout << "Not supported!" << std::endl;
            break;
        }
    }
    
    // Using a method that is unsupported
    std::cout << "Trying to use an unsupported method..." << std::endl;
    r = EasyCryptoLib::encrypt(userString, result, "dingdong");
    switch (r) {
        case EasyCryptoLib::ESuccess: {
            std::cout << "Text encrypted with dingdong method: ";
            std::cout << result << std::endl;
            break;
        }
        case EasyCryptoLib::EError: {
            std::cout << "Error with dingdong method!" << std::endl;
            break;
        }
        case EasyCryptoLib::ENotSupported: {
            std::cout << "Not supported!" << std::endl;
            break;
        }
    }
    
}

#include "../EasyCryptoLib/EasyCryptoExceptions.hpp"

void usingBadLib() {
    std::cout << "==============================" << std::endl;
    std::cout << "Welcome to Bad EasyCrypto(tm)!" << std::endl;
    std::cout << "Enter text to encrypt: ";
    
    std::string userString;
    std::string result;
    std::getline(std::cin, userString);
    
    using namespace EasyCrypto;
    
    std::unique_ptr<EasyCryptoLibBad> crypter(new EasyCryptoLibBad());
    
    try {
        crypter->encrypt(userString, result, EasyCryptoLibBad::Method::Reverse);
        std::cout << "Text encrypted with Reverse method: ";
        std::cout << result << std::endl;
        std::cout << "Decrypting back to original: ";
        crypter->decrypt(result, userString, EasyCryptoLibBad::Method::Reverse);
        std::cout << userString << std::endl << std::endl;
    } catch (EasyCrypto::not_supported & e) {
        std::cout << "Exception, not supported: " << e.what() << std::endl;
    } catch (std::exception & e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    //   try {
    //      crypter->encrypt(userString, result, EasyCryptoLibBad::Method::Matrix);
    //      std::cout << "Text encrypted with Matrix method: ";
    //      std::cout << result << std::endl;
    //      std::cout << "Decrypting back to original: ";
    //      crypter->decrypt(result, userString, EasyCryptoLibBad::Method::Matrix);
    //      std::cout << userString << std::endl << std::endl;
    //   } catch (not_supported & e) {
    //      std::cout << "Exception, not supported: " << e.what() << std::endl;
    //   } catch (std::exception & e) {
    //      std::cout << "Exception: " << e.what() << std::endl;
    //   }
    
    std::cout << "Trying to use an unsupported method..." << std::endl;
    try {
        crypter->encrypt(userString, result, (EasyCryptoLibBad::Method)3);
    } catch (not_supported & e) {
        std::cout << "Exception, not supported: " << e.what() << std::endl;
    } catch (std::exception & e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
}
