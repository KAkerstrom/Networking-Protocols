#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "Exceptions.h"
#include "Packet.h"
#include "PacketBuilder.h"
#include "Frame.h"

int main() {
  try {
    // Get packets from file & "send"
    std::string file = "C:\\dev\\Networking-Protocols\\docs\\shunned_house.txt"; //replace with whatever
    std::vector<Packet> sendPackets =
      Packet::PacketBuilder::getPacketsFromFile(file);

    std::vector<Frame> frames;
    for (int i = 0; i < sendPackets.size(); i++)
      for (int j = 0; j < sendPackets[i].getFrames().size(); j++)
        frames.push_back(sendPackets[i].getFrames()[j]);

    //"Receive" the frames & output packets
    Packet::PacketBuilder p;
    std::vector<Packet> receivedPackets;
    for (int i = 0; i < frames.size(); i++) {
      //std::cout << frames[i].getData() << "\n";
      p.addFrame(frames[i]);
      if (frames[i].containsNewLine()) {
        receivedPackets.push_back(p.build());
        p = Packet::PacketBuilder();
      }
    }

    for ( int i = 0; i < receivedPackets.size(); i++)
      std::cout << receivedPackets[i].getData();

  }
  catch (std::runtime_error) {
    std::cout << "There was a problem...\n";
  }
  return 0;
}
