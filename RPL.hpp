
#ifndef RPL_HPP
#define RPL_HPP

#define RPL_WELCOME(nickname, username) (":irc.example.com 001 " + nickname + " :Welcome to the IRC Network " + nickname + "!" + username + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) "332 " + nickname + " " + channel + " " + topic 
#define RPL_NOTOPIC(nickname, channel) "331 " + nickname + " " + channel + " :No topic is set"

#endif
