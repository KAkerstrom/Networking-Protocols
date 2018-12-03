#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <vector>
#include "Exceptions.h"

int main() {
  std::cout << "running....\n";
  try{
    // Create the socket
    ServerSocket server(3530);

    while (true) {
      ServerSocket new_sock;
      server.accept(new_sock);

      // For multiple threading, you need to create
      // a new thread here and pass new_sock to it.
      // The thread will use new_sock to communicate
      // with the client.
      try {
        while (true) {
          try {

            Frame initialFrame;
            do {
              new_sock >> initialFrame;
            }
            while (initialFrame.getData() != "shunned_house.txt");

            std::string filepath = "../../docs/shunned_house.txt";
            std::vector<Packet> packets = PacketBuilder::getPacketsFromFile(filepath);

            for (int p = 0; p < packets.size(); p++) {
              std::vector<Frame> frames = packets[p].getFrames();
              Frame response;

              for (int f = 0; f < packets[i].getFrames().size(); f++)
                do {
                  new_sock << frames[f];
                  new_sock >> response;
                }
                while (response.getFrameType() == Frame::NAK);
            }
          }
          catch (file_io_error) {
            std::cout << "Could not read file.\nExiting.\n";
            return 0;
          }

         std::string data;
         new_sock >> data;
         new_sock << data;
        }
      }
      catch(SocketException&) {}
    }
  }
  catch (SocketException& e) {
    std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }
  return 0;
}

/*int main() {
  std::cout << "running....\n";
  try{
    // Create the socket
    ServerSocket server(3530);

    while (true) {
      ServerSocket new_sock;
      server.accept(new_sock);

      // For multiple threading, you need to create
      // a new thread here and pass new_sock to it.
      // The thread will use new_sock to communicate
      // with the client.
      try {
        while (true) {
         std::string data;
         new_sock >> data;
         new_sock << data;
        }
      }
      catch(SocketException&) {}
    }
  }
  catch (SocketException& e) {
    std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }
  return 0;
}*/
