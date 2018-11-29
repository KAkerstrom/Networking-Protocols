#include <bitset>
#include <math.h>
#include <iostream>
#include <vector>
#include "Frame.h"
#include "Exceptions.h"


Frame::Frame() {
  seq = -1;
  frameType = DATA;
  sourceAddr = new char[4] {0, 0, 0, 0};
  destAddr = new char[4] {0, 0, 0, 0};
  data = "";
  evenParityBit = false;
}

Frame::Frame(std::string frameData, FrameType ft, char sequence, char* source,
  char* dest) : frameType{ft}, seq{sequence}, sourceAddr{source},
  destAddr{dest} {
  setData(frameData);
  evenParityBit = calculateEvenParity();
}

Frame::Frame(std::string frameData, FrameType ft, char sequence, char* source,
  char* dest, bool evenParity) : frameType{ft}, seq{sequence},
  sourceAddr{source}, destAddr{dest}, evenParityBit{evenParity} {
  setData(frameData);
  evenParityBit = calculateEvenParity();
}

bool Frame::parityIsValid() {
 return evenParityBit == calculateEvenParity();
}

bool Frame::calculateEvenParity() {
  bool evenBits = false;
  for(char c : data)
    for(char i = 1; i < 8; i++)
      if (c & (char)pow(2, i))
        evenBits = !evenBits;

  return !evenBits;
}

void Frame::setData(std::string frameData) {
  if (data.length() > MAX_DATA)
    throw data_exceeds_max_length_error("Frame data exceeds max data amount.");
  data = data;
}
/**
* INCOMPLETE METHOD
*/
std::istream& operator>>(std::istream& is, Frame& f) {
  //    1 START_END_BYTE
  //   32 SOURCE_ADDRESS
  //   32 DEST_ADDRESS
  //    1 CONTROL (2 bits FRAME_TYPE, 4 bits SEQ_NUM)
  // <=64 DATA
  //    1 EVEN_PARITY
  //    1 START_END_BYTE

  char c;
  //    1 START_END_BYTE
  is >> c;
  if (c & Frame::START_END_BYTE != Frame::START_END_BYTE)
    throw deserialization_error("Starting byte was not 0x7E as expected.");

  //   32 SOURCE_ADDRESS
  char* sourceAddr = new char[4];
  for (int i = 0; i < 4; i++)
    is >> sourceAddr[i];
  f.setSourceAddr(sourceAddr);

  //   32 DEST_ADDRESS
  char* destAddr = new char[4];
  for (int i = 0; i < 4; i++)
    is >> destAddr[i];
  f.setDestAddr(destAddr);

  //    1 CONTROL (2 bits FRAME_TYPE, 4 bits SEQ_NUM)
  is >> c;
  // 2 bits FRAME_TYPE
  f.setFrameType((Frame::FrameType)((c & 0xC0) >> 6));
  // 4 bits SEQ_NUM
  f.setSeq((c & 0x7E) >> 2);

  // Read until end of frame
  // <=64 DATA
  c = -1;
  std::vector<char> frameBytes;
  int maxBytes = Frame::MAX_DATA + 1;
  while(c != Frame::START_END_BYTE && maxBytes-- > 0) {
    is >> c;
    frameBytes.push_back(c);
  }

}

/**
* INSERT BIT STUFFING
*/
std::ostream& operator<<(std::ostream& os, Frame& f) {
  //    1 START_END_BYTE
  //   32 SOURCE_ADDRESS
  //   32 DEST_ADDRESS
  //    1 CONTROL (2 bits FRAME_TYPE, 4 bits SEQ_NUM)
  // <=64 DATA
  //    1 EVEN_PARITY
  //    1 START_END_BYTE
  ////////////////////////////////////////////////////////

  //    1 START_END_BYTE
  os << Frame::START_END_BYTE;

  //   32 SOURCE_ADDRESS
  for (int i = 0; i < 4; i++)
    os << f.getSourceAddr()[i];

  //   32 DEST_ADDRESS
  for (int i = 0; i < 4; i++)
    os << f.getDestAddr()[i];

  //    1 CONTROL (2 bits FRAME_TYPE, 4 bits SEQ_NUM)
  char control = (char)f.getFrameType() << 6;
  control |= f.getSeq() << 2;

  // <=64 DATA
  os << f.getData();

  //    1 EVEN_PARITY
  os << f.getEvenParity();

  //    1 START_END_BYTE
  os << Frame::START_END_BYTE;
}





