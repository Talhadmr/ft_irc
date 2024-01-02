
#include "../command.hpp"
#include "../RPL.hpp"

void	JOIN_info(std::vector<ClientInfo> clients, ClientInfo &ite, Channel &channels)
{
	std::string names;
	std::vector <ClientInfo *> a= channels.users;
	for(std::vector <ClientInfo *>::iterator itera = a.begin() ; itera != a.end(); itera++)
	{
		if(itera == a.begin())
		{
			names = "@";
			names += (*itera)->get_nickname();
		}
		else
		{
			names += " ";
			names += (*itera)->get_nickname();
		}
	}
	for(std::vector <ClientInfo *>::iterator itera = a.begin() ; itera != a.end(); itera++)
	{
		sendmessage_join((*itera), RPL_NAMREPLY((*itera)->get_nickname(), channels.ChannelName, names));
		sendmessage_join((*itera), RPL_ENDOFNAMES((*itera)->get_nickname(), channels.ChannelName));
	}
}
int	JOIN_check(std::vector <Channel>::iterator itChannels, ClientInfo &ite)
{
	for(std::vector <ClientInfo *>::iterator itera = itChannels->users.begin() ; itera != itChannels->users.end(); itera++)
	{
		if((*itera)->get_nickname() == ite.get_nickname())
			return (1);
	}
	return (0);
}
void	JOIN(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	*k++;
	if(k[0][0] == '#')
	{
		for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{
			if(itChannels->ChannelName == *k)
			{
				if(JOIN_check(itChannels, ite) == 1)
					return ;
				ClientInfo *userPtr1 = &ite;
				itChannels->adduser(userPtr1);
				ite.isjoined.push_back(*itChannels);
				sendmessage(ite, "JOIN You are now in channel " + itChannels->ChannelName);
				JOIN_info(clients, ite, *itChannels);
				return ;
			}
		}
		ClientInfo *userPtr = &ite;
		Channel newChannel = Channel((*k), userPtr, userPtr);
		ite.isjoined.push_back(newChannel);
		channels.push_back(newChannel);
		sendmessage(ite, " JOIN You are now in channel " + newChannel.ChannelName);
		std::string buffer = RPL_NOTOPIC(ite.get_nickname(), newChannel.ChannelName);
		sendmessage_for_topic(ite, RPL_NOTOPIC(ite.get_nickname(), newChannel.ChannelName));
		JOIN_info(clients, ite, newChannel);
	}
}
