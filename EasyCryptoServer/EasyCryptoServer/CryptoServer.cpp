//
//  CryptoServer.cpp
//  EasyCryptoServer
//
//  Created by Antti Juustila on 10.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//


#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>

#include "CryptoServer.hpp"
#include <json/json.h>
#include "EasyCryptoLib.hpp"

CryptoServer::CryptoServer(boost::asio::io_service & io_service, short port)
: socket_(io_service, udp::endpoint(udp::v4(), port)) {
   doReceive();
}

void CryptoServer::doReceive() {
   std::cout << "Start reading from socket..." << std::endl;
   socket_.async_receive_from(boost::asio::buffer(data_, max_length), sender_endpoint_,
                              [this](boost::system::error_code ec, std::size_t bytes_recvd)
                              {
                                 if (!ec && bytes_recvd > 0) {
                                    std::string arrived(data_, bytes_recvd);
                                    std::cout << "Data arrived: " << arrived << std::endl;
                                    doSendResponse(bytes_recvd);
                                 } else {
                                    doReceive();
                                 }
                              });
}

 /**
  Handles the received JSON from the client and produces an
  appropriate JSON response and sends it back to the client.
  Steps include:
  <ul><li>Parse the json request from data_ by creating a string 
  from data_ and putting it to a stringstream.</li>
  <li>Stream the string to Json::Value.</li>
  <li>Check if the value isObject, and then if yes,</li>
  <li>Read what kind of message arrived.</li>
  <li>Then handle the request from the client.</li></ul>
  Handling should produce a string which then is sent
 back to the client using socket_.async_send_to.
  @param length The length of the data_.
*/
void CryptoServer::doSendResponse(std::size_t length) {
   std::string response(data_, length);
   Json::Value value;
   std::stringstream str(response);
   try {
      str >> value;
      if (value.isObject()) {
         int msgType = value["msgtype"].asInt();
         std::cout << "msgtype value: " << msgType << std::endl;
         response = handleRequest(msgType, value);
      }
   } catch (std::exception & e) {
      response = "invalid json message structure from client";
   }
   
   std::cout << "Sending response : " << response << std::endl;
   socket_.async_send_to(boost::asio::buffer(response, response.length()), sender_endpoint_,
                         [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
                         {
                            doReceive();
                         });
}

std::string CryptoServer::handleRequest(int msgType, const Json::Value & value) {
   Json::Value response(Json::objectValue);
   switch (msgType) {
      case 1: { // capabilities request
         std::cout << "setting msgtype" << std::endl;
         response["msgtype"] = 2;
         std::cout << "setting version" << std::endl;
         response["version"] = EasyCrypto::version();
         Json::Value methodsArray(Json::arrayValue);
         std::vector<std::string> methods;
         boost::split(methods, EasyCrypto::methods(), boost::is_any_of(",;:"));
         for (std::string method : methods) {
            std::cout << "appending methods" << std::endl;
            methodsArray.append(method);
         }
         std::cout << "appending array to response" << std::endl;
         response["methods"] = methodsArray;
         std::cout << "done with constructing response" << std::endl;
         break;
      }
      case 3: { // encryption request
         std::cout << "setting msgtype" << std::endl;
         response["msgtype"] = 4;
         std::string plainText = value["text"].asString();
         std::string method = value["method"].asString();
         std::string encrypted;
         // Todo: check that method is in the list of supported methods
         if (method == "matrix") {
            EasyCrypto::encrypt(plainText, encrypted, EasyCrypto::Method::Matrix);
         } else if (method == "reverse") {
            EasyCrypto::encrypt(plainText, encrypted, EasyCrypto::Method::Reverse);
         } else {
            encrypted = "Not supported";
         }
         response["text"] = encrypted;
         response["requestid"] = value["requestid"].asInt();
         std::cout << "done with constructing response" << std::endl;
         break;
      }
      case 5: {
         std::cout << "setting msgtype" << std::endl;
         response["msgtype"] = 6;
         std::string encrypted = value["text"].asString();
         std::string method = value["method"].asString();
         std::string plainText;
         // Todo: check that method is in the list of supported methods
         if (method == "matrix") {
            EasyCrypto::decrypt(encrypted, plainText, EasyCrypto::Method::Matrix);
         } else if (method == "reverse") {
            EasyCrypto::decrypt(encrypted, plainText, EasyCrypto::Method::Reverse);
         } else {
            encrypted = "Not supported";
         }
         response["text"] = plainText;
         response["requestid"] = value["requestid"].asInt();
         std::cout << "done with constructing response" << std::endl;
         break;
      }
      default: {
         break;
      }
   }
   std::cout << "convert response to string" << std::endl;
   return response.toStyledString();
}
