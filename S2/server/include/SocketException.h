#ifndef SOCKETEXCEPTION_H
#define SOCKETEXCEPTION_H

#include <string>

class SocketException
{
    public:
        SocketException ( std::string s ) : m_s ( s ) {};
        ~SocketException (){};

        std::string description() { return m_s; }

    private:
        std::string m_s;
};

#endif // SOCKETEXCEPTION_H
