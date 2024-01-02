
#include "../command.hpp"
#include "../RPL.hpp"

void PART2(ClientInfo &sender, std::string message, Channel &channel)
{
    for (std::vector<ClientInfo *>::iterator itUser = channel.users.begin(); itUser != channel.users.end(); itUser++)
    {

        sendmessage2(sender, (*itUser)->socket_fd, message);
    }
}


void PART(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
    std::vector<std::string>::iterator k = ite.commands.begin();
	if(ite.commands.size() == 3)
	{
		std::string name;
		for(std::vector<std::string>::iterator k = ite.commands.begin(); k != ite.commands.end(); k++)
		{
			name += *k;
			name += " ";
		}
		for(std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{
			if(k[1] == itChannels->ChannelName)
			{
				if(channels.size() >= 1)
				{
					for(std::vector<ClientInfo *>::iterator users1 = itChannels->users.begin(); users1 != itChannels->users.end(); users1++)
					{
						if(itChannels->users.size() > 1)
						{
							if ((*users1)->get_nickname() == ite.get_nickname())
							{
								PART2(ite, "PART " + itChannels->ChannelName + " :" + name, *itChannels);
								itChannels->users.erase(users1);
								for(std::vector<Channel>::iterator ite1 = ite.isjoined.begin(); ite1 != ite.isjoined.end(); ite1++)
								{
									if(ite1->ChannelName == itChannels->ChannelName)
									{
										ite.isjoined.erase(ite1);
										break ;
									}
								}
								break ;
							}
						}
						else if(itChannels->users.size() == 1)
						{
							if ((*users1)->get_nickname() == ite.get_nickname())
							{
								PART2(ite, "PART " + itChannels->ChannelName + " :" + name, *itChannels);
								itChannels->users.erase(users1);
								channels.erase(itChannels);
								for(std::vector<Channel>::iterator ite1 = ite.isjoined.begin(); ite1 != ite.isjoined.end(); ite1++)
								{
									if(ite1->ChannelName == itChannels->ChannelName)
									{
										ite.isjoined.erase(ite1);
										break ;
									}
								}
								return ;
							}
						}
					}
				}
			}
		}
	}
}

