
#include "../command.hpp"
#include "../RPL.hpp"
#include "../server.hpp"

void	PASS(ClientInfo ite, Server &server)
{
	string pass;
	pass = server._pass;
	cout << "pass:" << pass.length() << endl;
	cout << "ite pass:" << ite.get_password().length() << endl;
	if(pass == ite.get_password())
	{
		cout << "password correct" << endl;
		string name = RPL_WELCOME(ite.get_nickname(),ite.get_username());
		send(ite.socket_fd, name.c_str() , name.size(), 0);
	}
}
