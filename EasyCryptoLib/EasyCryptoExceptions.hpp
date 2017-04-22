/*
 EasyCryptoExceptions.h
 EasyCryptoLib

 Created by Antti Juustila on 31.5.2016.
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

#ifndef EasyCryptoExceptions_h
#define EasyCryptoExceptions_h

#include "ECMasterHeader.hpp"

namespace EasyCrypto {
   
class EC_API not_supported : public std::logic_error
{
public:
   not_supported() : std::logic_error("Not supported") {}
};

} // namespace


#endif /* EasyCryptoExceptions_h */
