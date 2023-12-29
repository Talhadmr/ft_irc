
#include "../command.hpp"
#include "../RPL.hpp"

void	PART2(std::vector<ClientInfo> clients, std::vector <ClientInfo *>::iterator itera, Server &server, Channel &channels)
{
		sendmessage_join(clients, (*itera), "PART #A :No boundaries on the net!\r\n", channels);
}


void PART(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
    std::vector<std::string>::iterator k = ite.commands.begin();
    std::vector<Channel>::iterator a = ite.isjoined.begin();
	//std::vector<Channel>::iterator b = channels.begin();

	for(std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
	{
		if(k[1] == itChannels->ChannelName)
		{
			if(channels.size() >= 1)
			{
				for(std::vector<ClientInfo *>::iterator users1 = itChannels->users.begin(); users1 != itChannels->users.end(); users1++)
				{
					cout << "users1:" << (*users1)->get_nickname() << endl;
					if(itChannels->users.size() > 1)
					{
						if ((*users1)->get_nickname() == ite.get_nickname())
						{
							PART2(clients, users1, server, *itChannels);
							users1 = itChannels->users.erase(users1);
							JOIN_info(clients, ite, *itChannels);
							break ;
						}
					}
					//else
					//	if ((*users1)->get_nickname() == ite.get_nickname())
					//	{
					//		itChannels->users.clear();
					//		break;
					//	}
				}
			}
		}
	}
}

