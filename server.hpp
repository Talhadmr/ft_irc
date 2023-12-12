#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>


class Server
{
    public:
        int _sock;
        struct sockaddr_in _sin;
        int _bin;
        int _lis;
        Server(char *str);
        void serving();
};

#endif