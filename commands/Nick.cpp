
#include "../command.hpp"
#include "../RPL.hpp"

void	NICK(std::vector<ClientInfo> &clients, ClientInfo &ite, Server &server, std::vector <Channel> &channel) // bütün kanallara nick eklendi mesajı gönder join yapıldıktan sonra -- ite.nickname değişmiyor -- bütün clientlarda nickname karşılaştır
{
	std::vector<Channel>::iterator t = channel.begin();
	if (t != channel.end())
		std::vector<ClientInfo *>:: iterator cc = t->users.begin();
	std::vector<ClientInfo>::iterator cc = clients.begin();
	std::vector<std::string>::iterator k = ite.commands.begin();
	int size = clients.size();
	k++;
	std::string error;
	if (server.flag == 1)
	{
		cout << cc->get_nickname() << endl;
		server.flag = 0;
		return ;
	}
	for (int i = 0; i < k->length(); i++)
	{
		if (!std::isprint(k[0][i]))
		{
			error = ERR_ERRONEUSNICKNAME(*k);
			send(ite.socket_fd, error.c_str() , error.size(), 0);
			return ;
		}
	}
	if (std::isdigit(k[0][0]))
	{
		error = ERR_ERRONEUSNICKNAME(*k);
		send(ite.socket_fd, error.c_str() , error.size(), 0);
		return ;
	}
	for (int index = 0; index < size; index++)
	{
		if (cc->get_nickname() == *k)
		{
			error = ERR_NICKNAMEINUSE(*k);
			if(send(ite.socket_fd, error.c_str() , error.size(), 0) < 0)
				cout << "SEND ERROR"<< endl;
			return ;
		}
		cc++;
	}
	cc = clients.begin();
	for (int index = 0; index < size; index++)
	{
		if (cc->get_nickname() == ite.get_nickname())
		{
			std::string buffer = RPL_NICK(ite.get_nickname(), ite.get_username(), *k);
			cc->set_nickname(*k);
			ite.set_nickname(*k);
			cout << "NICK Requesting the new nick " + cc->get_nickname() + "\r\n" << endl;
			if (send(ite.socket_fd, buffer.c_str(), buffer.size(), 0) < 0)
				cout << "SEND ERROR" << endl;
		}
		cc++;
	}
}
