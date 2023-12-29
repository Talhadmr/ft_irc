
#include "../command.hpp"
#include "../RPL.hpp"


void	PASS(std::vector<ClientInfo> clients, ClientInfo ite, Server &server)
{
	string name = RPL_WELCOME(ite.get_nickname(),ite.get_username());
	send(ite.socket_fd, name.c_str() , name.size(), 0);
}
