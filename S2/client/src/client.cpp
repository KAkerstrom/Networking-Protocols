#include <stdlib.h>
#include <iostream>
#include <string>
#include "ClientSocket.h"
#include "SocketException.h"
#include "Frame.h"
#include "Packet.h"

int main()
{
    std::string input;
    std::string output;
    std::string serverName = "localhost";
    int port = 3536;
    while(true)
    {
        // TODO: Input validation or just remove inputs all together.
        std::cout << "Please enter the hostname or IP of your server. \n";
        std::cin >> serverName;

        std::cout << "Server = " << serverName << ":" << port << "\n";

        while(true)
        {
            try
            {
                std::cout << "Enter filename: ";
                std::cin >> input;
                std::string reply;

                ClientSocket client_socket(serverName, port);

                Frame f(input);
                client_socket << (f.serialize());

                do
                {
                    client_socket >> reply;
                    Frame f = Frame::deserialize(reply);
                    reply = f.getData();

                    if(f.parityIsValid())
                    {
                        Frame ack = Frame::createACK(0);
                        client_socket << (ack.serialize());

                        if(reply != "/ENDOFFILE")
                            std::cout << reply;
                    }
                    else
                    {
                        //std::cout << "\nIncorrect_parity\n";
                        Frame nak = Frame::createNAK(0);
                        client_socket << (nak.serialize());
                    }


                }
                while(reply != "/ENDOFFILE");
                //std::cout << "\nOutside do loop\n";

            }
            catch(SocketException& e)
            {
                std::cout << "Exception was caught: " << e.description() << "\n";
                break;
            }
        }
    }
    return 0;
}
