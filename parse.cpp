
#include "server.hpp"
#include "RPL.hpp"
#include "Client.hpp"
#include "command.hpp"




void nc_control(std::string buffer,std::vector<ClientInfo> clients,ClientInfo &it)
{
    char temp[1024];
	std::cout << "debug\n";
	command:
    std::string pass = "Please enter the password: ";
	memset(temp, 0, sizeof(temp));

	send(it.socket_fd, pass.c_str() , pass.size(), 0);
    int bytes_received = recv(it.socket_fd, temp, sizeof(buffer), 0);

    if(temp[0])
    {
		std::string strTemp(temp);
		strTemp = strTemp.substr(0, strTemp.size() - 1);
		std::strcpy(temp, strTemp.c_str());
        it.set_password(temp);
    }
    else
        goto command;
    command1:
	std::string nick = "Please enter the nickname: ";
    send(it.socket_fd, nick.c_str() , nick.size(), 0);
	memset(temp, 0, sizeof(temp));
	bytes_received = recv(it.socket_fd, temp, sizeof(buffer), 0);
    //getline(std::cin, temp);
    if(temp[0])
    {
		std::string strTemp(temp);
		strTemp = strTemp.substr(0, strTemp.size() - 1);
		std::strcpy(temp, strTemp.c_str());
        it.set_nickname(temp);
    }
    else
        goto command1;
    command2:
    std::string username =  "Please enter the username: ";
	memset(temp, 0, sizeof(temp));
	send(it.socket_fd, username.c_str() , username.size(), 0);
	bytes_received = recv(it.socket_fd, temp, sizeof(buffer), 0);
    if(temp[0])
    {
		std::string strTemp(temp);
		strTemp = strTemp.substr(0, strTemp.size() - 1);
		std::strcpy(temp, strTemp.c_str());
        it.set_username(temp);
    }
    else
        goto command2;
    command3:
    std::string realname = "Please enter the realname: ";
    send(it.socket_fd, realname.c_str() , realname.size(), 0);
	memset(temp, 0, sizeof(temp));

	bytes_received = recv(it.socket_fd, temp, sizeof(buffer), 0);
    if(temp[0])
    {
		std::string strTemp(temp);
		strTemp = strTemp.substr(0, strTemp.size() - 1);
		std::strcpy(temp, strTemp.c_str());
        it.set_realname(temp);
    }
    else
        goto command3;
}

void	command_info(std::string buffer,std::vector<ClientInfo> clients, ClientInfo &ite)
{
	int i = 0;
	std::vector <std::string> name;
	int index = buffer.find('\n',i);
	name.push_back(buffer.substr(i, index + 1));
	int indexx = buffer.find('\n',(index + 1));
	name.push_back(buffer.substr(index + 1, indexx - index));
	name.push_back(buffer.substr(indexx + 1, buffer.length() - 2));
	std::vector<std::string>::iterator k = name.begin();
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
	index = k->find(':', indexx);
	ite.set_realname(k->substr(index + 1, (k->length() - index) - 3));
}

void    command_message(std::string buffer,std::vector<ClientInfo> clients,ClientInfo &ite)
{
    int a;
    if (buffer[buffer.length() - 2] == '\r')
        a = buffer.length() - 2;
    else
        a = buffer.length() - 1;
    std::string temp = buffer.substr(0,a);
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
 }

void	search_command(std::vector<ClientInfo> clients, ClientInfo &ite, Server &server, std::vector <Channel> &channels)
{
	std::vector<std::string>::iterator k = ite.commands.begin();
	std::string error;
	if(k != ite.commands.end())
	{
		if(*k == "JOIN" && ite.isregister == true)
			JOIN(clients, ite, server, channels);
		else if (*k == "PING" )
			PING(clients, ite, server);
		else if(*k == "PASS")
			PASS(ite,server);
		else if(*k == "PART" && ite.isregister == true)
			PART(clients, ite, server, channels);
		else if(*k == "PRIVMSG" && ite.isregister == true)
			PRIVMSG(clients, ite, channels);
		else if(*k == "NOTICE" && ite.isregister == true)
			NOTICE(clients, ite, channels);
		else if(*k == "USER" && ite.isregister == true)
			USER(clients, ite, server, channels);
		else if (*k == "TOPIC" && ite.isregister == true)
			TOPIC(clients, ite, server, channels);
		else if(*k == "KICK" && ite.isregister == true)
			KICK(clients, ite, server, channels);
		else if(*k == "CAP")
			CAP(clients, ite, server);
		else if(*k == "MODE" && ite.isregister == true)
			MODE(clients, ite, server, channels);
		else if(*k == "QUIT")
			QUIT(clients, ite, server, channels);
		else if (*k == "WHO" && ite.isregister == true)
		{
			if (ite.commands.size() == 1)
			{
				error = ERR_NEEDMOREPARAMS("WHO");
				send(ite.socket_fd, error.c_str() , error.size(), 0);
			}
			else
				WHO(clients,ite, server, channels);
		}
		else if (*k == "NICK" && ite.isregister == true)
		{
			if (ite.commands.size() == 1)
			{
				error = ERR_NONICKNAMEGIVEN();
				send(ite.socket_fd, error.c_str() , error.size(), 0);
			}
			else
				NICK(clients, ite, server, channels);
		}
		for (std::vector<std::string>::iterator it = ite.commands.begin(); it != ite.commands.end(); it++) {
    	        it->clear();
		}
    	ite.commands.erase(std::remove(ite.commands.begin(), ite.commands.end(), ""), ite.commands.end());
	}
}
