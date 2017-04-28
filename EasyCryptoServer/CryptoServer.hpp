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


namespace Json {
   class Value;
}

class CryptoServer
{
public:
   CryptoServer(boost::asio::io_service & io_service, short port);
      
private:
   void doReceive();
   void doSendResponse(std::size_t length);
   // Remove the method below when giving code to students
   std::string handleRequest(int msgType, const Json::Value & value);
   
private:
   boost::asio::ip::udp::socket socket_;
   boost::asio::ip::udp::endpoint sender_endpoint_;
   enum { max_length = 4096 };
   char data_[max_length];
   

};


#endif /* CryptoServer_hpp */
