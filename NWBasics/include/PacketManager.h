#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <string>
#include <vector>
#include "Packet.h"

class PacketManager {
 public:
  static std::vector<Packet> getPacketsFromFile(std::string filename);
};

#endif // PACKETMANAGER_H
