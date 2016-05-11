//
//  main.cpp
//  EasyCryptoServer
//
//  Created by Antti Juustila on 10.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#include <iostream>
#include <boost/asio.hpp>

#include "CryptoServer.hpp"

// TODO: specify JSON structures
// - query server capabilities (crypto methods) + lib version number
// - send text to be en/decrypted (with a method)
// - reply from the server with en/decrypted text
// TODO: implement JSON parsing and creation
// TODO: implement datagram socket API for receiving requests and replying

int main(int argc, const char * argv[]) {
   try
   {
      short port = 0;
      if (argc != 2)
      {
         std::cout << "Usage: EasyCryptoServer <port>" << std::endl;
         port = 10000;
      } else {
         port = std::atoi(argv[1]);
      }
      std::cout << "Using port: " << port << std::endl;
      
      boost::asio::io_service io_service;
      
      CryptoServer server(io_service, port);
      
      io_service.run();
   } catch (std::exception & e) {
      std::cerr << "Exception: " << e.what() << "\n";
   }
   return 0;
}
