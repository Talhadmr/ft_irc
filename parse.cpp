
#include "server.hpp"

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
	//while (k != name.end())
	//{
	//	std::cout << *k++;
	//}
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

void	command_message(string buffer,std::vector<ClientInfo> clients)
{
	int a = buffer.length() - 2;
	string temp = buffer.substr(0,a);

}
