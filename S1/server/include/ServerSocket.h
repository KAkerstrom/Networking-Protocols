#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include "Socket.h"

class ServerSocket : private Socket
{
    public:
      ServerSocket(int port);
      ServerSocket(){};
      virtual ~ServerSocket();

      const ServerSocket& operator << (const std::string&) const;
      const ServerSocket& operator >> (std::string&) const;

      void accept(ServerSocket&);

    private:
};

#endif // SERVERSOCKET_H
