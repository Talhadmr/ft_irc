
#include "RPL.hpp"
#include "command.hpp"
#include "server.hpp"
#include "Channel.hpp"

void    sendmessage2(ClientInfo &sender, int socketfd, std::string message)
{
    std::string buffer = sender.getPrefix() + " "  +  message + "\r\n";
    send(socketfd, buffer.c_str(), buffer.size(), 0);
}

void sendmessage_privmsg(ClientInfo &ite,ClientInfo *clients,std::string message)
{
	std::string buffer = ite.getPrefix() + " "  +  message + "\r\n";
	send(clients->socket_fd, buffer.c_str(), buffer.size(), 0);
}

void sendmessage(ClientInfo &ite, std::string message)
{
	std::string buffer = ite.getPrefix() + " "  +  message + "\r\n";

	send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}

void sendmessage_join(ClientInfo *ite, std::string message)
{
	std::string buffer = ite->getPrefix() + " "  +  message + "\r\n";
	send(ite->socket_fd, buffer.c_str(), buffer.size(), 0);
}

void sendmessage_for_topic(ClientInfo &ite, std::string message)
{
	std::string buffer = ite.getPrefix() + " "  +  message + "\r\n";;
	send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}
void sendmessage_for_part(ClientInfo *ite, std::string message)
{
	std::string buffer = ite->getPrefix() + " "  +  message + "\r\n";;
	send(ite->socket_fd, buffer.c_str(), buffer.size(), 0);
}
