#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

class ClientInfo {
public:
    int socket_fd;
    sockaddr_in address;


    ClientInfo(int fd, sockaddr_in addr) : socket_fd(fd), address(addr) {}
};

int main() {
    const int PORT = 6667;
    const int MAX_CLIENTS = 5;

    fd_set master_set, working_set;
    int listener, new_socket, max_sd;
    struct sockaddr_in server, client;
    socklen_t addr_len = sizeof(client);
    std::vector<ClientInfo> clients;

    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(listener, (struct sockaddr*)&server, sizeof(server)) == -1) {
        perror("bind");
        close(listener);
        return 1;
    }

    if (listen(listener, MAX_CLIENTS) == -1) {
        perror("listen");
        close(listener);
        return 1;
    }

    FD_ZERO(&master_set);
    FD_SET(listener, &master_set);
    max_sd = listener;
    printf("%d\n", listener);
    std::cout << "Server is waiting for connections on port " << PORT << std::endl;

    while (true) {
        working_set = master_set;

        if (select(max_sd + 1, &working_set, NULL, NULL, NULL) == -1) {
            perror("select");
            break;
        }

        if (FD_ISSET(listener, &working_set)) {
            if ((new_socket = accept(listener, (struct sockaddr*)&client, &addr_len)) == -1) {
                perror("accept");
            } else {
                std::cout << "New connection from " << inet_ntoa(client.sin_addr) << " on socket " << new_socket << std::endl;

                clients.push_back(ClientInfo(new_socket, client));

                FD_SET(new_socket, &master_set);
                if (new_socket > max_sd) {
                    max_sd = new_socket;
                }
            }
        }

        for (std::vector<ClientInfo>::iterator it = clients.begin(); it != clients.end(); ++it) {
            int client_socket = it->socket_fd;
            if (FD_ISSET(client_socket, &working_set)) {
                char buffer[1024];
                int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
                if (bytes_received <= 0) {
                    std::cout << "Client on socket " << client_socket << " disconnected." << std::endl;
                    close(client_socket);
                    FD_CLR(client_socket, &master_set);
                    it = clients.erase(it);
                    if (it == clients.end()) {
                    }
                } else {
                    buffer[bytes_received] = '\0';
                    std::cout << "Received from client " << client_socket << ": " << buffer << std::endl;
                }
            }
        }
    }

    close(listener);

    return 0;
}
