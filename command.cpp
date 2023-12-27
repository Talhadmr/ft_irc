
#include "RPL.hpp"
#include "command.hpp"
#include "server.hpp"
#include "Channel.hpp"
# define RPL_PRIVMSG(nick, username, target, message) (":" + nick + "!" + username + "@localhost PRIVMSG " + target + " " + message + "\r\n")
# define RPL_JOIN(user_id, channel) (user_id + " JOIN :#" +  channel + "\r\n")
#define RPL_NAMREPLY(nickname, channel, nicknames) "353 " + nickname + " = " + channel + " :" + nicknames + "\r\n"
#define RPL_ENDOFNAMES(nickname, channel) "366 " + nickname + " " + channel + " :End of /NAMES list" + "\r\n"

void	PASS(std::vector<ClientInfo> clients, ClientInfo ite, Server &server)
{
	string name = RPL_WELCOME(ite.get_nickname(),ite.get_username());
	send(ite.socket_fd, name.c_str() , name.size(), 0);
}

int	PING(std::vector<ClientInfo> clients, ClientInfo ite, Server &server)
{
	std::vector<std::string>::iterator i = ite.commands.begin();
	i++;
	string name = RPL_PONG(user_id(ite.get_nickname(), ite.get_username()), *i);
	send(ite.socket_fd, name.c_str() , name.size(), 0);
	return (1);
}

void sendmessage(std::vector<ClientInfo> clients, ClientInfo &ite, string message, Channel channel)
{
	string buffer = ite.getPrefix() + " "  +  message + channel.ChannelName + "\r\n";;
	send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}


void sendmessage_join(std::vector<ClientInfo> clients, ClientInfo *ite, string message, Channel channel)
{
	string buffer = ite->getPrefix() + " "  +  message + channel.ChannelName + "\r\n";;
	send(ite->socket_fd, buffer.c_str(), buffer.size(), 0);
}

void	JOIN_info(std::vector<ClientInfo> clients, ClientInfo &ite, Channel &channels)
{
	string names;
	std::vector <ClientInfo *> a= channels.users;
	std::vector <ClientInfo *> b= channels.admin;
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
	cout << "names::" << names << endl;
	for(std::vector <ClientInfo *>::iterator itera = a.begin() ; itera != a.end(); itera++)
	{
		sendmessage_join(clients, (*itera), RPL_NAMREPLY((*itera)->get_nickname(), channels.ChannelName, names), channels);
	}
}

void sendmessage_for_topic(std::vector<ClientInfo> clients, ClientInfo &ite, string message)
{
	string buffer = ite.getPrefix() + " "  +  message + "\r\n";;
	send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
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


void	WHO(std::vector<ClientInfo> clients, ClientInfo ite, Server &server) // WHO kullanıcı adı || kanal adı şeklinde olucak kişinin bulunduğu kanallara ihtiyac var. clienta eklenmeli.
{
	string name = RPL_WHOREPLY(ite.get_nickname(), "channelname", ite.get_username(), server.hostname, "localhost", ite.get_nickname(), "*", "0 ", "baran"); //kanal adı ekle channelname
	string name2= RPL_ENDOFWHO(ite.get_nickname(), "channelname");
	send(ite.socket_fd, name.c_str() , name.size(), 0);
	send(ite.socket_fd, name2.c_str() , name2.size(), 0);
}

void	NICK(std::vector<ClientInfo> clients, ClientInfo ite, Server &server, std::vector <Channel> channel) // bütün kanallara nick eklendi mesajı gönder join yapıldıktan sonra -- ite.nickname değişmiyor -- bütün clientlarda nickname karşılaştır
{
	std::vector<ClientInfo>::iterator c = clients.begin();
	std::vector<std::string>::iterator k = c->commands.begin();
	int size = clients.size();
	k++;
	std::string error;
	cout << ite.get_nickname() << endl;
	for (int i = 0; i < k->length(); i++)
	{
		if (!std::isprint(k[0][i]))
		{
			error = ERR_ERRONEUSNICKNAME(*k);
			cout << "KONTROL 4444"<< endl;
			send(ite.socket_fd, error.c_str() , error.size(), 0);
			return ;
		}
	}
	if (std::isdigit(k[0][0]))
	{
		error = ERR_ERRONEUSNICKNAME(*k);
		cout << "KONTROL 3333"<< endl;
		send(ite.socket_fd, error.c_str() , error.size(), 0);
		return ;
	}
	for (int index = 0; index < size; index++)
	{
		if (c->get_nickname() == *k)
		{
			cout << "KONTROL 2222"<< endl;
			error = ERR_NICKNAMEINUSE(*k);
			send(ite.socket_fd, error.c_str() , error.size(), 0);
			return ;
		}
		c++;
	}
	cout << "KONTROL 111111"<< endl;
	c->set_nickname(*k);
	std::string buffer = ":" + c->get_nickname() + "!" + c->get_username() + "@" + server.hostname + ": " + "NICK Requesting the new nick " + c->get_nickname() + "\r\n";
	if (send(ite.socket_fd, buffer.c_str(), buffer.size(), 0) < 0)
		cout << "SEND ERROR" << endl;
}

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
				sendmessage_for_topic(clients, ite, RPL_TOPIC(ite.get_nickname(), itChannels->ChannelName, itChannels->getTopic()));
				return ;
			}
			else
			{
				string buffer = RPL_NOTOPIC(ite.get_nickname(), itChannels->ChannelName);
				sendmessage_for_topic(clients, ite, RPL_NOTOPIC(ite.get_nickname(), itChannels->ChannelName));
				return ;
			}
		}
	}
}

void CAP(std::vector<ClientInfo> clients, ClientInfo ite, Server &server)
{
	string buffer = ite.getPrefix() + " "  +  " CAP * LS :multi-refix sasl" + "\r\n";
    send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}

void MODE(std::vector<ClientInfo> clients, ClientInfo ite, Server &server, std::vector <Channel> channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();

	std::cout << "modus\n";
	if(k[2] == "+o")
	{
		for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{
			std::cout << "+o is working\n" << std::endl;
			//"Mode " + itChannels->ChannelName + " +o " + k[3] + "\r\n"
			sendmessage(clients, ite, "Mode " + itChannels->ChannelName + " +o " + k[3] + "", (*itChannels));
		}

		// std::cout << "MODE: " << *k << std::endl;
		// string buffer = ite.getPrefix() + " "  +  " MODE " + k[1] + " +o " + k[3] + "\r\n";
		// send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
	}
	else if(k[2] == "-o")
	{
		for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{
			std::cout << "-o is working\n" << std::endl;
			sendmessage(clients, ite, "Mode " + itChannels->ChannelName + " -o " + k[3], (*itChannels));
		}
	}
}

