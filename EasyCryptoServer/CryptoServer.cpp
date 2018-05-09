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

#include <json/json.h>

#include <EasyCrypto/EasyCryptoLib.hpp>

#include "CryptoServer.hpp"

CryptoServer::CryptoServer(boost::asio::io_service & io_service, short port)
: socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {
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
   if (response == "ping") {
      response = "pong";
   } else {
      // Remove starting from here when giving code to students...
      // From the string, create a json "thing" and handle the request, creating a response.
      // Send the response to the server using the code after the else branch (see the code...).
      Json::Value value;
      std::stringstream str(response);
      try {
         str >> value;
         if (value.isObject()) {
            int msgType = value["msgtype"].asInt();
            std::cout << "msgtype value: " << msgType << std::endl;
            response = handleRequest(msgType, value);
         }
        // ..until here, code removed when giving code to students.
      } catch (std::exception & e) {
         response = "invalid json message structure from client";
      }
      
   }
   if (response.length() > 0) {
      std::cout << "Sending response : " << response << std::endl;
      socket_.async_send_to(boost::asio::buffer(response, response.length()), sender_endpoint_,
                            [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
                            {
                               doReceive();
                            });
   }
}

// Remove the whole method below when giving code to students.
std::string CryptoServer::handleRequest(int msgType, const Json::Value & value) {
   using namespace EasyCrypto;
   
   Json::Value response(Json::objectValue);
   switch (msgType) {
      case 1: { // capabilities request
         response["msgtype"] = 2;
         response["version"] = EasyCryptoLib::version();
         Json::Value methodsArray(Json::arrayValue);

         std::string meths = EasyCryptoLib::methods();
         std::vector<std::string> supportedMethods;
         boost::split(supportedMethods, meths, boost::is_any_of(",;:"));

         for (std::string method : supportedMethods) {
            std::cout << "appending methods" << std::endl;
            methodsArray.append(method);
         }
         std::cout << "appending array to response" << std::endl;
         response["methods"] = methodsArray;
         std::cout << "done with constructing response" << std::endl;
         break;
      }
      case 3: { // encryption request
         std::string plainText = value["text"].asString();
         std::string method = value["method"].asString();
         std::string encrypted;

         EasyCryptoLib::Result r = EasyCryptoLib::encrypt(plainText, encrypted, method);
         
         response["requestid"] = value["requestid"].asInt();
         switch (r) {
            case EasyCryptoLib::ESuccess: {
               response["msgtype"] = 4;
               response["text"] = encrypted;
               break;
            }
            case EasyCryptoLib::EError: {
               response["msgtype"] = 999;
               response["text"] = "ERROR IN ENCRYPTION";
               std::cout << "Error with reverse method!" << std::endl;
               break;
            }
            default:
            case EasyCryptoLib::ENotSupported: {
               response["msgtype"] = 999;
               response["text"] = "NOT SUPPORTED";
               std::cout << "Method not supported!" << std::endl;
               break;
            }
         }
         std::cout << "done with constructing response" << std::endl;
         break;
      }
      case 5: { // decryption request
         std::string encrypted = value["text"].asString();
         std::string method = value["method"].asString();
         std::string plainText;
         
         EasyCryptoLib::Result r = EasyCrypto::EasyCryptoLib::decrypt(encrypted, plainText, method);

         response["requestid"] = value["requestid"].asInt();
         switch (r) {
            case EasyCryptoLib::ESuccess: {
               response["msgtype"] = 6;
               response["text"] = plainText;
               std::cout << "Success with decryption method!" << std::endl;
               break;
            }
            case EasyCryptoLib::EError: {
               response["msgtype"] = 999;
               response["text"] = "ERROR IN DECRYPTION";
               std::cout << "Error with decryption method!" << std::endl;
               break;
            }
            default:
            case EasyCryptoLib::ENotSupported: {
               response["msgtype"] = 999;
               response["text"] = "NOT SUPPORTED";
               std::cout << "Method not supported!" << std::endl;
               break;
            }
         }
         std::cout << "done with constructing response" << std::endl;
         break;
      }
      default: {
         response["requestid"] = value["requestid"].asInt();
         response["msgtype"] = 999;
         response["text"] = "NOT SUPPORTED";
         std::cout << "Message type not supported!" << std::endl;
         break;
      }
   }
   std::cout << "convert response to string" << std::endl;
   return response.toStyledString();
}


