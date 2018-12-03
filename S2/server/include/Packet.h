#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <vector>
#include "Frame.h"

class Packet {
 public:
  class PacketBuilder;

  /**
  * Destructor.
  */
  virtual ~Packet() {}

  /**
  * Gets the packet data.
  * @return Returns the packet data.
  */
  std::string getData();

  /**
  * Gets the frames for the packet.
  * @return Returns the packet split up into Frames.
  */
  std::vector<Frame> getFrames();

 private:
  /**
  * Constructor.
  * @param data: The packet data.
  */
  Packet(std::vector<Frame> packetFrames);

  /**
  * The frames holding the packet data.
  */
  std::vector<Frame> frames;
};

#endif // PACKET_H
