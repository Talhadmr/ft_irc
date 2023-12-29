#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include "command.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include <arpa/inet.h>

using std::string;
using std::cout;
using std::endl;
class Channel;

class Server
{
    public:
        int _socket;
        std::string hostname;
        struct sockaddr_in _sin;
        int _bin;
        int _lis;
        int _port;
        int flag;
        std::string _pass;
        Server(char *str);
        std::vector <Channel> channels;
        string c_name();
        void serving();
};

void	command_info(string buffer, std::vector<ClientInfo> clients,  ClientInfo &ite);
void	command_message(string buffer,std::vector<ClientInfo> clients,ClientInfo &ite);
void	search_command(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels);


#endif
