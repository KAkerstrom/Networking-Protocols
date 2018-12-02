#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include "Packet.h"

class Packet::PacketBuilder
{
public:
  PacketBuilder() {}
  virtual ~PacketBuilder() {}

  /**
  * Sets the Frames for the packet.
  * @param allFrames: The frames to set for this Packet, in order.
  */
  void setFrames(std::vector<Frame> allFrames);

  /**
  * Adds a Frame to the Packet.
  * @param f: The frame to add.
  */
  void addFrame(Frame f);

  /**
  * Gets the Packet.
  * @return Returns the packet.
  */
  Packet build();

  /**
  * Splits a file into packets.
  * @param filename: The filename.
  * @return Returns a vector of packets.
  */
  static std::vector<Packet> getPacketsFromFile(std::string filename);

protected:
  /**
  * Splits string data into frames.
  * @param data: The string data.
  * @return Returns the frames containing the data.
  */
  static std::vector<Frame> dataToFrames(std::string data);

  /**
  * The frames holding the packet data.
  */
  std::vector<Frame> frames;

};

#endif // PACKETBUILDER_H
