
#include "RPL.hpp"
#include "command.hpp"
#include "server.hpp"
#include "Channel.hpp"

void    sendmessage2(ClientInfo &sender, int socketfd, string message)
{
    string buffer = sender.getPrefix() + " "  +  message + "\r\n";
    send(socketfd, buffer.c_str(), buffer.size(), 0);
}

void sendmessage_privmsg(ClientInfo &ite,ClientInfo *clients,string message)
{
	string buffer = ite.getPrefix() + " "  +  message + "\r\n";
	cout << "buffer::" << buffer << endl;
	send(clients->socket_fd, buffer.c_str(), buffer.size(), 0);
}

void sendmessage(ClientInfo &ite, string message)
{
	string buffer = ite.getPrefix() + " "  +  message + "\r\n";
	cout << "buffer::" << buffer << endl;
	send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}

void sendmessage_join(ClientInfo *ite, string message)
{
	string buffer = ite->getPrefix() + " "  +  message + "\r\n";
	cout << "buffer:" << buffer << endl;
	send(ite->socket_fd, buffer.c_str(), buffer.size(), 0);
}

void sendmessage_for_topic(ClientInfo &ite, string message)
{
	string buffer = ite.getPrefix() + " "  +  message + "\r\n";;
	send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}
void sendmessage_for_part(ClientInfo *ite, string message)
{
	string buffer = ite->getPrefix() + " "  +  message + "\r\n";;
	send(ite->socket_fd, buffer.c_str(), buffer.size(), 0);
}
