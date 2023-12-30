
#include "../command.hpp"
#include "../RPL.hpp"
#include "../server.hpp"

void	PASS(ClientInfo ite, Server &server)
{
	string pass;
	pass = server._pass;
	string password = ite.get_password();
	password = password.substr(0, password.length() - 2);

	if(pass == password)
	{
		cout << "password correct" << endl;
		string name = RPL_WELCOME(ite.get_nickname(),ite.get_username());
		send(ite.socket_fd, name.c_str() , name.size(), 0);
	}
}
