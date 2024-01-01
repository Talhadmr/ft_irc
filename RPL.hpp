
#ifndef RPL_HPP
#define RPL_HPP

#define RPL_WELCOME(nickname, username) (":irc.example.com 001 " + nickname + " :Welcome to the IRC Network " + nickname + "!" + username + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) "332 " + nickname + " " + channel + " " + topic
#define RPL_NOTOPIC(nickname, channel) "331 " + nickname + " " + channel + " :No topic is set"
# define RPL_PONG(user_id, token) (user_id + " PONG " + token + "\r\n")
# define RPL_PRIVMSG(nick, username, target, message) (":" + nick + "!" + username + "@localhost PRIVMSG " + target + " " + message + "\r\n")
# define RPL_JOIN(user_id, channel) (user_id + " JOIN :#" +  channel + "\r\n")
#define RPL_NAMREPLY(nickname, channel, nicknames) "353 " + nickname + " = " + channel + " :" + nicknames + "\r\n"
#define RPL_ENDOFNAMES(nickname, channel) "366 " + nickname + " " + channel + " :End of /NAMES list" + "\r\n"
# define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel" + "\r\n"
# define ERR_NOSUCHNICK(nickname) "401 " + nickname + " :No such nick/channel" + "\r\n"
# define RPL_NICK(oldnick, username, newnick) (":" + oldnick + "!" + username + "@localhost NICK: " +  newnick + "\r\n")
# define user_id(nickname, username) (":" + nickname + "!" + username + "@localhost" + "\r\n")
# define RPL_WHOREPLY(nickname, channel, user, host, server, nick, status, hopcount, realname) "352 " + nickname + " " + channel + " " + user + " " + host + " " + server + " " + nick + " " + status + " " + hopcount + " : " + realname + "\r\n"
# define RPL_ENDOFWHO(nickname, channel) "315 " + nickname + " " + channel + " :End of /WHO list" + "\r\n"
# define ERR_NEEDMOREPARAMS(cmd) (std::string("461 ") + cmd + " :Not enough parameter" + "\r\n")
# define ERR_NONICKNAMEGIVEN() ("431 :No nickname given\r\n")
# define ERR_NICKNAMEINUSE(nick) ("433 * " + nick + " :Nickname is already in use" + "\r\n")
# define ERR_ERRONEUSNICKNAME(nick) ("432 " + nick + " :Erroneus nickname")


#endif
