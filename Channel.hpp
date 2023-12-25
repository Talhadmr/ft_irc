
#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include <ostream>
#include "Client.hpp"
#include <vector>

using std::endl;
using std::string;

class ClientInfo;

class Channel
{
	public:
	std::vector <ClientInfo *>users;
	string topic;
	string ChannelName;
	string getPrefix();
	Channel(string, ClientInfo *);
	void adduser(ClientInfo *client);
	void setTopic(string topic);
	string getTopic();
};

#endif
