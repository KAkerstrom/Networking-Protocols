#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <vector>
#include "Exceptions.h"
#include "Frame.h"
#include "PacketBuilder.h"

int main()
{
    std::cout << "running....\n";
    try
    {
        // Create the socket
        ServerSocket server(3530);

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
                        do
                        {
                            std::string data;
                            new_sock >> data;
                            std::cout << data << "\n";


                            if(data != "")
                             initialFrame = Frame::deserialize(data);

                            if(initialFrame.getData() != "shunned_house.txt")
                            {
                               Frame f("Not-Proper-Text-File");
                               new_sock << (f.serialize());
                               Frame lastFrame("/ENDOFFILE");
                               new_sock << (lastFrame.serialize());
                            }

                        }
                        while (initialFrame.getData() != "shunned_house.txt");
                        std::cout << "\nOutside do loop\n";

                        //std::string filepath = "../../docs/shunned_house.txt";
                        std::string filepath = "shunned_house.txt";
                        std::vector<Packet> packets = Packet::PacketBuilder::getPacketsFromFile(filepath);

                        for (int p = 0; p < packets.size(); p++)
                        {
                            std::vector<Frame> frames = packets[p].getFrames();
                            Frame response;

                            for (int f = 0; f < packets[p].getFrames().size(); f++)
                                do
                                {
                                  std::string tmp = frames[f].serialize();
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
            catch(SocketException& e) {
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
