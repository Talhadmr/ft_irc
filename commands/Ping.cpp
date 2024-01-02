
#include "../command.hpp"

void	PING(std::vector<ClientInfo> clients, ClientInfo ite, Server &server)
{
	std::vector<std::string>::iterator i = ite.commands.begin();
	std::string message;
	if (ite.commands.size() != 2 && server.message.empty())
	{
		message = ERR_NEEDMOREPARAMS(*i);
		send(ite.socket_fd, message.c_str() , message.size(), 0);
		return ;
	}
	if (ite.commands.size() > 1)
	{
		i++;
		server.message = *i;
	}
	message = RPL_PONG(user_id(ite.get_nickname(), ite.get_username()), server.message);
	send(ite.socket_fd, message.c_str() , message.size(), 0);
}
