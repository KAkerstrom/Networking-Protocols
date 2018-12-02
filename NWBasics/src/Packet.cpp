#include "Packet.h"

#include <vector>
#include <string>
#include "Frame.h"

Packet::Packet(std::vector<Frame> packetFrames)
  : frames{packetFrames} {}

std::string Packet::getData() {
  std::string output;
  for (int i = 0; i < frames.size(); i++)
    output += frames[i].getData();
  return output;
}

std::vector<Frame> Packet::getFrames() {
  return frames;
}
