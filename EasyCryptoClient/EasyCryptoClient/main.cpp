//
//  main.cpp
//  EasyCryptoClient
//
//  Created by Antti Juustila on 10.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>

#include "json.h"

using boost::asio::ip::udp;

class Client {
public:
   Client();
   int mainFunc(int argc, char * argv[]);
   
private:
   
   void handleCapabilityRequest();
   void handleEncryptionRequest();
   void handleDecryptionRequest();
   
   bool isMethodSupported(const std::string & method) const;
   void printSupportedMethods() const;
   int createRequestId() const;
   void printJsonMsg(const Json::Value & json) const;
   std::string askMethodOfEncryption() const;
   
private:
   boost::asio::io_service io_service;
   
   udp::socket s;
   
   udp::resolver resolver;
   udp::endpoint endpoint;
   
   std::chrono::system_clock::time_point started;
   std::vector<std::string> supportedMethods;
   
   bool printDetails;
};

enum { max_length = 4096 };
static const std::string clientVersion("1.0.0");

int main (int argc, char* argv[]) {
   Client client;
   
   return client.mainFunc(argc, argv);
}

Client::Client()
: s(io_service, udp::endpoint(udp::v4(), 0)), resolver(io_service), printDetails(false) {
   started = std::chrono::system_clock::now();
}

int Client::mainFunc(int argc, char* argv[]) {
   if (argc != 3) {
      std::cerr << "Usage: EasyCryptoClient <host> <port>\n";
      return 1;
   }
   
   endpoint = *resolver.resolve({udp::v4(), argv[1], argv[2]});
   
   int command = 0;
   char request[max_length];
   do {
      try {
         std::cout << std::endl << "---------------------------------" << std::endl;
         std::cout << "Menu of commands" << std::endl;
         std::cout << "1  >> Send capability request to server" << std::endl;
         std::cout << "2  >> Send encryption request to server" << std::endl;
         std::cout << "3  >> Send decryption request to server" << std::endl;
         std::cout << "99 >> Toggle print details" << std::endl;
         std::cout << "0 or Enter >> Exit client" << std::endl;
         std::cout << "Enter command >> ";
         std::cin.getline(request, max_length);
         command = std::atoi(request);
         switch (command) {
            case 1: {
               handleCapabilityRequest();
               break;
            }
            case 2: {
               handleEncryptionRequest();
               break;
            }
            case 3: {
               handleDecryptionRequest();
               break;
            }
            case 99: {
               printDetails = !printDetails;
               break;
            }
            default: {
               break;
            }
         }
      } catch (std::exception& e) {
         std::cerr << "SOS SOS SOS SOS SOS SOS SOS SOS SOS SOS SOS SOS SOS SOS SOS " << std::endl;
         std::cerr << "Exception: " << e.what() << std::endl;
      }
   } while (command > 0);
   
   std::cout << "Bye!" << std::endl;
   return 0;
}

void Client::handleCapabilityRequest() {
   std::cout << " *** Sending Capability Message to Server *** " << std::endl;
   
   Json::Value message(Json::objectValue);
   message["msgtype"] = 1;
   message["version"] = clientVersion;
   
   printJsonMsg(message);
   
   s.send_to(boost::asio::buffer(message.toStyledString()), endpoint);
   
   char reply[max_length];
   udp::endpoint sender_endpoint;
   size_t reply_length = s.receive_from(boost::asio::buffer(reply, max_length), sender_endpoint);
   
   std::string response(reply, reply_length);
   std::stringstream stream(response);
   Json::Value value;
   stream >> value;
   printJsonMsg(value);
   if (value.isObject()) {
      int msgType = value["msgtype"].asInt();
      if (msgType == 2) {
         supportedMethods.clear();
         Json::Value array(Json::arrayValue);
         array = value["methods"];
         for (Json::ArrayIndex index = 0; index < array.size(); index++) {
            std::string method = array[index].asString();
            supportedMethods.push_back(method);
         }
         printSupportedMethods();
      } else {
         throw new std::invalid_argument("wrong response to msgtype 1 from server");
      }
   }
}

void Client::handleEncryptionRequest() {
   std::cout << " *** Sending Message to Encrypt to Server *** " << std::endl;
   std::string text;
   std::string method;
   std::cout << "Give the text to encrypt: ";
   std::getline(std::cin, text);
   
   method = askMethodOfEncryption();
   
   int requestId = createRequestId();
   
   Json::Value message(Json::objectValue);
   message["msgtype"] = 3;
   message["text"] = text;
   message["method"] = method;
   message["requestid"] = requestId;

   printJsonMsg(message);
   
   s.send_to(boost::asio::buffer(message.toStyledString()), endpoint);
   
   char reply[max_length];
   udp::endpoint sender_endpoint;
   size_t reply_length = s.receive_from(boost::asio::buffer(reply, max_length), sender_endpoint);
   
   std::string response(reply, reply_length);
   std::stringstream stream(response);
   Json::Value value;
   stream >> value;
   printJsonMsg(value);
   if (value.isObject()) {
      int msgType = value["msgtype"].asInt();
      if (msgType == 4) {
         std::cout << "Encrypted text is: ";
         std::cout << value["text"].asString() << std::endl;
      } else {
         throw new std::invalid_argument("wrong response to msgtype 3 from server");
      }
   }
}

void Client::handleDecryptionRequest() {
   std::string text;
   std::string method;
   std::cout << "Give the text to decrypt: ";
   std::getline(std::cin, text);
   
   method = askMethodOfEncryption();
   
   int requestId = createRequestId();

   Json::Value message(Json::objectValue);
   message["msgtype"] = 5;
   message["text"] = text;
   message["method"] = method;
   message["requestid"] = requestId;
   
   printJsonMsg(message);
   
   s.send_to(boost::asio::buffer(message.toStyledString()), endpoint);
   
   char reply[max_length];
   udp::endpoint sender_endpoint;
   size_t reply_length = s.receive_from(boost::asio::buffer(reply, max_length), sender_endpoint);
   
   std::string response(reply, reply_length);
   std::stringstream stream(response);
   Json::Value value;
   stream >> value;
   printJsonMsg(value);
   if (value.isObject()) {
      int msgType = value["msgtype"].asInt();
      if (msgType == 6) {
         std::cout << "Decrypted text is: ";
         std::cout << value["text"].asString() << std::endl;
      } else {
         throw new std::invalid_argument("wrong response to msgtype 5 from server");
      }
   }
}

bool Client::isMethodSupported(const std::string & method) const {
   for (std::string m : supportedMethods) {
      if (m == method) {
         return true;
      }
   }
   return false;
}

void Client::printSupportedMethods() const {
   std::cout << "Supported encryption methods are: ";
   for (std::string m : supportedMethods) {
      std::cout << " " << m;
   }
   std::cout << std::endl;
}

int Client::createRequestId() const {
   std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
   std::stringstream str;
   str << std::chrono::duration_cast<std::chrono::milliseconds>(now-started).count();
   int requestId = 0;
   str >> requestId;
   return requestId;
}

void Client::printJsonMsg(const Json::Value & json) const {
   if (printDetails) {
      std::cout << json.toStyledString() << std::endl;
   }
}

std::string Client::askMethodOfEncryption() const {
   std::string method;
   bool methodOK = false;
   do {
      std::cout << "Give the method of encryption: ";
      std::getline(std::cin, method);
      methodOK = isMethodSupported(method);
      if (!methodOK) {
         std::cout << "Not supported, select from: ";
         printSupportedMethods();
      }
      
   } while (!methodOK);
   return method;
}