#include "server.hpp"
#include "Channel.hpp"
#include "Client.hpp"

ClientInfo::ClientInfo(int fd, sockaddr_in addr) : socket_fd(fd), address(addr)
{
    this->isregister = false;
}

Server::Server(char *str) {
    char host_name[1024];
    this->registered = false;
    int herror = gethostname(host_name, 1024);
	if (herror == -1)
    {
        std::cout << "Host Error" << std::endl;
		exit(1);
    }
	this->hostname = host_name;
    _socket = -1;
    _bin = -1;
    _lis = -1;
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    _port = atoi(str);
    if(!(_port > 0 && _port < 65537))
    {
        std::cerr << "port has to be betwen 0 and 65537\n";
        exit(1);
    }

    if (_socket < 0)
    {
        std::cerr << "sock error\n";
        exit(1);
    }
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(_port);
    _sin.sin_addr.s_addr = INADDR_ANY;

    int reuse = 1;

    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
        exit(1);
    }
    _bin = bind(_socket, (struct sockaddr *)&_sin, sizeof(_sin));

    if (_bin)
    {
        std::cerr << "bind error\n";
        exit(1);
    }

    _lis = listen(_socket, 5);

    if (_lis)
    {
        std::cerr << "list error\n";
        exit(1);
    }

    std::cout << "server is listening\n";
}

void Server::serving()
{
    fd_set rfds, tmp_rfds;
    int max_sd, new_socket;
    struct sockaddr_in client;
    socklen_t addr_len = sizeof(client);
    std::vector<ClientInfo> clients;
    int flag = 0;
    int w_flag = 0;

    FD_ZERO(&rfds);
    FD_SET(_socket, &rfds);
    max_sd = _socket;

    std::cout << "Server is waiting for connections on port " << _port << std::endl;

    while (true)
    {
        tmp_rfds = rfds;

        if (select(max_sd + 1, &tmp_rfds, NULL, NULL, NULL) == -1)
        {
            std::cerr << "select error\n";
            break;
        }

        if (FD_ISSET(_socket, &tmp_rfds))
        {
            if ((new_socket = accept(_socket, (struct sockaddr *)&client, &addr_len)) == -1)
            {
                std::cerr << "accept error\n";
                break;
            }
            else
            {
                flag = 1;
                std::cout << "New connection from " << inet_ntoa(client.sin_addr) << " on socket " << new_socket << std::endl;
                clients.push_back(ClientInfo(new_socket, client));
                FD_SET(new_socket, &rfds);

                if (new_socket > max_sd)
                    max_sd = new_socket;
            }
        }

        for (std::vector<ClientInfo>::iterator it = clients.begin(); it != clients.end();)
        {
            int client_socket = it->socket_fd;
            if (FD_ISSET(client_socket, &tmp_rfds))
            {
                char buffer[1024];
                int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

                if (bytes_received <= 0)
                {
                    std::cout << "Client on socket " << client_socket << " disconnected." << std::endl;
                    close(client_socket);
                    FD_CLR(client_socket, &rfds);
                    it = clients.erase(it);
                }
                else
                {
                    buffer[bytes_received] = '\0';
                    if(flag == 1 && buffer[0])
                    {
                        if(buffer[strlen(buffer) -2] == '\r')
                         {
                            command_info(buffer, clients, *it);
                            PASS(*it, *this);
                         }
                        else
                        {
                            nc_control(buffer, clients, *it);
                        }
                    }
                    else if(buffer[0])
                    {
                        command_message(buffer, clients, *it);
                        search_command(clients, *it, *this, this->channels);
                    }
                    flag = 0;
                    ++it;
                }
            }
            else
                ++it;
        }
    }
    close(_socket);
}
