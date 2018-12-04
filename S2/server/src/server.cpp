#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <vector>
#include <fstream>
#include "Exceptions.h"
#include "Frame.h"
#include "PacketBuilder.h"
#include <stdlib.h>

int main()
{
    srand(1);
    std::cout << "running....\n";
    try
    {
        // Create the socket
        ServerSocket server(3536);

        while (true)
        {
            ServerSocket new_sock;
            server.accept(new_sock);

            // For multiple threading, you need to create
            // a new thread here and pass new_sock to it.
            // The thread will use new_sock to communicate
            // with the client.
            try
            {
                //while (true)
                //{
                try
                {

                    Frame initialFrame;
                    bool exists = false;
                    do
                    {
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
                        if (!inFile)
                        {
                            exists = false;
                        }

                        inFile.close();

                        if(!exists)
                        {
                            std::string data;
                            Frame clientResponse;
                            Frame f("Not-Proper-Text-File\n");
                            new_sock << (f.serialize());


                            do
                            {
                                new_sock >> data;
                                clientResponse = Frame::deserialize(data);
                            }
                            while (clientResponse.getFrameType() == Frame::NAK);

                            Frame lastFrame("/ENDOFFILE");
                            new_sock << (lastFrame.serialize());
                        }

                    }
                    while (!exists);
                    std::cout << "\nOutside do loop\n";

                    std::string filepath = "docs/" + initialFrame.getData();

                    std::vector<Packet> packets = Packet::PacketBuilder::getPacketsFromFile(filepath);

                    for (int p = 0; p < packets.size(); p++)
                    {
                        std::vector<Frame> frames = packets[p].getFrames();
                        Frame response;

                        for (int f = 0; f < packets[p].getFrames().size(); f++)
                            do
                            {
                                Frame toSend = frames[f];
                                //Mess up the parity maybe
                                if(rand() % 5 == 0)
                                {
                                    toSend.setEvenParity(!toSend.getEvenParity());
                                    std::cout << "!!!Flipping_parity!!!\n";
                                }

                                std::string tmp = toSend.serialize();
                                std::cout << "Sending " << tmp << "\n";
                                new_sock << tmp;
                                std::string data;
                                new_sock >> data;
                                response = Frame::deserialize(data);
                            }
                            while (response.getFrameType() == Frame::NAK);
                    }
                    Frame lastFrame("/ENDOFFILE");
                    new_sock << (lastFrame.serialize());
                }
                catch (file_io_error)
                {
                    std::cout << "Could not read file.\nExiting.\n";
                    return 0;
                }

                //}
            }
            catch(SocketException& e)
            {
                std::cout << "Exception was caught:" << e.description() << "\n";
            }

        }
    }
    catch (SocketException& e)
    {
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
