
#include "../command.hpp"
#include "../RPL.hpp"

void QUIT(std::vector<ClientInfo> &clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	cout <<	"QUİT::"<< *k << endl;
	cout <<	"QUİT1::"<< k[1] << endl;
	cout <<	"QUİT2::"<< k[2] << endl;
	PART(clients, ite, server, channels);
//	for(std::vector<Channel>::iterator ite1 = channels.begin(); ite1 != channels.end(); ite1++)
//	{
//	}
}
