
#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include <ostream>
#include "Client.hpp"

using std::endl;
using std::string;
#include <vector>

class Channel
{
	public:
	std::vector <ClientInfo *>users;
	string ChannelName;
	string getPrefix();
};

#endif
