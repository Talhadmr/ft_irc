#include "server.hpp"


ClientInfo::ClientInfo(int fd, sockaddr_in addr) : socket_fd(fd), address(addr) {}

Server::Server(char *str)
{
    _socket = -1;
    _bin = -1;
    _lis = -1;
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    //uint16_t port;
    //std::memcpy(&port, str, sizeof(uint16_t));
    _port = atoi(str);
    if(_socket < 0)
    {
        std::cerr << "sock error\n";
            exit(1);
    }
    //_sin = new struct sockaddr_in;
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(_port);
    _sin.sin_addr.s_addr = INADDR_ANY;

    _bin = bind(_socket, (struct sockaddr *)&_sin, sizeof(_sin));

    if(_bin)
    {
        std::cerr << "bind error\n";
            exit(1);
    }
    
    _lis = listen(_socket,5);

    if(_lis)
    {
        std::cerr << "list error\n";
            exit(1);
    }

    std::cout << "server is listening\n";   
}


void Server::serving() {
    fd_set rfds, tmp_rfds;
    int max_sd, new_socket;
    struct sockaddr_in client;
    socklen_t addr_len = sizeof(client);
    std::vector<ClientInfo> clients;

    FD_ZERO(&rfds);
    FD_SET(_socket, &rfds);
    max_sd = _socket;

    std::cout << "Server is waiting for connections on port " << _port << std::endl;

    while (true) {
        tmp_rfds = rfds;

        if (select(max_sd + 1, &rfds, NULL, NULL, NULL) == -1)
        {
            std::cerr << "select error\n";
            break;
        }

        if (FD_ISSET(_socket, &tmp_rfds)) 
        {
            if ((new_socket = accept(_socket, (struct sockaddr *)&client, &addr_len)) == -1) {
                std::cerr << "accept error\n";
                break;
            } else {
                std::cout << "New connection from " << inet_ntoa(client.sin_addr) << " on socket " << new_socket << std::endl;
                clients.push_back(ClientInfo(new_socket, client));

                FD_SET(new_socket, &rfds);
                if (new_socket > max_sd)
                    max_sd = new_socket;
            }
        }

        for (std::vector<ClientInfo>::iterator it = clients.begin(); it != clients.end(); ++it) {
            int client_socket = it->socket_fd;
            if (FD_ISSET(client_socket, &tmp_rfds)) {
                char buffer[1024];
                int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
                if (bytes_received <= 0) {
                    std::cout << "Client on socket " << client_socket << " disconnected." << std::endl;
                    close(client_socket);
                    FD_CLR(client_socket, &rfds);
                    if (it == clients.end())
                        break;
                } else {
                    buffer[bytes_received] = '\0';
                    std::cout << "Received from client " << client_socket << ": " << buffer << std::endl;
                }
            }
        }
    }
    close(_socket);
}

