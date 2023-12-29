
#include "RPL.hpp"
#include "command.hpp"
#include "server.hpp"
#include "Channel.hpp"

void sendmessage(std::vector<ClientInfo> clients, ClientInfo &ite, string message, Channel channel)
{
	string buffer = ite.getPrefix() + " "  +  message + channel.ChannelName + "\r\n";;
	send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}


void sendmessage_join(std::vector<ClientInfo> clients, ClientInfo *ite, string message, Channel channel)
{
	string buffer = ite->getPrefix() + " "  +  message + channel.ChannelName + "\r\n";;
	cout << "buffer:" << buffer << endl;
	send(ite->socket_fd, buffer.c_str(), buffer.size(), 0);
}

void sendmessage_for_topic(std::vector<ClientInfo> clients, ClientInfo &ite, string message)
{
	string buffer = ite.getPrefix() + " "  +  message + "\r\n";;
	send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}
