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

Frame Frame::createACK(char sequence) {
  Frame f;
  f.setFrameType(ACK);
  f.setSeq(sequence);
  return f;
}

Frame Frame::createNAK(char sequence) {
  Frame f;
  f.setFrameType(NAK);
  f.setSeq(sequence);
  return f;
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

  f.setSeq(serial[0] - '0');
  f.setFrameType((Frame::FrameType)(serial[1] - '0'));
  f.setEvenParity(serial[2] - '0');
  f.setData(serial.substr(3));
  return f;
}

std::string Frame::serialize() {
  std::string chars;
  chars += getSeq() + '0';
  chars += (((char)getFrameType()) + '0');
  chars += getEvenParity() + '0';
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
