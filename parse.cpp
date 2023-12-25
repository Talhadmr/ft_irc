
#include "server.hpp"
#include "RPL.hpp"
#include "Client.hpp"

# define RPL_JOIN(user_id, channel) (user_id + " JOIN :#" +  channel + "\r\n")
void	command_info(string buffer,std::vector<ClientInfo> clients, ClientInfo &ite)
{
	int i = 0;
	std::vector <string> name;
	int index = buffer.find('\n',i);
	name.push_back(buffer.substr(i, index + 1));
	int indexx = buffer.find('\n',(index + 1));
	name.push_back(buffer.substr(index + 1, indexx - index));
	name.push_back(buffer.substr(indexx + 1, buffer.length() - 2));
	std::vector<string>::iterator k = name.begin();
	k = name.begin();
	i = 0;
	index = k->find(':',i);


	ite.set_password(k->substr(index + 1, k++->length() - 2));
	 i = 0;
	 index = k->find(' ',i);
	 ite.set_nickname(k->substr(index + 1, k++->length() - (index + 3)));
	 i = 0;
	 index = k->find(' ',i);
	 indexx = k->find(' ',index + 1);
	 ite.set_username(k->substr(index + 1, indexx - (index + 1)));
}

void	command_message(string buffer,std::vector<ClientInfo> clients,ClientInfo &ite)
{
	int a = buffer.length() - 2;
	string temp = buffer.substr(0,a);
	int index;
	int flag;
	for(int i = 0; i < a; i++)
	{
		flag = 0;
		while (temp[i] == ' ' && i < a)
			i++;
		if (i < a)
			index = i;
		while (temp[i] != ' ' && i < a)
		{
			flag = 1;
			i++;
		}
		if (flag == 1)
			ite.commands.push_back(temp.substr(index, i - index));
	}
	// std::vector<std::string>::iterator kk = ite.commands.begin();
	// while (kk != ite.commands.end())
	// 	cout << "COMMANDS::: " << *kk++ << endl;
 }

void	search_command(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	//cout <<"*kkkkk:::::" <<*k << endl;
	std::string error;
	if (*k == "PASS")
		PASS(clients, ite, server);
	else if(*k == "JOIN")
		JOIN(clients, ite, server, channels);
	else if (*k == "PING")
		PING(clients, ite, server);
	else if (*k == "TOPIC")
		TOPIC(clients, ite, server, channels);
	else if(*k == "CAP")
		CAP(clients, ite, server);
	else if (*k == "WHO")
	{
		if (ite.commands.size() == 1)
		{
			error = ERR_NEEDMOREPARAMS("WHO");
			send(ite.socket_fd, error.c_str() , error.size(), 0);
		}
		else
			WHO(clients,ite, server);
	}
	else if (*k == "NICK")
	{
		if (ite.commands.size() == 1)
		{
			error = ERR_NONICKNAMEGIVEN();
			send(ite.socket_fd, error.c_str() , error.size(), 0);
		}
		else
			NICK(clients, ite, server, channels);	
	}
	for (std::vector<std::string>::iterator it = ite.commands.begin(); it != ite.commands.end(); ++it) {
            it->clear();
    }
    ite.commands.erase(std::remove(ite.commands.begin(), ite.commands.end(), ""), ite.commands.end());
}
