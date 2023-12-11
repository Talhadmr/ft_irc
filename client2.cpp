#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>

int main(int ac, char **av)
{
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        std::cerr << "socket error\n";
        return 1;
    }
    struct sockaddr_in sin;
    sin.sin_family =AF_INET; 
    sin.sin_port = htons(11234);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&sin, sizeof(sin));

    std::cout << "Sunucuya bağlandı." << std::endl;
    const char* message =strdup(av[1]);
    send(sock, message, strlen(message), 0);

}