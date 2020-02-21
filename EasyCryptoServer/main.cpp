//
//  main.cpp
//  EasyCryptoServer
//
//  Created by Antti Juustila on 10.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#include <iostream>

#include "CryptoServer.hpp"

int main(int argc, const char * argv[]) {
   try
   {
      // setlocale(LC_CTYPE, "");
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
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}
