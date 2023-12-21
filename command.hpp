
#ifndef COMMAND_HPP
#define COMMAND_HPP

# define RPL_PONG(user_id, token) (user_id + " PONG " + token + "\r\n")
# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost")

#include "server.hpp"
#include <iostream>
class ClientInfo;

using std::cout;
using std::string;


void	PASS(std::vector<ClientInfo> clients, ClientInfo ite);
int		PING(std::vector<ClientInfo> clients, ClientInfo ite);
void	JOIN(std::vector<ClientInfo> clients, ClientInfo &ite);
void send_message(std::vector<ClientInfo> clients, ClientInfo &ite,string message);

#endif
