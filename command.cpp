
#include "RPL.hpp"

#include "command.hpp"

#include "server.hpp"


void	PASS(std::vector<ClientInfo> clients, ClientInfo ite)
{
	string name = RPL_WELCOME(ite.get_nickname(),ite.get_username());
	cout << ite.socket_fd << endl;
	send(ite.socket_fd, name.c_str() , name.size(), 0);
}
