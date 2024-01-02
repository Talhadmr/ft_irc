
#include "../RPL.hpp"
#include "../command.hpp"

void	WHO(std::vector<ClientInfo> clients, ClientInfo ite, Server &server, std::vector <Channel> &channel) //99.satıra kanal adı ekle. 82ye realname ekle
{
	std::string error;
	int flag = 0;
	if (ite.commands[1][0] == '#')
	{
		int counter = 0;
		for (std::vector<Channel>::iterator itChannels = server.channels.begin(); itChannels != server.channels.end(); itChannels++)
		{
			if (itChannels->ChannelName == ite.commands[1])
				flag = 1;
			counter++;
		}
		if (counter == 0 || flag == 0)
		{
			error = ERR_NOSUCHCHANNEL(ite.commands[1]);
			send(ite.socket_fd, error.c_str(), error.size(), 0);
			return ;
		}
		std::vector<Channel>::iterator itChannels = server.channels.begin();
		while (itChannels != server.channels.end())
		{
			if (itChannels->ChannelName == ite.commands[1])
			{
				for(std::vector<ClientInfo *>::iterator users = itChannels->users.begin(); users != itChannels->users.end(); users++)
				{
					std::string message = RPL_WHOREPLY((*users)->get_nickname(), itChannels->ChannelName, (*users)->get_username(), server.hostname, "localhost", (*users)->get_nickname(), "*", "0 ", (*users)->get_realname());
					send(ite.socket_fd, message.c_str() , message.size(), 0);
				}
				std::string message2= RPL_ENDOFWHO(ite.get_nickname(), itChannels->ChannelName);
				send(ite.socket_fd, message2.c_str() , message2.size(), 0);
			}
			itChannels++;
		}
	}
	else
	{
		flag = 0;
		int flag2;
		for (std::vector<ClientInfo>::iterator users = clients.begin(); users != clients.end(); users++)
		{
			flag2 = 0;
			for(std::vector<Channel>::iterator c = users->isjoined.begin(); c != users->isjoined.end(); c++)
			{
				flag2 = 1;
				if (users->get_nickname() == ite.commands[1])
				{
					flag = 1;
					std::string message = RPL_WHOREPLY(users->get_nickname(), c->ChannelName, users->get_username(), server.hostname, "localhost", users->get_nickname(), "*", "0 ", users->get_realname());
					send(ite.socket_fd, message.c_str() , message.size(), 0);
					message = RPL_ENDOFWHO(users->get_nickname(), c->ChannelName);
					send(ite.socket_fd, message.c_str() , message.size(), 0);
				}
			}
			if (flag2 == 0)
			{
				if (users->get_nickname() == ite.commands[1])
				{
					flag = 1;
					std::string message = RPL_WHOREPLY(users->get_nickname(),"*", users->get_username(), server.hostname, "localhost", users->get_nickname(), "*", "0", users->get_realname());
					send(ite.socket_fd, message.c_str() , message.size(), 0);
					message = RPL_ENDOFWHO(users->get_nickname(), "channel");
					send(ite.socket_fd, message.c_str() , message.size(), 0);
					return ;
				}
			}

		}
		if (flag == 0)
		{
			error = ERR_NOSUCHNICK(ite.commands[1]);
			send(ite.socket_fd, error.c_str(), error.size(), 0);
			return ;
		}
	}
}
