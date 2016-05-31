/*
 EasyCryptoPrivReverse.hpp
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
