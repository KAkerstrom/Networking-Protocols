#ifndef FRAME_H
#define FRAME_H

#include <string>
#include <vector>

class Frame {
 public:
  enum FrameType {ACK, NAK, DATA};
  Frame();
  virtual ~Frame() {}
  std::vector<char> getBinary();

 private:
  char seq;
  FrameType frameType;
  bool evenParityBit;
  std::string data; //Max 64 Characters!
  void setEvenParityBit();
  std::vector<char> getDataBits();
};

#endif // FRAME_H
