#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <string>
#include <vector>
#include "Packet.h"

class PacketManager {
 public:
  PacketManager();
  virtual ~PacketManager();

  std::vector<Packet> getPacketsFromFile(std::string filename);

 private:
};

#endif // PACKETMANAGER_H
