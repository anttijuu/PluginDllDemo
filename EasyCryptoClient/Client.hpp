//
//  Client.hpp
//  EasyCryptoClient
//
//  Created by Antti Juustila on 2.6.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#ifndef Client_h
#define Client_h

#include <chrono>

#include <boost/asio.hpp>

namespace Json {
   class Value;
}

/////////////////////////////////////////////////////////////////////////////////////////


class Client {
public:
   Client();
   int mainFunc(int argc, char * argv[]);
   
private:
   
   void handleCapabilityRequest();
   void handleEncryptionRequest();
   void handleDecryptionRequest();
   void handlePingMessage();
   void sendTestRequests();
   
   // Remove all methods here from code given to students.
   bool isMethodSupported(const std::string & method) const;
   void printSupportedMethods() const;
   int createRequestId() const;
   void printJsonMsg(const Json::Value & json) const;
   std::string askMethodOfEncryption() const;
   
private:
   boost::asio::io_service io_service;
   
   boost::asio::ip::udp::socket s;
   
   boost::asio::ip::udp::resolver resolver;
   boost::asio::ip::udp::endpoint endpoint;
   
   
   std::chrono::system_clock::time_point started;
   std::vector<std::string> supportedMethods;
   bool printDetails;
   
   enum { max_length = 4096 };

};
#endif /* Client_h */
