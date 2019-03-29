/*
 EasyCryptoPlugin.cpp
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
#include <stdexcept>

#include <boost/make_shared.hpp>

#include "EasyCryptoPlugin.hpp"


namespace EasyCrypto {
   
   EasyCryptoPlugin::EasyCryptoPlugin() {
      // Empty
   }
   
   EasyCryptoPlugin::~EasyCryptoPlugin() {
      // Empty
   }
   std::string EasyCryptoPlugin::method() {
      return "reverse";
   }
   
   void EasyCryptoPlugin::encrypt(const std::string & toEncrypt, std::string & toStoreTo) {
      if (toEncrypt.length() < 1) {
         throw std::runtime_error("Empty string");
      }
      toStoreTo = toEncrypt;
      std::reverse(toStoreTo.begin(), toStoreTo.end());
   };
   
   void EasyCryptoPlugin::decrypt(const std::string & toDecrypt, std::string & toStoreTo) {
      if (toDecrypt.length() < 1) {
         throw std::runtime_error("Empty string");
      }
      encrypt(toDecrypt, toStoreTo);
   }
   
   boost::shared_ptr<EasyCryptoPluginAPI> create_plugin() {
      return boost::make_shared<EasyCryptoPlugin>();
   }
   
} // namespace

