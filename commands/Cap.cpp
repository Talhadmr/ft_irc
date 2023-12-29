
#include "../command.hpp"
#include "../RPL.hpp"

void CAP(std::vector<ClientInfo> clients, ClientInfo ite, Server &server)
{
	string buffer = ite.getPrefix() + " "  +  " CAP * LS :multi-refix sasl" + "\r\n";
    send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}
