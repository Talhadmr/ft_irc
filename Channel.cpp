
#include "Channel.hpp"

Channel::Channel(string name, ClientInfo *user, ClientInfo *admin)
{
    this->isTopic = false;
    this->topic = "";
    this->ChannelName = name;
    users.push_back(user);
    this->admin.push_back(admin);
}

void Channel::adduser(ClientInfo *client)
{
    this->users.push_back(client);
}

string Channel::getTopic()
{
    return this->topic;
}

void Channel::setTopic(string topic)
{
    size_t colonPosition;
    colonPosition = topic.find(':');

    if (colonPosition != std::string::npos)
    {
        std::string result = topic.substr(colonPosition + 1);
        this->topic = result;
    }
    else
        std::cerr << "Hata: ':' karakteri bulunamadı." << std::endl;
}

