/*
 EasyCryptoLib.cpp
 EasyCryptoLib
 
 Created by Antti Juustila on 3.5.2016.
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

#include <memory>
#include <iostream>

#include <boost/dll/shared_library.hpp>
#include <boost/make_shared.hpp>
#include <boost/container/map.hpp>
#include <boost/filesystem.hpp>

#include <boost/dll/smart_library.hpp>
#include <boost/dll/import_mangled.hpp>
#include <boost/dll/import_class.hpp>

#include <EasyCryptoPlugin/EasyCryptoLib.hpp>
#include <EasyCryptoPlugin/EasyCryptoPluginAPI.hpp>

namespace EasyCrypto {

   //MARK: - Static variables
   // Name => plugin
   typedef boost::container::map<std::string, boost::dll::experimental::smart_library> plugins_t;
   
   // Where to search for the plugin dlls. Must be set by calling EasyCryptoLib::init.
   static boost::filesystem::path         pluginsDirectory;
   // Here in the map, the plugins are stored, searchable with the encryption method name.
   static plugins_t                       plugins;
   
   //MARK: - Helper functions
   // Check if the file name contains a dynamic library extension.
   bool isSharedLibrary(const std::string& s) {
      return (s.find(".dll") != std::string::npos || s.find(".so") != std::string::npos || s.find(".dylib") != std::string::npos)
      && s.find(".lib") == std::string::npos
      && s.find(".exp") == std::string::npos
      && s.find(".pdb") == std::string::npos
      && s.find(".manifest") == std::string::npos
      && s.find(".rsp") == std::string::npos
      && s.find(".obj") == std::string::npos
      && s.find(".a") == std::string::npos;
   }
   
   bool isSharedLibrary(const char* p) {
      return isSharedLibrary(std::string(p));
   }
   
   bool isSharedLibrary(const boost::filesystem::path& p) {
      return isSharedLibrary(p.string());
   }

   boost::filesystem::path dropVersion(const boost::filesystem::path& lhs) {
      boost::filesystem::path ext = lhs.filename().extension();
      if (ext.native().size() > 1 && std::isdigit(ext.string()[1])) {
         ext = lhs;
         ext.replace_extension().replace_extension().replace_extension();
         return ext;
      }
      return lhs;
   }

   //MARK: - Loading plugins

   // Insert the plugin to the map with the encryption method name, if create_plugin function exists in the plugin dll.
   void insertPlugin(BOOST_RV_REF(boost::dll::experimental::smart_library) lib) {
      std::string plugin_name;
      if (lib.has("create_plugin")) {
         plugin_name = lib.shared_lib().get_alias<boost::shared_ptr<EasyCryptoPluginAPI>()>("create_plugin")()->method();
      } else if (lib.has("plugin")) {
         plugin_name = lib.shared_lib().get<EasyCryptoPluginAPI>("plugin").method();
      } else {
         return;
      }
      // Check that do not insert plugin with same method name twice.
      if (plugins.find(plugin_name) == plugins.cend()) {
         plugins.insert(std::pair<std::string, boost::dll::experimental::smart_library>(plugin_name, boost::move(lib)));
      }
   }

   // Go recursively through the plugin directory to search for encryption plugin dll's.
   static void loadPlugins() {
      namespace fs = ::boost::filesystem;
      typedef fs::path::string_type string_type;
      const string_type extension = boost::dll::shared_library::suffix().native();
      
      // Searching a folder for files with dynamic library extensions (.so, .dll, .dylib)
      fs::recursive_directory_iterator endit;
      for (fs::recursive_directory_iterator it(pluginsDirectory); it != endit; ++it) {
         if (!fs::is_regular_file(*it)) {
            continue;
         }
         if ( !isSharedLibrary((*it).path()) ) {
            continue;
         }
         // We found a file. Trying to load it
         boost::system::error_code error;
         boost::dll::experimental::smart_library plugin(it->path(), error);
         if (error) {
            continue;
         }
         
         // Gets plugin using "create_plugin" or "plugin" function
         insertPlugin(boost::move(plugin));
      }
   }
   
   //MARK: - API Class EasyCryptoLib implementation.
   // For documentation, see header file.
   const std::string & EasyCryptoLib::version() {
      static const std::string versionNumber("1.0.0");
      return versionNumber;
   }
   
   void EasyCryptoLib::init(const std::string & pathToPlugins) {
      plugins.clear();
      pluginsDirectory = pathToPlugins;
      loadPlugins();
   }
   
   std::string EasyCryptoLib::methods() {
      std::string methods;
      int pluginCount = plugins.size();
      int pluginCounter = 0;
      for (plugins_t::iterator iter = plugins.begin(); iter != plugins.end(); iter++, pluginCounter++) {
         methods += iter->first;
         if (pluginCounter < pluginCount-1) {
            methods += ",";
         }
      }
      return methods;
   }
   
   EasyCryptoLib::Result EasyCryptoLib::encrypt(const std::string & toEncrypt, std::string & toStoreTo, const std::string & method) {
      try {
         boost::dll::experimental::smart_library & lib = plugins.at(method);
         if (lib.is_loaded()) {
            auto encrypter = lib.shared_lib().get_alias<boost::shared_ptr<EasyCryptoPluginAPI>()>("create_plugin")();
            encrypter->encrypt(toEncrypt, toStoreTo);
            return ESuccess;
         } else {
            return EError;
         }
      } catch (std::exception & e) {
         std::cout << e.what() << std::endl;
         return EError;
      }
      return ENotSupported;
   }
   
   
   EasyCryptoLib::Result EasyCryptoLib::decrypt(const std::string & toDecrypt, std::string & toStoreTo, const std::string & method) {
      try {
         boost::dll::experimental::smart_library & lib = plugins.at(method);
         if (lib.is_loaded()) {
            auto decrypter = lib.shared_lib().get_alias<boost::shared_ptr<EasyCryptoPluginAPI>()>("create_plugin")();
            decrypter->decrypt(toDecrypt, toStoreTo);
            return ESuccess;
         } else {
            return EError;
         }
      } catch (std::exception & e) {
         return EError;
      }
      return ENotSupported;
   }
   
} // namespace
