#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

int main()
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
    sin.sin_addr.s_addr = INADDR_ANY;

    int bin;

    bin = bind(sock, (struct sockaddr *)&sin, sizeof(sin));
    if(bin < 0)
    {
        std::cerr << "bind error\n";
        return 1;
    }
    int lis;

    lis = listen(sock, 5);
    if(lis < 0)
    {
        std::cerr << "listen error\n";
        return 1;
    }
    std::cout << "server is listening\n";

    while(1)
    {
        int acc;
        socklen_t sock_len = sizeof(sin);
        acc = accept(sock,(struct sockaddr *)&sin, &sock_len);
        if(acc < 0)
        {
            std::cerr << "accept error\n";
            return 1;
        }
        char buff[1024];

        if(recv(acc, buff, sizeof(buff), 0) != -1)
            std::cout << "client message: "<< buff <<std::endl; 
    }
}