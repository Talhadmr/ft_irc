
#include "../command.hpp"
#include "../RPL.hpp"
#include "../server.hpp"

void	PASS(ClientInfo &ite, Server &server)
{
	std::string pass;
	pass = server._pass;
	std::string password = ite.get_password();
	if(password[password.length() - 2] == '\r' )
		password = password.substr(0, password.length() - 2);
	if(ite.isregister == true)
		sendmessage(ite, "462 " + ite.get_nickname() + " :Unauthorized command (already registered)\r\n");
	if(pass == password && ite.isregister == false)
	{
		ite.isregister = true;
		ite.hostname = server.hostname;
		std::string name = RPL_WELCOME(ite.get_nickname(),ite.get_username());
		send(ite.socket_fd, name.c_str() , name.size(), 0);
	}
}
