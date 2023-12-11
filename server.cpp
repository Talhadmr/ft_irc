#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    // Socket oluşturma
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Socket oluşturulamadı" << std::endl;
        return -1;
    }

    // Adres bilgilerini ayarlama
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1235);  // Port numarası
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Socket'i adrese bağlama (bind)
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Bind hatası" << std::endl;
        close(serverSocket);
        return -1;
    }

    // Bağlantıları dinleme (listen)
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Listen hatası" << std::endl;
        close(serverSocket);
        return -1;
    }

        /* code */
    
    
        std::cout << "Sunucu başlatıldı. Bağlantı bekleniyor..." << std::endl;

    while (1)
    { 
        // Bağlantı kabul etme (accept)
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
            std::cerr << "Bağlantı kabul hatası" << std::endl;
            close(serverSocket);
            return -1;
        }

        std::cout << "İstemci bağlandı." << std::endl;

        // İstemciden veri alıp gönderme
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        if (recv(clientSocket, buffer, sizeof(buffer), 0) == -1) {
            std::cerr << "Veri alınamadı" << std::endl;
        } else {
            std::cout << "İstemciden gelen mesaj: " << buffer << std::endl;

            // İstemciye cevap gönderme
            const char* response = "Merhaba, istemciden gelen mesaj alındı!";
            send(clientSocket, response, strlen(response), 0);
        }
        close(clientSocket);
    }
    close(serverSocket);

    // Soketleri kapatma

    return 0;
}
