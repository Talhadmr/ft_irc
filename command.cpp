
#include "RPL.hpp"
#include "command.hpp"
#include "server.hpp"
#include "Channel.hpp"

# define RPL_JOIN(user_id, channel) (user_id + " JOIN :#" +  channel + "\r\n")

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


void	JOIN(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	*k++;
	cout <<"join::::" <<k[0][0] << endl;
	if(k[0][0] == '#')
	{
		for (std::vector<Channel>::iterator itChannels = channels.begin(); itChannels != channels.end(); itChannels++)
		{
			if(itChannels->ChannelName == *k)
			{
				ClientInfo *userPtr1 = &ite;
				itChannels->adduser(userPtr1);
				sendmessage(clients, ite, "JOIN You are now in channel ", (*itChannels));
				return ;
			}
		}
		ClientInfo *userPtr = &ite;
		Channel newChannel = Channel((*k), userPtr);
		channels.push_back(newChannel);
		sendmessage(clients, ite, "JOIN You are now in channel ", newChannel);
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