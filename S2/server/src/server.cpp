#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <pthread.h>
#include "Exceptions.h"
#include "Frame.h"
#include "PacketBuilder.h"
#include "ServerSocket.h"
#include "SocketException.h"

void* serve(void* sock) {
  ServerSocket new_sock = *((ServerSocket*)sock);

  try {
    try {
      Frame initialFrame;
      bool exists = false;
      do {
        std::string data;
        new_sock >> data;
        std::cout << data << "\n";

        if(data != "")
          initialFrame = Frame::deserialize(data);

        std::ifstream inFile;
        std::string fileName = "docs/" + initialFrame.getData();
        std::cout << fileName << "\n";

        inFile.open(fileName.c_str());
        exists = true;
        if (!inFile) {
          exists = false;
        }

        inFile.close();

        if(!exists) {
          std::string data;
          Frame clientResponse;
          Frame f("File Not Found.\n");
          new_sock << (f.serialize());


          do {
            new_sock >> data;
            clientResponse = Frame::deserialize(data);
          } while (clientResponse.getFrameType() == Frame::NAK);

          Frame lastFrame("/ENDOFFILE");
          new_sock << (lastFrame.serialize());
        }

      } while (!exists);

      std::string filepath = "docs/" + initialFrame.getData();

      std::vector<Packet> packets = Packet::PacketBuilder::getPacketsFromFile(filepath);

      for (int p = 0; p < packets.size(); p++) {
        std::vector<Frame> frames = packets[p].getFrames();
        Frame response;

        for (int f = 0; f < packets[p].getFrames().size(); f++)
          do {
            Frame toSend = frames[f];
            //Mess up the parity maybe
            if(rand() % 5 == 0) {
              toSend.setEvenParity(!toSend.getEvenParity());
              std::cout << "!!!Flipping_parity!!!\n";
            }

            std::string tmp = toSend.serialize();
            std::cout << "Sending " << tmp << "\n";
            new_sock << tmp;
            std::string data;
            new_sock >> data;
            response = Frame::deserialize(data);
          } while (response.getFrameType() == Frame::NAK);
      }
      Frame lastFrame("/ENDOFFILE");
      new_sock << (lastFrame.serialize());
    } catch (file_io_error) {
      std::cout << "Could not read file.\nExiting.\n";
      return 0;
    }
  } catch(SocketException& e) {
    std::cout << "Exception was caught:" << e.description() << "\n";
  }
}

int main() {
  srand(1);
  std::cout << "running....\n";
  try {
    // Create the socket
    ServerSocket server(3536);
    std::vector<pthread_t> threads;
    while (true) {
      ServerSocket new_sock;
      server.accept(new_sock);

      pthread_t newThread;
      int returnVal;
      returnVal = pthread_create(&newThread, NULL, serve, (void*)&new_sock);
      if (returnVal)
        std::cout << "Error creating new thread. Return code: " << returnVal << ".\n";
      else
        threads.push_back(newThread);

      for (int i = 0; i < threads.size(); i++)
        pthread_join(threads[i], NULL);
    }
  } catch (SocketException& e) {
    std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }
  return 0;
}
