
#include "../command.hpp"
#include "../RPL.hpp"

void CAP(std::vector<ClientInfo> clients, ClientInfo ite, Server &server)
{
	std::string a = ":" + ite.get_nickname() + "!" + ite.get_username() + "@" + ite.hostname + ":";
	std::string buffer = a + " "  +  " CAP * LS :multi-refix sasl" + "\r\n";
    send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}
