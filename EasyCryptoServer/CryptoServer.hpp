//
//  CryptoServer.hpp
//  EasyCryptoServer
//
//  Created by Antti Juustila on 10.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#ifndef CryptoServer_hpp
#define CryptoServer_hpp

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <nlohmann/json.hpp>

#include "ServerAPI.hpp"

class CryptoServer
{
public:
   CryptoServer(boost::asio::io_service & io_service, short port);
      
private:
   void doReceive();
   void doSendResponse(std::size_t length);
   // Remove the method below when giving code to students
   std::string handleRequest(int msgType, const nlohmann::json & value);
   
private:
   boost::asio::ip::udp::socket socket_;
   boost::asio::ip::udp::endpoint sender_endpoint_;
   char data_[ECServerAPI::MaxPackageLen];
   std::string response;

};


#endif /* CryptoServer_hpp */
