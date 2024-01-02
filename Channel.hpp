
#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include <ostream>
#include "Client.hpp"
#include <vector>
#include "Client.hpp"


class ClientInfo;

class Channel
{
	public:
	std::vector <ClientInfo *>users;

	std::vector <ClientInfo *>admin;

	bool isTopic;
	std::string topic;

	std::string ChannelName;
	std::string getPrefix();
	Channel(std::string, ClientInfo *, ClientInfo *);
	void adduser(ClientInfo *client);
	int checkuser(ClientInfo *client);
	void setTopic(std::string topic);
	std::string getTopic();
};

#endif
