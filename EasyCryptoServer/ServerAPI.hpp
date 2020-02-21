#pragma once

/**
 This is part of the API to the EasyCrypto Server. Clients should use these API constants in communicating with the server.
 
 Deliver this API file to client programmers. Make sure updates to this file do not break clients build
 with older version of the API definitions file. That means, do not:
  - remove any enumerations
  - change any values of the enumerations
  - do not make the max package length smaller
  - if you grow the package length, and send larger amounts of data than client can handle, it will crash the client or the data cannot be handled by the client.
 
  @todo Add string constants to be used in the JSON messages.
  @todo Create a class that builds JSON messages both for client and server.
 */
namespace ECServerAPI {

enum Constants {
   MaxPackageLen = 4096,    /*!< Maximum length of data in bytes to pass between client and server. */
   ServerAPIVersion = 0x01  /*!< The version number of the server API. */
};

enum Requests {
   Capability = 1,    /*!< Send this to server to request list of encryption methods server supports. */
   Encrypt = 2,       /*!< Send this to server to request encryption of text passed with the message. */
   Decrypt = 3        /*!< Send this to server to request decryption of text passed with the message. */
};

enum Response {
   Capabilities = 1,  /*!< Server response code to requested encryption methods server supports. Also encryption lib version number is returned with the list of methods supported. */
   Encrypted = 2,     /*!< Server response code to request to encrypt data. */
   Decrypted = 3,     /*!< Server response code to request to decrypt data. */
   Error = 999        /*!< Server error code to any request that was failed. */
};

} // namespace
