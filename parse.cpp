
#include "server.hpp"
#include "RPL.hpp"

void	command_info(string buffer,std::vector<ClientInfo> clients, ClientInfo ite)
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

	 cout << ite.get_password();
	 i = 0;
	 index = k->find(' ',i);
	 ite.set_nickname(k->substr(index + 1, k++->length() - 2));
	 cout << ite.get_nickname();
	 i = 0;
	 index = k->find(' ',i);
	 indexx = k->find(' ',index + 1);
	 ite.set_username(k->substr(index + 1, indexx - index));
	 cout << ite.get_username() << endl;
}

void	command_message(string buffer,std::vector<ClientInfo> clients,ClientInfo ite)
{
	int a = buffer.length() - 2;
	string temp = buffer.substr(0,a);
	if (temp[0] == ' ')
	{
		cout << "space error" << endl;
		return ;
	}
	int index = temp.find(' ', 0);
	if (index != -1)
	{
		string command = temp.substr(0, index);
		cout << "command: " << command << endl;
	}
	else
	{
		cout << "You must enter the argument of the command!" << endl;
		return ;
	}
	cout << temp << endl;
	if (!isalpha(temp[index + 1]) && !isdigit(temp[index + 1]))
	{
		cout << "You must enter the argument of the command!" << endl;
		return ;
	}
	int indexx = temp.find(' ', index + 1);
	int flag = 0;
	if (indexx != std::string::npos)
		flag = 1;
	string argumant1 = temp.substr(index + 1, indexx - index);
	if (flag == 0)
	{
		cout << "1 Arguman:" << argumant1 << endl;
		return ;
	}
	if (!isalpha(temp[indexx + 1]) && !isdigit(temp[indexx + 1]))
	{
		cout << "Wrong Argumant space!" << endl;
		return ;
	}
	int indexxx = temp.find(' ', indexx + 1);
	if (indexxx != -1)
	{
		cout << "Wrong 3. argumant space" << endl;
		return ;
	}
	string argumant2 = temp.substr(indexx + 1, temp.length());
	cout << "1 Arguman:" << argumant1 << endl;
	cout << "2 Arguman:" << argumant2 << endl;
	cout << temp << endl;
	ite.
	PASS(clients, ite);
}
