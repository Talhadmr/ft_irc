
#include "../command.hpp"
#include "../RPL.hpp"

void TOPIC(std::vector<ClientInfo> &clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	k++;
	for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
	{
		if(itChannels->ChannelName == *k)
		{
			if (k[1][0] == ':')
			{
				itChannels->isTopic = true;
				itChannels->setTopic(k[1]);
				std::cout << "TOPIC: " << itChannels->topic << std::endl;
				sendmessage_for_topic(ite, RPL_TOPIC(ite.get_nickname(), itChannels->ChannelName, itChannels->getTopic()));
				return ;
			}
			else
			{
				string buffer = RPL_NOTOPIC(ite.get_nickname(), itChannels->ChannelName);
				sendmessage_for_topic(ite, RPL_NOTOPIC(ite.get_nickname(), itChannels->ChannelName));
				return ;
			}
		}
	}
}

