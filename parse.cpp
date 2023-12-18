
#include "server.hpp"

void	command_parse(char* buffer,  std::vector<ClientInfo> clients)
{
	//int i = 0;
	//int len = buffer.length();
	//buffer = buffer.substr(0, len - 2);
	//(void)clients;
	char *a = std::strtok(buffer, " ");
	cout << a << endl;
}

