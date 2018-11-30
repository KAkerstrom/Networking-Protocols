#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include "Packet.h"

class Packet::PacketBuilder
{
public:
  PacketBuilder();
  virtual ~PacketBuilder();

  /**
  * Sets the Frames for the packet.
  */
  void setFrames(std::vector<Frame> frames);

  /**
  * Adds a Frame to the Packet.
  * @param f: The frame to add.
  */
  void addFrame(Frame f);

protected:
  /**
  * The frames holding the packet data.
  */
  std::vector<Frame> frames;

};

#endif // PACKETBUILDER_H
