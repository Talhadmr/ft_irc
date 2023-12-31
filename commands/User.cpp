
#include "../command.hpp"
#include "../RPL.hpp"

void    USER(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
    std::string message;
    if (server.registered == true)
    {
        message = ERR_ALREADYREGISTRED();
        send(ite.socket_fd,message.c_str(), message.size(), 0);
        return;
    }  
    std::vector<ClientInfo>::iterator it = clients.begin();
    if (ite.commands.size() < 5)
    {
        message = ERR_NEEDMOREPARAMS("USER");
        send(ite.socket_fd,message.c_str(), message.size(), 0);
        return ;
    }
    std::vector<std::string> param = user_helper(ite);
    if (param.size() != 5 && param[2][0] != '0' && param[3][0] != '*')
    {
        message = ":" + ite.get_nickname() + "!" + ite.get_username() + "@" + server.hostname + ":" + " " + "Error: Wrong parameters" + "\r\n";
        send(ite.socket_fd, message.c_str(), message.size(), 0);
        return ;
    }
    ite.set_username(param[1]);
    ite.set_realname(param[4]);
    server.registered = true;
    param.clear();
}

std::vector<std::string>    user_helper(ClientInfo &ite)
{
    std::vector<std::string> param;
    std::string buffer;
    for (int i = 0; i < ite.commands.size(); i++)
    {
        if (ite.commands[i][0] == ':' && i == 4)
        {
            buffer += (&ite.commands[i][1]);
            while (++i < ite.commands.size())
            {
                buffer += " ";
                buffer += ite.commands[i];
            }
            param.push_back(buffer);
            return (param);
        }
        else
            param.push_back(ite.commands[i]);
    }
    return (param);
}
