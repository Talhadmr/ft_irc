
#include "Client.hpp"

void    ClientInfo::set_password(std::string pass)
{
    password = pass;
}

void    ClientInfo::set_username(std::string user)
{
    username = user;
}

void    ClientInfo::set_nickname(std::string nick)
{
    nickname = nick;
}

void    ClientInfo::set_realname(std::string real)
{
    realname = real;
}

std::string  ClientInfo::get_password()
{
    return password;
}

std::string  ClientInfo::get_username()
{
    return username;
}

std::string  ClientInfo::get_nickname()
{
    return nickname;
}

std::string  ClientInfo::get_realname()
{
    return realname;
}

std::string ClientInfo::getPrefix()
{
    return ":" + this->get_nickname() + "!" + this->get_username() + "@" + this->hostname + ":";
}

int    ClientInfo::get_joined(ClientInfo *ite)
{
    for (std::vector<Channel>::iterator it = isjoined.begin(); it != isjoined.end(); it++)
    {
        if (it->ChannelName == ite->get_nickname())
            return 1;
    }
    return 0;
}
