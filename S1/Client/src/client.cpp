#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

// Send "message" to hostName at port
std::string sendMsg(std::string message, std::string hostName, int port)
{
    std::string reply;
    try
    {
        ClientSocket client_socket(hostName, port);

//        try
//        {
        client_socket << message;
        client_socket >> reply;
//        }
//        catch(SocketException&)
//        {
//        }
        reply = "We received this response from the server:\n\"" + reply + "\"\n";
    }
    catch(SocketException& e)
    {
        reply = "Exception was caught:" + e.description() + "\n";
    }

    return reply;
}

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
        output = sendMsg(input, serverName, port);
        std::cout << output;
    }


    return 0;
}
