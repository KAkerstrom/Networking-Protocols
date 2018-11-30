#include <sstream>
#include <iostream>
#include "Frame.h"

int main() {
  char* source = new char[4]{0, 0, 0, 0};
  char* dest = new char[4]{0, 0, 0, 0};
  std::string data = "This is a test lmfao!";
  Frame f1(data, Frame::DATA, '0', source, dest, true);
  std::string test = f1.serialize();
  Frame f2 = Frame::deserialize(test);
  std::cout << f2.getData();
}
