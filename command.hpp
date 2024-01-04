
#ifndef COMMAND_HPP
#define COMMAND_HPP

# define RPL_PONG(user_id, token) (user_id + " PONG " + token + "\r\n")
# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost" + "\r\n")
# define RPL_WHOREPLY(nickname, channel, user, host, server, nick, status, hopcount, realname) "352 " + nickname + " " + channel + " " + user + " " + host + " " + server + " " + nick + " " + status + " " + hopcount + " : " + realname + "\r\n"
# define RPL_ENDOFWHO(nickname, channel) "315 " + nickname + " " + channel + " :End of /WHO list" + "\r\n"
# define ERR_NEEDMOREPARAMS(cmd) (std::string("461 ") + cmd + " :Not enough parameter" + "\r\n")
# define ERR_NONICKNAMEGIVEN() ("431 :No nickname given\r\n")
# define ERR_NICKNAMEINUSE(nick) ("433 * " + nick + " :Nickname is already in use" + "\r\n")
# define ERR_ERRONEUSNICKNAME(nick) ("432 " + nick + " :Erroneus nickname")

#include "server.hpp"
#include "RPL.hpp"
#include <iostream>
#include "Channel.hpp"

class ClientInfo;
class Server;
class Channel;


void	PASS(ClientInfo &ite, Server &server);
void	PING(std::vector<ClientInfo> clients, ClientInfo ite, Server &server);
void	JOIN(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels);
void sendmessage(ClientInfo &ite, std::string message);
void	PRIVMSG(std::vector<ClientInfo> clients, ClientInfo &ite, std::vector <Channel> &channel);
void	JOIN_info(std::vector<ClientInfo> clients, ClientInfo &ite, Channel &channels);
void sendmessage_join(ClientInfo *ite, std::string message);
void	WHO(std::vector<ClientInfo> clients, ClientInfo ite, Server &server, std::vector <Channel> &channel);
void	NICK(std::vector<ClientInfo> &clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels);
void    TOPIC(std::vector<ClientInfo> &clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels);
void    CAP(std::vector<ClientInfo> clients, ClientInfo ite, Server &server);
void    MODE(std::vector<ClientInfo> clients, ClientInfo ite, Server &server, std::vector <Channel> channels);
void sendmessage_for_topic(ClientInfo &ite, std::string message);
void	PART(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels);
void	PART2(std::vector<ClientInfo> clients, std::vector <ClientInfo *>::iterator itera, Server &server, Channel &channels, std::string name);
void    USER(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels);
void sendmessage_for_part(ClientInfo *ite, std::string message);
std::vector<std::string>    user_helper(ClientInfo &ite);
void    sendmessage2(ClientInfo &sender, int socketfd, std::string message);
void	NOTICE(std::vector<ClientInfo> clients, ClientInfo &ite, std::vector <Channel> &channel);
void KICK(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels);
void sendmessage_privmsg(ClientInfo &ite,ClientInfo *clients,std::string message);

#endif
