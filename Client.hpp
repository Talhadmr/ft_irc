
#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <sys/socket.h>
#include <iostream>
#include "server.hpp"

using std::string;
using std::cout;
using std::endl;


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
        std::vector <std::string> commands; 

        void set_password(string pass);
        void set_username(string user);
        void set_nickname(string nick);
        void set_realname(string real);

        string getPrefix();

        // İhtiyaç duyulan diğer bilgileri ekleyebilirsiniz.

    ClientInfo(int fd, sockaddr_in addr);
};

#endif
