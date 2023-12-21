
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
	string command;
	if (temp[0] == ' ')
	{
		cout << "space error" << endl;
		return ;
	}
	int index = temp.find(' ', 0);
	if (index != -1)
	{
		ite.command = temp.substr(0, index);
	}
	else
	{
		//cout << "You must enter the argument of the command!" << endl;
		return ;
	}
	if (!isalpha(temp[index + 1]) && !isdigit(temp[index + 1]))
	{
		//cout << "You must enter the argument of the command!" << endl;
		return ;
	}
	int indexx = temp.find(' ', index + 1);
	int flag = 0;
	string argumant1;
	if (indexx == -1)
	{
		flag = 1;
		argumant1 = temp.substr(index + 1, indexx - index);
		ite.argumant1 = argumant1;
	}
	else
	{
		argumant1 = temp.substr(index + 1, indexx - index);
		ite.argumant1 = argumant1;
	}
	if (flag == 1)
		return ;
	if (!isalpha(temp[indexx + 1]) && !isdigit(temp[indexx + 1]))
	{
		cout << "Wrong Argumant space!" << endl;
		return ;
	}
	int indexxx = temp.find(' ', indexx + 1);
	string argumant2;
	if (indexxx != -1)
	{
		cout << "Wrong 3. argumant space" << endl;
		return ;
	}
	else
	{
		argumant2 = temp.substr(indexx + 1, temp.length());
		ite.argumant2 = argumant2;
	}
}

void	search_command(std::vector<ClientInfo> clients, ClientInfo &ite)
{
	string message = " JOIN You are now in channel ";
	if (ite.command == "PASS")
		PASS(clients, ite);
		string buffer = ite.getPrefix() + " "  +  message + "\r\n";
		cout << buffer.c_str() << endl;

	    send(ite.socket_fd, buffer.c_str(), buffer.size(), 0);
}
