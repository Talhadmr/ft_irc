
#include "RPL.hpp"

#include "command.hpp"

#include "server.hpp"


void	PASS(std::vector<ClientInfo> clients, ClientInfo ite)
{
	string name = RPL_WELCOME(ite.get_nickname(),ite.get_username());
	send(ite.socket_fd, name.c_str() , name.size(), 0);
}

int	PING(std::vector<ClientInfo> clients, ClientInfo ite)
{
	string name = RPL_PONG(user_id(ite.get_nickname(), ite.get_username()), ite.argumant1);
	send(ite.socket_fd, name.c_str() , name.size(), 0);
	return (1);
}

void	JOIN(std::vector<ClientInfo> clients, ClientInfo &ite)
{
	string message = " JOIN You are now in channel ";
	string buffer = ite.getPrefix() + " "  +  message + "\r\n";;
	send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}
