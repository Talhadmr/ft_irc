
#include "../command.hpp"
#include "../RPL.hpp"

void    USER(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
    std::vector<ClientInfo>::iterator it = clients.begin();
    if (ite.commands.size() < 4)
    {
        ERR_NEEDMOREPARAMS("USER");
        return ;
    }
    if (ite.commands.size() != 5 && ite.commands[2][0] != '0' && ite.commands[3][0] != '*')
    {
        std::string message = ":" + ite.get_nickname() + "!" + ite.get_username() + "@" + server.hostname + ":" + " " + "Error: Wrong parameters" + "\r\n";
        send(ite.socket_fd, message.c_str(), message.size(), 0);
        cout << "Wrong parameters" << endl;
        return ;
    }
}
