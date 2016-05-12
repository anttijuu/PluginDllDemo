//
//  CryptoServer.hpp
//  EasyCryptoServer
//
//  Created by Antti Juustila on 10.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#ifndef CryptoServer_hpp
#define CryptoServer_hpp

/*
 For background information, see
 https://github.com/open-source-parsers/jsoncpp
 http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html
 
 and
 
 http://www.boost.org
 http://www.boost.org/users/history/version_1_60_0.html
 */


#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

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
   std::string handleRequest(int msgType, const Json::Value & value);
private:
   udp::socket socket_;
   udp::endpoint sender_endpoint_;
   enum { max_length = 4096 };
   char data_[max_length];
};


#endif /* CryptoServer_hpp */
