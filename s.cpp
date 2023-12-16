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

    // İhtiyaç duyulan diğer bilgileri ekleyebilirsiniz.

    ClientInfo(int fd, sockaddr_in addr) : socket_fd(fd), address(addr) {}
};

std::vector<ClientInfo> clients;

int main() {
    const int PORT = 124;
    const int MAX_CLIENTS = 5;

    fd_set master_set, working_set;
    int listener, new_socket, max_sd;
    struct sockaddr_in server, client;
    socklen_t addr_len = sizeof(client);

    // Socket oluştur
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 1;
    }

    // Server adresini ayarla
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Socket'i bind et
    if (bind(listener, (struct sockaddr*)&server, sizeof(server)) == -1) {
        perror("bind");
        close(listener);
        return 1;
    }

    // Socket'i dinle
    if (listen(listener, MAX_CLIENTS) == -1) {
        perror("listen");
        close(listener);
        return 1;
    }

    FD_ZERO(&master_set);
    FD_SET(listener, &master_set);
    max_sd = listener;

    std::cout << "Server is waiting for connections on port " << PORT << std::endl;

    while (true) {
        working_set = master_set;

        // Socket'ları kontrol et
        if (select(max_sd + 1, &working_set, NULL, NULL, NULL) == -1) {
            perror("select");
            break;
        }

        // Yeni bağlantı kontrolü
        if (FD_ISSET(listener, &working_set)) {
            if ((new_socket = accept(listener, (struct sockaddr*)&client, &addr_len)) == -1) {
                perror("accept");
            } else {
                std::cout << "New connection from " << inet_ntoa(client.sin_addr) << " on socket " << new_socket
                          << std::endl;

                // Yeni client bilgilerini ekleyin
                clients.push_back(ClientInfo(new_socket, client));

                FD_SET(new_socket, &master_set);
                if (new_socket > max_sd) {
                    max_sd = new_socket;
                }
            }
        }

        // Mevcut bağlantılardan gelen verileri kontrol et
        for (auto it = clients.begin(); it != clients.end(); ) {
            int client_socket = it->socket_fd;
            if (FD_ISSET(client_socket, &working_set)) {
                char buffer[1024];
                sleep(1);
                int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
                if (bytes_received <= 0) {
                    std::cout << "Client on socket " << client_socket << " disconnected." << std::endl;
                    close(client_socket);
                    it = clients.erase(it);
                    FD_CLR(client_socket, &master_set);
                } else {
                    buffer[bytes_received] = '\0';
                    std::cout << "Received from client " << client_socket << ": " << buffer << std::endl;
                    // Burada gelen veriye karşı bir işlem yapabilirsiniz.
                    // Örneğin, başka bir client'a gönderebilirsiniz.
                }
            } else {
                ++it;
            }
        }
    }

    // Server'ı kapat
    close(listener);

    return 0;
}
