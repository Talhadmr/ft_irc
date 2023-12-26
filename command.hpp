
#ifndef COMMAND_HPP
#define COMMAND_HPP

# define RPL_PONG(user_id, token) (user_id + " PONG " + token + "\r\n")
# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost" + "\r\n")
# define RPL_WHOREPLY(nickname, channel, user, host, server, nick, status, hopcount, realname) "352 " + nickname + " " + channel + " " + user + " " + host + " " + server + " " + nick + " " + status + " " + hopcount + " :" + realname + "\r\n"
# define RPL_ENDOFWHO(nickname, channel) "315 " + nickname + " " + channel + " :End of /WHO list" + "\r\n"
# define ERR_NEEDMOREPARAMS(cmd) (std::string("461 ") + cmd + " :Not enough parameter" + "\r\n")
# define ERR_NONICKNAMEGIVEN() ("431 :No nickname given\r\n")
# define ERR_NICKNAMEINUSE(nick) ("433 * " + nick + " :Nickname is already in use" + "\r\n")
# define ERR_ERRONEUSNICKNAME(nick) ("432 " + nick + " :Erroneus nickname")

#include "server.hpp"
#include <iostream>
#include "Channel.hpp"

class ClientInfo;
class Server;
class Channel;

using std::cout;
using std::string;


void	PASS(std::vector<ClientInfo> clients, ClientInfo ite, Server &server);
int		PING(std::vector<ClientInfo> clients, ClientInfo ite, Server &server);
void	JOIN(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels);
void 	sendmessage(std::vector<ClientInfo> clients, ClientInfo &ite, string message, Channel channel);
void	WHO(std::vector<ClientInfo> clients, ClientInfo ite, Server &server);
void	NICK(std::vector<ClientInfo> clients, ClientInfo ite, Server &server, std::vector <Channel> channels);
void	PRIVMSG(std::vector<ClientInfo> clients, ClientInfo &ite, std::vector <Channel> &channel);
void	JOIN_info(std::vector<ClientInfo> clients, ClientInfo &ite, Channel &channels);
void sendmessage_join(std::vector<ClientInfo> clients, ClientInfo ite, string message, Channel channel);

#endif
