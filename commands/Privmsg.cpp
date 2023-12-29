
#include "../command.hpp"
#include "../RPL.hpp"

void	PRIVMSG(std::vector<ClientInfo> clients, ClientInfo &ite, std::vector <Channel> &channel)
{
	std::vector<string>::iterator itArgs = ite.commands.begin();

	string message = "PRIVMSG " + *(ite.commands.begin() + 1) + " "+ *(ite.commands.begin() + 2);
	cout <<"komut::" << itArgs[1] << endl;
	for(std::vector<Channel>::iterator itChannels = channel.begin(); itChannels != channel.end(); itChannels++)
	{
		//if(itChannels->checkuser(&ite) == 1)
		//{
		//}
	}
}

