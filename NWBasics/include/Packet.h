#ifndef PACKET_H
#define PACKET_H

#include <string>

class Packet
{
 public:
  Packet();
  virtual ~Packet() {}

 private:
  std::string data;
};

#endif // PACKET_H
