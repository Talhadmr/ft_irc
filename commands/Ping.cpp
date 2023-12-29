
#include "../command.hpp"

int	PING(std::vector<ClientInfo> clients, ClientInfo ite, Server &server)
{
	std::vector<std::string>::iterator i = ite.commands.begin();
	i++;
	string name = RPL_PONG(user_id(ite.get_nickname(), ite.get_username()), *i);
	send(ite.socket_fd, name.c_str() , name.size(), 0);
	return (1);
}
