#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <vector>
#include "Exceptions.h"
#include "Frame.h"
#include "PacketBuilder.h"
#include <stdlib.h>

int main()
{
    const std::string FILE = "lorem.txt";
    std::cout << "running....\n";
    try
    {
        // Create the socket
        ServerSocket server(3530);

        while (true)
        {
            ServerSocket new_sock;
            server.accept(new_sock);

            try
            {
                try
                {
                    std::string data;
                    new_sock >> data;
                    std::cout << data << "\n";
                    std::vector<Packet> packets = Packet::PacketBuilder::getPacketsFromFile("docs/" + FILE);

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

