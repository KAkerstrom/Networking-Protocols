#include <iostream>
#include <string>
#include "ClientSocket.h"
#include "SocketException.h"
#include "Frame.h"
#include "Packet.h"

// Send "message" to hostName at port
//std::string sendMsg(std::string message, std::string hostName, int port)
//{
//    std::string reply;
//    try
//    {
//        ClientSocket client_socket(hostName, port);
//
//        Frame f(message);
//
//        client_socket << (f.serialize());
//        client_socket >> reply;
//
//        //reply = "We received this response from the server:\n\"" + reply + "\"\n";
//    }
//    catch(SocketException& e)
//    {
//        reply = "Exception was caught:" + e.description() + "\n";
//    }
//
//    return reply;
//}

int main()
{
    std::string input;
    std::string output;
    std::string serverName = "localhost";
    int port = 3530;

    // TODO: Input validation or just remove inputs all together.
    std::cout << "Please enter the hostname or IP of your server. \n";
    std::cin >> serverName;

    std::cout << "Server = " << serverName << ":" << port << "\n";

    while(true)
    {
        std::cin >> input;
        Frame f(input);
        std::string reply;
        try
        {
            ClientSocket client_socket(serverName, port);
            client_socket << (f.serialize());

            do
            {
                client_socket >> reply;
                reply = Frame::deserialize(reply).getData();

                std::cout << reply;
            }
            while(reply != "/ENDOFFILE");
        }
        catch(SocketException& e)
        {
            reply = "Exception was caught:" + e.description() + "\n";
        }


    }


    return 0;
}
