#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "command.hpp"
#include "Client.hpp"
#include <arpa/inet.h>

using std::string;
using std::cout;
using std::endl;

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

void	command_info(string buffer, std::vector<ClientInfo> clients,  ClientInfo &ite);
void	command_message(string buffer,std::vector<ClientInfo> clients,ClientInfo &ite);
void	search_command(std::vector<ClientInfo> clients, ClientInfo &ite);


#endif
