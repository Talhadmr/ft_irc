
#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include <ostream>
#include "Client.hpp"
#include <vector>
#include "Client.hpp"

using std::endl;
using std::string;

class ClientInfo;

class Channel
{
	public:
	std::vector <ClientInfo *>users;
	std::vector <ClientInfo *>admin;
	string ChannelName;
	string getPrefix();
	Channel(string, ClientInfo *, ClientInfo *);
	void adduser(ClientInfo *client);
	int checkuser(ClientInfo *client);
};

#endif
