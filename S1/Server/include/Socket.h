#ifndef SOCKET_H
#define SOCKET_H

#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

class Socket
{
    public:
        Socket();
       virtual ~Socket();

       // Server initialization
       bool create();
       bool bind (const int port);
       bool listen() const;
       bool accept (Socket&) const;

       // Client initialization
       bool connect (const std::string host, const int port);

       // Data Transimission
       bool send (const std::string) const;
       int recv (std::string&) const;

       bool is_valid() const {
          return m_sock != -1; }

    private:
        int m_sock;
        sockaddr_in m_addr;
};

#endif // SOCKET_H