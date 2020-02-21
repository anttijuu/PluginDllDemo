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
#include <iostream>
#include <codecvt>

#include <boost/make_shared.hpp>

// #include <utf8cpp/utf8.h>

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
      toStoreTo.clear();
      toStoreTo.resize(toEncrypt.size());
      std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cvt;
      utf8::iterator iter(toEncrypt.begin(), toEncrypt.end(), toEncrypt.begin());
      utf8::iterator end(toEncrypt.begin(), toEncrypt.begin(), toEncrypt.end());
      // utf8::iterator target(toStoreTo.end(), toStoreTo.end(), toStoreTo.begin());
      while (iter != end) {
         utf8::append(*iter, toStoreTo);
         // target.insert(toStoreTo.begin(), *iter);
         iter++;
      }
//      for (char32_t c: cvt.from_bytes(toEncrypt)) {
//         // toStoreTo += c;
//         toStoreTo.insert(toStoreTo.begin(), c);
//         std::cout << c << std::endl;
//      }
      //      toStoreTo.reserve(toEncrypt.size());
      //      utf8::iterator iter(toEncrypt.end(), toEncrypt.begin(), toEncrypt.end());
      //      utf8::iterator begin(toEncrypt.begin(), toEncrypt.begin(), toEncrypt.end());
      //      // utf8::iterator target(toStoreTo.begin(), toStoreTo.begin(), toStoreTo.end());
      //      int loopcount = 0;
      //      auto target = toStoreTo.begin();
      //      while (iter != begin) {
      //         std::cout << "Loop #" << loopcount << std::endl;
      //         // toStoreTo.push_back(*iter);
      //         utf8::append(*iter, target);
      //         --iter;
      //      }
      //toStoreTo = toEncrypt;
      //std::reverse(toStoreTo.begin(), toStoreTo.end());
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

