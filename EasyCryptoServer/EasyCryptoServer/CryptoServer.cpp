//
//  CryptoServer.cpp
//  EasyCryptoServer
//
//  Created by Antti Juustila on 10.5.2016.
//  Copyright © 2016 Antti Juustila. All rights reserved.
//

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
 "text"    : "Text to encrypt"
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
 "text"    : "dfawie afwea adf"
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
#include "CryptoServer.hpp"

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

void CryptoServer::doSendResponse(std::size_t length) {
   // parse the json request
   // do encryption/decryption
   // construct json reply
   // send back json reply
   std::string response(data_, length);
   std::cout << "Sending response : " << response << std::endl;
   socket_.async_send_to(boost::asio::buffer(data_, length), sender_endpoint_,
                         [this](boost::system::error_code /*ec*/, std::size_t /*bytes_sent*/)
                         {
                            doReceive();
                         });
}
