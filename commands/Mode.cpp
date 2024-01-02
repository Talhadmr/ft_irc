
#include "../command.hpp"
#include "../RPL.hpp"

void MODE(std::vector<ClientInfo> clients, ClientInfo ite, Server &server, std::vector <Channel> channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	string names;


	if(k[2] == "+o")
	{
		for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{

			if(itChannels->ChannelName == k[1])
			{
				names = '@' + k[3];
				std::cout << "+o is working\n" << std::endl;
				sendmessage(ite, "Mode " + itChannels->ChannelName + " +o " +k[3]);
				for(std::vector <ClientInfo *>::iterator itera = itChannels->users.begin() ; itera != itChannels->users.end(); itera++)
				{
					cout << "message "<< names << endl;
					(*itera)->set_nickname(names);
					sendmessage_join((*itera), RPL_NAMREPLY((*itera)->get_nickname(), k[1], names));
					//sendmessage_join(clients, (*itera), RPL_NAMREPLY((*itera)->get_nickname(), k[1], names), itChannels);
					//void sendmessage_join(std ::vector<ClientInfo> clients, ClientInfo *ite, string message, Channel channel)
				}
			}
		}

		// send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
	}
	else if(k[2] == "-o")
	{
		for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{
			if(itChannels->ChannelName == k[1])
			{
				std::cout << "-o is working\n" << std::endl;
				sendmessage(ite, "Mode " + itChannels->ChannelName + " -o " + k[3]);
				for(std::vector <ClientInfo *>::iterator itera = itChannels->users.begin() ; itera != itChannels->users.end(); itera++)
				{
					sendmessage_join((*itera), RPL_NAMREPLY((*itera)->get_nickname(), k[1], k[3]));
					//sendmessage_join(clients, (*itera), RPL_NAMREPLY((*itera)->get_nickname(), k[1], names), itChannels);
					//void sendmessage_join(std ::vector<ClientInfo> clients, ClientInfo *ite, string message, Channel channel)
				}
			}
		}
	}
}
