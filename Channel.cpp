
#include "Channel.hpp"

Channel::Channel(string name, ClientInfo *user)
{
    this->ChannelName = name;
    users.push_back(user);
}

void Channel::adduser(ClientInfo *client)
{
    this->users.push_back(client);
}


