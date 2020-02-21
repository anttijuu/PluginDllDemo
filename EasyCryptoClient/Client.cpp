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


#include "Client.hpp"

#include "../EasyCryptoServer/ServerAPI.hpp"




/////////////////////////////////////////////////////////////////////////////////////////


static const std::string clientVersion("1.0.0");


/////////////////////////////////////////////////////////////////////////////////////////


int main (int argc, char* argv[]) {
   //setlocale(LC_CTYPE, "");
   Client client;
   
   return client.mainFunc(argc, argv);
}


/////////////////////////////////////////////////////////////////////////////////////////

using boost::asio::ip::udp;

Client::Client()
: s(io_service, udp::endpoint(udp::v4(), 0)), resolver(io_service), printDetails(false) {
   // Remove the line below from code given to students.
   started = std::chrono::system_clock::now();
}

int Client::mainFunc(int argc, char* argv[]) {
   if (argc != 3) {
      std::cerr << "Usage: EasyCryptoClient <host> <port>\n";
      return EXIT_FAILURE;
   }
   
   endpoint = *resolver.resolve({udp::v4(), argv[1], argv[2]});
   
   int command = 0;
   char request[ECServerAPI::Constants::MaxPackageLen];
   do {
      try {
         std::cout << std::endl << "---------------------------------" << std::endl;
         std::cout << "Menu of commands" << std::endl;
         std::cout << "1  >> Send capability request to server" << std::endl;
         std::cout << "2  >> Send encryption request to server" << std::endl;
         std::cout << "3  >> Send decryption request to server" << std::endl;
         std::cout << "77 >> Send test json message requests to server" << std::endl;
         std::cout << "88  >> Send ping to server" << std::endl;
         std::cout << "99 >> Toggle print details" << std::endl;
         std::cout << "0 or Enter >> Exit client" << std::endl;
         std::cout << "Enter command >> ";
         std::cin.getline(request, ECServerAPI::Constants::MaxPackageLen);
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
            case 77: {
               sendTestRequests();
               break;
            }
            case 88: {
               handlePingMessage();
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
   return EXIT_SUCCESS;
}

void Client::handlePingMessage() {
   std::cout << " *** Sending Ping Message to Server *** " << std::endl;
   const std::string pingMsg("ping");
   s.send_to(boost::asio::buffer(pingMsg), endpoint);
   char reply[ECServerAPI::Constants::MaxPackageLen];
   udp::endpoint sender_endpoint;
   size_t reply_length = s.receive_from(boost::asio::buffer(reply, ECServerAPI::Constants::MaxPackageLen), sender_endpoint);

   std::string response(reply, reply_length);
   std::cout << "Server response to ping is: " << response << std::endl;
}

void Client::handleCapabilityRequest() {
   std::cout << " *** Sending Capability Message to Server *** " << std::endl;
   
   // Remove all code below in this method from code given to students.
   
   nlohmann::json message;
   message["msgtype"] = ECServerAPI::Requests::Capability;
   message["version"] = clientVersion;
   
   printJsonMsg(message);
   
   s.send_to(boost::asio::buffer(message.dump()), endpoint);
   
   char reply[ECServerAPI::Constants::MaxPackageLen];
   udp::endpoint sender_endpoint;
   size_t reply_length = s.receive_from(boost::asio::buffer(reply, ECServerAPI::Constants::MaxPackageLen), sender_endpoint);
   
   std::string response(reply, reply_length);
   std::stringstream stream(response);
   nlohmann::json value;
   stream >> value;
   printJsonMsg(value);
   if (value.is_object()) {
      int msgType = value["msgtype"].get<int>();
      if (msgType == ECServerAPI::Response::Capabilities) {
         supportedMethods.clear();
         nlohmann::json array;
         supportedMethods = value["methods"].get<std::vector<std::string>>();
         printSupportedMethods();
      } else {
         throw new std::invalid_argument("wrong response to msgtype 1 from server");
      }
   }
}

void Client::handleEncryptionRequest() {
   std::cout << " *** Sending Message to Encrypt to Server *** " << std::endl;
   
   // Remove all code below in this method from code given to students.

   std::string text;
   std::string method;
   std::cout << "Give the text to encrypt: ";
   std::getline(std::cin, text);
   
   method = askMethodOfEncryption();
   
   int requestId = createRequestId();
   
   nlohmann::json message;
   message["msgtype"] = ECServerAPI::Requests::Encrypt;
   message["text"] = text;
   message["method"] = method;
   message["requestid"] = requestId;

   printJsonMsg(message);
   
   s.send_to(boost::asio::buffer(message.dump()), endpoint);
   
   char reply[ECServerAPI::Constants::MaxPackageLen];
   udp::endpoint sender_endpoint;
   size_t reply_length = s.receive_from(boost::asio::buffer(reply, ECServerAPI::Constants::MaxPackageLen), sender_endpoint);
   
   std::string response(reply, reply_length);
   std::stringstream stream(response);
   nlohmann::json value;
   stream >> value;
   printJsonMsg(value);
   if (value.is_object()) {
      int msgType = value["msgtype"].get<int>();
      if (msgType == ECServerAPI::Response::Encrypted) {
         std::cout << "Encrypted text is: ";
         std::cout << value["text"].get<std::string>() << std::endl;
      } else if (msgType == ECServerAPI::Response::Error) {
         std::cout << "ERROR from server: ";
         std::cout << value["text"].get<std::string>() << std::endl;
      } else {
         std::cout << "UNEXPECTED happened, don't know what to do... :/" << std::endl;
      }
   }
}

void Client::handleDecryptionRequest() {
   std::cout << " *** Sending Message to Decrypt to Server *** " << std::endl;

   // Remove all code below in this method from code given to students.

   std::string text;
   std::string method;
   std::cout << "Give the text to decrypt: ";
   std::getline(std::cin, text);
   
   method = askMethodOfEncryption();
   
   int requestId = createRequestId();

   nlohmann::json message;
   message["msgtype"] = ECServerAPI::Requests::Decrypt;
   message["text"] = text;
   message["method"] = method;
   message["requestid"] = requestId;
   
   printJsonMsg(message);
   
   s.send_to(boost::asio::buffer(message.dump()), endpoint);
   
   char reply[ECServerAPI::Constants::MaxPackageLen];
   udp::endpoint sender_endpoint;
   size_t reply_length = s.receive_from(boost::asio::buffer(reply, ECServerAPI::Constants::MaxPackageLen), sender_endpoint);
   
   std::string response(reply, reply_length);
   std::stringstream stream(response);
   nlohmann::json value;
   stream >> value;
   printJsonMsg(value);
   if (value.is_object()) {
      int msgType = value["msgtype"].get<int>();
      if (msgType == ECServerAPI::Response::Decrypted) {
         std::cout << "Decrypted text is: ";
         std::cout << value["text"].get<std::string>() << std::endl;
      } else if (msgType == ECServerAPI::Response::Error) {
         std::cout << "ERROR from server: ";
         std::cout << value["text"].get<std::string>() << std::endl;
      } else {
         std::cout << "UNEXPECTED happened, don't know what to do... :/" << std::endl;
      }
   }
}

void Client::sendTestRequests() {
   // TODO: Implement json test requests (correct and incorrect ones) and send them to the server.
   // Check that responses are as expected. Print out the results of the tests.
}

// Remove all methods below from code given to students.
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

void Client::printJsonMsg(const nlohmann::json & json) const {
   if (printDetails) {
      std::cout << json.dump() << std::endl;
   }
}

std::string Client::askMethodOfEncryption() const {
   std::string method;
   bool methodOK = true;
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
