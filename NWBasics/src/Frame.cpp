#include <bitset>
#include <math.h>
#include <iostream>
#include <vector>
#include "Frame.h"
#include "Exceptions.h"


Frame::Frame() {
  seq = -1;
  frameType = DATA;
  data = "";
  evenParityBit = false;
}

Frame::Frame(std::string frameData) {
  setData(frameData);
  frameType = DATA;
  seq = 0;
  evenParityBit = calculateEvenParity();
}

Frame::Frame(std::string frameData, FrameType ft, char sequence, bool evenParity)
  : frameType{ft}, seq{sequence}, evenParityBit{evenParity} {
  setData(frameData);
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
  Frame f;
  if (serial.length() < 3)
    throw deserialization_error("Serial string too short (<3 characters)");

  f.setSeq(serial[0]);
  f.setFrameType((Frame::FrameType)serial[1]);
  f.setEvenParity(serial[2]);
  f.setData(serial.substr(3));
  return f;
}

std::string Frame::serialize() {
  std::string chars;
  chars.push_back(getSeq());
  chars.push_back((char)getFrameType());
  chars.push_back(getEvenParity());
  chars += getData();
  return chars;
}

std::ostream& operator<<(std::ostream& os, Frame& frame) {
  os << frame.serialize();
}

std::istream& operator>>(std::istream& is, Frame& frame) {
  std::string s;
  is >> s;
  frame = Frame::deserialize(s);
}
