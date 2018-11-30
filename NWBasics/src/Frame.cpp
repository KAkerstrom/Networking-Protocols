#include <bitset>
#include <math.h>
#include <iostream>
#include <vector>
#include "Frame.h"
#include "Exceptions.h"


Frame::Frame() {
  seq = -1;
  frameType = DATA;
  sourceAddr = 0;
  destAddr = 0;
  data = "";
  evenParityBit = false;
}

Frame::Frame(std::string frameData, FrameType ft, char sequence, int source,
  int dest) : frameType{ft}, seq{sequence}, sourceAddr{source},
  destAddr{dest} {
  setData(frameData);
  evenParityBit = calculateEvenParity();
}

Frame::Frame(std::string frameData, FrameType ft, char sequence, int source,
  int dest, bool evenParity) : frameType{ft}, seq{sequence},
  sourceAddr{source}, destAddr{dest}, evenParityBit{evenParity} {
  setData(frameData);
  evenParityBit = calculateEvenParity();
}

bool Frame::parityIsValid() {
 return evenParityBit == calculateEvenParity();
}

bool Frame::calculateEvenParity() {
  bool evenBits = false;
  for(int i = 0; i < data.length(); i++)
    for(char j = 1; j < 8; j++)
      if (data[i] & (char)pow(2, j))
        evenBits = !evenBits;

  return !evenBits;
}

void Frame::setData(std::string frameData) {
  if (data.length() > MAX_DATA)
    throw data_exceeds_max_length_error("Frame data exceeds max data amount.");
  data = frameData;
}


Frame Frame::deserialize(std::string serial) {
  //    1 START_END_BYTE
  //   32 SOURCE_ADDRESS
  //   32 DEST_ADDRESS
  //    1 CONTROL (2 bits FRAME_TYPE, 4 bits SEQ_NUM)
  // <=64 DATA
  //    1 EVEN_PARITY
  //    1 START_END_BYTE

  int charIndex = 0;
  Frame f;
  //    1 START_END_BYTE
  if (serial[charIndex++] != Frame::START_END_BYTE)
    throw deserialization_error("Starting byte was not 0x7E as expected.");

  //   32 SOURCE_ADDRESS
  int addr = 0;
  for (int i = 0; i < 4; i++) {
    addr = addr | serial[charIndex++];
    if (i < 3)
      addr = addr << 8;
  }
  f.setSourceAddr(addr);

  //   32 DEST_ADDRESS
  addr = 0;
  for (int i = 0; i < 4; i++) {
    addr = addr | serial[charIndex++];
    if (i < 3)
      addr = addr << 8;
  }
  f.setDestAddr(addr);

  //    1 CONTROL (2 bits FRAME_TYPE, 4 bits SEQ_NUM)
  char c = serial[charIndex++];
  // 2 bits FRAME_TYPE
  f.setFrameType((Frame::FrameType)((c & 0xC0) >> 6));
  // 4 bits SEQ_NUM
  f.setSeq(c & 0x7F);

  // Read until end of frame
  // <=64 DATA
  f.setData(serial.substr(charIndex, serial.length() - charIndex - 2));
  return f;
}

std::string Frame::serialize() {
  //    1 START_END_BYTE
  //   32 SOURCE_ADDRESS
  //   32 DEST_ADDRESS
  //    1 CONTROL (2 bits FRAME_TYPE, 4 bits SEQ_NUM)
  // <=64 DATA
  //    1 EVEN_PARITY
  //    1 START_END_BYTE
  ////////////////////////////////////////////////////////

  std::string chars;
  //    1 START_END_BYTE
  chars.push_back(Frame::START_END_BYTE);

  //   32 SOURCE_ADDRESS
  for (int i = 0; i < 4; i++)
    chars.push_back(getSourceAddr() >> (i * 8));

  //   32 DEST_ADDRESS
  for (int i = 0; i < 4; i++)
    chars.push_back(getDestAddr() >> (i * 8));

  //    1 CONTROL (2 bits FRAME_TYPE, 4 bits SEQ_NUM)
  char control = (char)getFrameType() << 6;
  control |= getSeq();
  chars.push_back(control);

  // <=64 DATA
  for (int i = 0; i < getData().length(); i++)
    chars.push_back(getData()[i]);

  //    1 EVEN_PARITY
  chars.push_back(getEvenParity());

  //    1 START_END_BYTE
  chars.push_back(Frame::START_END_BYTE);

  return chars;
}
