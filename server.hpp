#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>
#include <unistd.h>
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

class ClientInfo
{
    private:
        string password;
        string username;
        string nickname;
        string realname;

    public:
        int socket_fd;
        sockaddr_in address;
        string get_password();
        string get_username();
        string get_nickname();
        string get_realname();

        void set_password(string pass);
        void set_username(string user);
        void set_nickname(string nick);
        void set_realname(string real);

        // İhtiyaç duyulan diğer bilgileri ekleyebilirsiniz.

    ClientInfo(int fd, sockaddr_in addr);
};
void	command_info(string buffer, std::vector<ClientInfo> clients,  ClientInfo ite);
void	command_message(string buffer, std::vector<ClientInfo> clients);


#endif
