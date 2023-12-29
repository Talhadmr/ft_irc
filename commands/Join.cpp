
#include "../command.hpp"
#include "../RPL.hpp"

void	JOIN_info(std::vector<ClientInfo> clients, ClientInfo &ite, Channel &channels)
{
	string names;
	std::vector <ClientInfo *> a= channels.users;
	std::vector <ClientInfo *> b= channels.admin;
	cout << "******" << endl;
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
		cout << "message "<< names << endl;
		sendmessage_join(clients, (*itera), RPL_NAMREPLY((*itera)->get_nickname(), channels.ChannelName, names), channels);
	}
}

void	JOIN(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	*k++;
	cout << ite.get_nickname() << endl;
	if(k[0][0] == '#')
	{
		for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{
			if(itChannels->ChannelName == *k)
			{
				ClientInfo *userPtr1 = &ite;
				itChannels->adduser(userPtr1);
				ite.isjoined.push_back(*itChannels);
				sendmessage(clients, ite, "JOIN You are now in channel ", (*itChannels));
				JOIN_info(clients, ite, *itChannels);
				return ;
			}
		}
		int i = 1;
		ClientInfo *userPtr = &ite;
		Channel newChannel = Channel((*k), userPtr, userPtr);
		ite.isjoined.push_back(newChannel);
		channels.push_back(newChannel);

		sendmessage(clients, ite, "JOIN You are now in channel ", newChannel);
		JOIN_info(clients, ite, newChannel);
	}
}
