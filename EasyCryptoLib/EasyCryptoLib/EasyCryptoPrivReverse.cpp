/*
 EasyCryptoPrivReverse.cpp
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

#include <algorithm>

#include "EasyCryptoPrivReverse.hpp"

namespace EasyCrypto {

const std::string EasyCryptoPrivReverse::methodName("reverse");

void EasyCryptoPrivReverse::encrypt(const std::string & toEncrypt, std::string & toStoreTo) {
   toStoreTo = toEncrypt;
   std::reverse(toStoreTo.begin(), toStoreTo.end());
};

void EasyCryptoPrivReverse::decrypt(const std::string & toDecrypt, std::string & toStoreTo) {
   encrypt(toDecrypt, toStoreTo);
}

const std::string & EasyCryptoPrivReverse::method() const {
   return methodName;
}

} // namespace