#include <sstream>
#include <iostream>
#include "Frame.h"

int main() {
  std::string data = "This is a test lmfao!";
  Frame f1(data, Frame::DATA, '8', 12345, 12345, true);
  std::string test = f1.serialize();
  Frame f2 = Frame::deserialize(test);
  std::cout << f2.getData();
}
