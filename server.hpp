#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>


class Server
{
    public:
        int _socket;
        struct sockaddr_in _sin;
        int _bin;
        int _lis;
        int _port;
        Server(char *str);
        void serving();
};

class ClientInfo 
{
    public:
        int socket_fd;
        sockaddr_in address;

        // İhtiyaç duyulan diğer bilgileri ekleyebilirsiniz.

    ClientInfo(int fd, sockaddr_in addr);
};


#endif