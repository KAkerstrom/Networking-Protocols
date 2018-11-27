// Implementation of the ServerSocket class

#include "ServerSocket.h"
#include "SocketException.h"

ServerSocket::ServerSocket(int port) {
  if (!Socket::create())
    throw SocketException("Error creating server socket!");

  if (!Socket::bind(port))
    throw SocketException("Error binding to port!");

  if (!Socket::listen())
    throw SocketException("Error listening to socket!");
}

const ServerSocket& ServerSocket::operator << (const std::string& s) const {
  if (!Socket::send(s))
    throw SocketException("Error writing to socket.");
  return *this;

}

const ServerSocket& ServerSocket::operator >> (std::string& s) const {
  if (!Socket::recv(s))
    throw SocketException("Could not read from socket.");
  return *this;
}

void ServerSocket::accept(ServerSocket& sock) {
  if (!Socket::accept(sock))
    throw SocketException("Could not accept socket.");
}