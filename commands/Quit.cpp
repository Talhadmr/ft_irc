
#include "../command.hpp"
#include "../RPL.hpp"

void QUIT(std::vector<ClientInfo> &clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	PART(clients, ite, server, channels);
//	for(std::vector<Channel>::iterator ite1 = channels.begin(); ite1 != channels.end(); ite1++)
//	{
//	}
}
