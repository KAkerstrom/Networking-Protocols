#include <fstream>
#include "PacketManager.h"

std::vector<Packet> PacketManager::getPacketsFromFile(std::string filename) {
  std::string line;
  std::ifstream myfile (filename);
  std::vector<Packet> packets;
  if (myfile.is_open()) {
    while ( getline (myfile, line) ) {
      Packet p(line);
      packets.push_back(p);
    }
    myfile.close();
  }
  else
    throw new file_io_error("Unable to open file.");

  return packets;
}
