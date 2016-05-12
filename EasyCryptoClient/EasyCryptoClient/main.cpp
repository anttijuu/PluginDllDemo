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

#include <boost/asio.hpp>
/*
// query to server about capabilities
{
   "msgtype" : 1,
   "version" : 1.0.0
}
// server response for query message 1
{
   "msgtype" : 2,
   "version" : 1.0.1,
   "methods  : [reverse,matrix]
}
// request to encrypt data
{
   "msgtype" : 3,
   "text"    : "Text to encrypt",
   "method"  : "matrix",
   "requestid" : 12422231241
}
// response to encrypt data msg
{
   "msgtype" : 4,
   "text"    : "dfawie afwea adf",
   "requestid" : 12422231241
}
// request to decrypt data
{
   "msgtype" : 5,
   "text"    : "dfawie afwea adf",
   "method"  : "matrix",
   "requestid" : 12422231241
}
// response to decrypt data msg
{
   "msgtype" : 6,
   "text"    : "Text to encrypt",
   "requestid" : 12422231241
}
*/

using boost::asio::ip::udp;

class Client {
public:
   Client();
   int mainFunc(int argc, char * argv[]);

private:
   
   void handleCapabilityRequest();
   void handleEncryptionRequest();
   void handleDecryptionRequest();
   
private:
   boost::asio::io_service io_service;
   
   udp::socket s;
   
   udp::resolver resolver;
   udp::endpoint endpoint;
   
   std::chrono::system_clock::time_point started;
   
};

enum { max_length = 4096 };
static const std::string clientVersion("1.0.0");
static const std::string queryMsg("{\"msgtype\" : 1, \"version\" : \"%s\"}");
static const std::string encryptMsg("{\"msgtype\" : 3, \"text\" : \"%s\", \"method\" : \"%s\", \"requestid\" : %d}");
static const std::string decryptMsg("{\"msgtype\" : 5,\"text\"  : \"%s\", \"method\" : \"%s\",\"requestid\" : %d }");
static const std::string parameterStr("%s");
static const std::string parameterInt("%d");

int main (int argc, char* argv[]) {
   Client client;
   
   return client.mainFunc(argc, argv);
}

Client::Client()
: s(io_service, udp::endpoint(udp::v4(), 0)), resolver(io_service) {
   started = std::chrono::system_clock::now();
}

int Client::mainFunc(int argc, char* argv[])
{
   try
   {
      if (argc != 3)
      {
         std::cerr << "Usage: EasyCryptoClient <host> <port>\n";
         return 1;
      }
      
      endpoint = *resolver.resolve({udp::v4(), argv[1], argv[2]});
      
      int command = 0;
      char request[max_length];
      do {
         std::cout << "Menu of commands" << std::endl;
         std::cout << "1) Send capability request to server" << std::endl;
         std::cout << "2) Send encryption request to server" << std::endl;
         std::cout << "3) Send decryption request to server" << std::endl;
         std::cout << "0) Exit client" << std::endl;
         std::cout << "Menu of commands" << std::endl;
         std::cout << "Enter command: ";
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
            default: {
               break;
            }
         }
         
      } while (command > 0);
   }
   catch (std::exception& e)
   {
      std::cerr << "Exception: " << e.what() << "\n";
   }
   std::cout << "Bye!" << std::endl;
   return 0;
}

void Client::handleCapabilityRequest() {
   std::string msg;
   msg = queryMsg;
   msg.replace(msg.rfind(parameterStr),parameterStr.length(), clientVersion);
   std::cout << " *** Sending Capability Message to Server *** " << std::endl;
   std::cout << "Sending: " << msg << std::endl;
   s.send_to(boost::asio::buffer(msg), endpoint);
   
   char reply[max_length];
   udp::endpoint sender_endpoint;
   size_t reply_length = s.receive_from(boost::asio::buffer(reply, max_length), sender_endpoint);
   std::cout << "Reply is: ";
   std::cout.write(reply, reply_length);
   std::cout << std::endl;
}

void Client::handleEncryptionRequest() {
   /*
    {
    "msgtype" : 3,
    "text"    : "%s",
    "method"  : "%s",
    "requestid" : %d
    }
    */
   std::cout << " *** Sending Message to Encrypt to Server *** " << std::endl;
   std::string msg;
   std::string text;
   std::string method;
   msg = encryptMsg;
   std::cout << "Give the text to encrypt: ";
   std::getline(std::cin, text);
   std::cout << "Give the method of encryption: ";
   std::getline(std::cin, method);
   
   std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
   std::stringstream str;
   str << std::chrono::duration_cast<std::chrono::milliseconds>(now-started).count();

   msg.replace(msg.rfind(parameterInt),parameterStr.length(), str.str());
   msg.replace(msg.rfind(parameterStr),parameterStr.length(), method);
   msg.replace(msg.rfind(parameterStr),parameterStr.length(), text);
   std::cout << "Sending: " << msg << std::endl;
   s.send_to(boost::asio::buffer(msg), endpoint);
   
   char reply[max_length];
   udp::endpoint sender_endpoint;
   size_t reply_length = s.receive_from(boost::asio::buffer(reply, max_length), sender_endpoint);
   std::cout << "Encrypted text is: ";
   std::cout.write(reply, reply_length);
   std::cout << std::endl;
   
}

void Client::handleDecryptionRequest() {
/*
 // request to decrypt data
   {
      "msgtype" : 5,
      "text"    : "dfawie afwea adf"
      "method"  : "matrix",
      "requestid" : 12422231241
   }
*/
   std::cout << " *** Sending Message to Decrypt to Server *** " << std::endl;
   std::string msg;
   std::string text;
   std::string method;
   msg = decryptMsg;
   std::cout << "Give the text to decrypt: ";
   std::getline(std::cin, text);
   std::cout << "Give the method of decryption: ";
   std::getline(std::cin, method);
   
   std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
   std::stringstream str;
   str << std::chrono::duration_cast<std::chrono::milliseconds>(now-started).count();
   
   msg.replace(msg.rfind(parameterInt),parameterStr.length(), str.str());
   msg.replace(msg.rfind(parameterStr),parameterStr.length(), method);
   msg.replace(msg.rfind(parameterStr),parameterStr.length(), text);
   std::cout << "Sending: " << msg << std::endl;
   s.send_to(boost::asio::buffer(msg), endpoint);
   
   char reply[max_length];
   udp::endpoint sender_endpoint;
   size_t reply_length = s.receive_from(boost::asio::buffer(reply, max_length), sender_endpoint);
   std::cout << "Decrypted text is: ";
   std::cout.write(reply, reply_length);
   std::cout << std::endl;
   
}
