
#include "Client.hpp"

void    ClientInfo::set_password(string pass)
{
    password = pass;
}

void    ClientInfo::set_username(string user)
{
    username = user;
}

void    ClientInfo::set_nickname(string nick)
{
    nickname = nick;
}

void    ClientInfo::set_realname(string real)
{
    realname = real;
}

string  ClientInfo::get_password()
{
    return password;
}

string  ClientInfo::get_username()
{
    return username;
}

string  ClientInfo::get_nickname()
{
    return nickname;
}

string  ClientInfo::get_realname()
{
    return realname;
}

string ClientInfo::getPrefix()
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
