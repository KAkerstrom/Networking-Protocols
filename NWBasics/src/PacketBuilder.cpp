#include <fstream>
#include <iostream>
#include <vector>
#include "PacketBuilder.h"
#include "Exceptions.h"
#include "Frame.h"

void Packet::PacketBuilder::setFrames(std::vector<Frame> allFrames) {
  frames = allFrames;
}

void Packet::PacketBuilder::addFrame(Frame f) {
  frames.push_back(f);
}

Packet Packet::PacketBuilder::build() {
  Packet p (frames);
  return p;
}

std::vector<Packet> Packet::PacketBuilder::getPacketsFromFile(std::string filename) {
  std::string line;
  std::ifstream myfile (filename.c_str());
  std::vector<Packet> packets;
  if (myfile.is_open()) {
    while (getline (myfile, line)) {
        line += "\n";
      Packet::PacketBuilder builder;
      std::vector<Frame> lineFrames = Packet::PacketBuilder::dataToFrames(line);
      char test = line[line.size() - 1];
      for (int i = 0; i < lineFrames.size(); i++)
        builder.addFrame(lineFrames[i]);
      packets.push_back(builder.build());
    }
    myfile.close();
  }
  else
    throw file_io_error("Unable to open file.");

  return packets;
}

std::vector<Frame> Packet::PacketBuilder::dataToFrames(std::string data) {
  int index = 0;
  std::vector<Frame> output;

  for (int i = 0; i < data.length() % 64 + 1; i++) {
    if (data.length() >= (i * 64) + 64) {
      std::string s = data.substr(i * 64, 64);
      Frame f (s);
      output.push_back(f);
    } else {
      Frame f (data.substr(i * 64, data.length() - (i * 64)));
      output.push_back(f);
      break;
    }
  }

  return output;
}



