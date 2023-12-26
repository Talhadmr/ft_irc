
#include "Channel.hpp"

Channel::Channel(string name, ClientInfo *user, ClientInfo *admin)
{
    this->ChannelName = name;
    users.push_back(user);
    this->admin.push_back(admin);
}

void Channel::adduser(ClientInfo *client)
{
    this->users.push_back(client);
}

int Channel::checkuser(ClientInfo *client)
{
    for(std::vector<ClientInfo *>::iterator it = users.begin(); it != users.end(); ++it)
    {
        if((*it)->get_nickname() == client->get_nickname())
            return 1;
    }
    return 0;
}
