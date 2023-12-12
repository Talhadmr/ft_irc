#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main(int ac, char **av) {
    // Socket oluşturma
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Socket oluşturulamadı" << std::endl;
        return -1;
    }

    // Adres bilgilerini ayarlama
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1235);  // Sunucunun port numarası
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Sunucunun IP adresi

    // Sunucuya bağlanma (connect)
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Bağlantı hatası" << std::endl;
        close(clientSocket);
        return -1;
    }
    
    std::cout << "Sunucuya bağlandı." << std::endl;

    // Sunucuya mesaj gönderme
    const char* message =strdup(av[1]);
    send(clientSocket, message, strlen(message), 0);

    // Sunucudan cevap alma
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    if (recv(clientSocket, buffer, sizeof(buffer), 0) == -1) {
        std::cerr << "Cevap alınamadı" << std::endl;
    } else {
        std::cout << "Sunucudan gelen cevap: " << buffer << std::endl;
    }

    // Soketi kapatma
    close(clientSocket);

    return 0;
}
