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

#include <EasyCryptoPlugin/EasyCryptoLib.hpp>

#include "CryptoServer.hpp"

CryptoServer::CryptoServer(boost::asio::io_service & io_service, short port)
: socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {
   doReceive();
}

void CryptoServer::doReceive() {
   std::memset(data_, 0, sizeof data_);
   std::cout << "Start reading from socket..." << std::endl;
   socket_.async_receive_from(boost::asio::buffer(data_, ECServerAPI::MaxPackageLen), sender_endpoint_,
                              [this](boost::system::error_code ec, std::size_t bytes_recvd)
                              {
                                 if (!ec && bytes_recvd > 0) {
                                    std::string arrived(data_, bytes_recvd);
                                    response = arrived;
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
  <li>Stream the string to nlohmann::json.</li>
  <li>Check if the value is_object, and then if yes,</li>
  <li>Read what kind of message arrived.</li>
  <li>Then handle the request from the client.</li></ul>
  Handling should produce a string which then is sent
 back to the client using socket_.async_send_to.
  @param length The length of the data_.
*/
void CryptoServer::doSendResponse(std::size_t length) {
   if (response == "ping") {
      response = "pong";
   } else {
      // From the string, create a json "thing" and handle the request, creating a response.
      // Send the response to the server using the code after the else branch (see the code...).
      nlohmann::json value;
      std::stringstream str(response);
      try {
         str >> value;
         if (value.is_object()) {
            int msgType = value["msgtype"].get<int>();
            std::cout << "msgtype value: " << msgType << std::endl;
            response = handleRequest(msgType, value);
         }
      } catch (std::exception & e) {
         std::cout << "Exception in handleRequest: " << e.what() << std::endl;
         response = "{ \"msgtype\":999, \"text\": \"Invalid json message structure from client.\"}";
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
std::string CryptoServer::handleRequest(int msgType, const nlohmann::json & value) {
   using namespace EasyCrypto;
   
   nlohmann::json responseJson;
   switch (msgType) {
      case ECServerAPI::Requests::Capability: { // capabilities request
         // Refresh the available plugins.
         // If new plugings were installed after last init call, those are now loaded.
         EasyCrypto::EasyCryptoLib::init("/usr/local/lib/ECPlugins");
         responseJson["msgtype"] = ECServerAPI::Response::Capabilities;
         responseJson["version"] = EasyCryptoLib::version();
         responseJson["ServerAPI"] = ECServerAPI::Constants::ServerAPIVersion;
         

         std::string meths = EasyCryptoLib::methods();
         std::vector<std::string> supportedMethods;
         boost::split(supportedMethods, meths, boost::is_any_of(",;:"));
         nlohmann::json methodsArray = supportedMethods;
         std::cout << "appending array to response" << std::endl;
         responseJson["methods"] = methodsArray;
         std::cout << "done with constructing response" << std::endl;
         break;
      }
      case ECServerAPI::Requests::Encrypt: { // encryption request
         std::string plainText = value["text"].get<std::string>();
         std::string method = value["method"].get<std::string>();
         std::string encrypted;

         EasyCryptoLib::Result r = EasyCryptoLib::encrypt(plainText, encrypted, method);
         
         responseJson["requestid"] = value["requestid"].get<int>();
         switch (r) {
            case EasyCryptoLib::ESuccess: {
               responseJson["msgtype"] = ECServerAPI::Response::Encrypted;
               responseJson["text"] = encrypted;
               std::cout << "Success with encryption method: " << encrypted << std::endl;
               break;
            }
            case EasyCryptoLib::EError: {
               responseJson["msgtype"] = ECServerAPI::Response::Error;
               responseJson["text"] = "ERROR IN ENCRYPTION";
               std::cout << "Error with encryption method!" << std::endl;
               break;
            }
            default:
            case EasyCryptoLib::ENotSupported: {
               responseJson["msgtype"] = ECServerAPI::Response::Error;
               responseJson["text"] = "NOT SUPPORTED";
               std::cout << "Method not supported!" << std::endl;
               break;
            }
         }
         std::cout << "done with constructing response" << std::endl;
         break;
      }
      case ECServerAPI::Requests::Decrypt: { // decryption request
         std::string encrypted = value["text"].get<std::string>();
         std::string method = value["method"].get<std::string>();
         std::string plainText;
         
         EasyCryptoLib::Result r = EasyCrypto::EasyCryptoLib::decrypt(encrypted, plainText, method);

         responseJson["requestid"] = value["requestid"].get<int>();
         switch (r) {
            case EasyCryptoLib::ESuccess: {
               responseJson["msgtype"] = ECServerAPI::Response::Decrypted;
               responseJson["text"] = plainText;
               std::cout << "Success with decryption method!" << std::endl;
               break;
            }
            case EasyCryptoLib::EError: {
               responseJson["msgtype"] = ECServerAPI::Response::Error;
               responseJson["text"] = "ERROR IN DECRYPTION";
               std::cout << "Error with decryption method!" << std::endl;
               break;
            }
            default:
            case EasyCryptoLib::ENotSupported: {
               responseJson["msgtype"] = ECServerAPI::Response::Error;
               responseJson["text"] = "NOT SUPPORTED";
               std::cout << "Method not supported!" << std::endl;
               break;
            }
         }
         std::cout << "done with constructing response" << std::endl;
         break;
      }
      default: {
         responseJson["requestid"] = value["requestid"].get<int>();
         responseJson["msgtype"] = ECServerAPI::Response::Error;
         responseJson["text"] = "NOT SUPPORTED";
         std::cout << "Message type not supported!" << std::endl;
         break;
      }
   }
   std::cout << "convert response to string" << std::endl;
   std::stringstream output;
   output << responseJson;
   return output.str();
}


