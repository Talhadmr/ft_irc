
#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include <ostream>

using std::cout;
using std::endl;
using std::string;
#include <vector>

class Channel
{
	public:
	std::vector <ClientInfo *>users;
	string getPrefix();
};

#endif
