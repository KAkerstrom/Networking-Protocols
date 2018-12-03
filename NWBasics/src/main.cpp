#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "Exceptions.h"
#include "Packet.h"
#include "PacketBuilder.h"
#include "Frame.h"

std::vector<std::string> emulateSend(std::string filename) {
  std::vector<std::string> output;

  std::vector<Packet> sendPackets =
    Packet::PacketBuilder::getPacketsFromFile(filename);

  std::vector<Frame> frames;
  for (int i = 0; i < sendPackets.size(); i++)
    for (int j = 0; j < sendPackets[i].getFrames().size(); j++)
      output.push_back(sendPackets[i].getFrames()[j].serialize());

  return output;
}

std::vector<Packet> emulateReceive(std::vector<std::string> input) {
  Packet::PacketBuilder p;
  std::vector<Packet> receivedPackets;
  for (int i = 0; i < input.size(); i++) {
    Frame f = Frame::deserialize(input[i]);
    p.addFrame(f);
    if (f.containsNewLine()) {
      receivedPackets.push_back(p.build());
      p = Packet::PacketBuilder();
    }
  }

  return receivedPackets;
}

int main() {
  //try {
    std::vector<std::string> sent =
      emulateSend("shunned_house.txt");
    sent.push_back(Frame::createACK(1).serialize());

    std::vector<Packet> received = emulateReceive(sent);

    for (int i = 0; i < received.size(); i++)
      std::cout << received[i].getData();

//  }
//  catch (std::runtime_error& e) {
//    std::cout << "There was a problem...\n";
//  }
  return 0;
}
