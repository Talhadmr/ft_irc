#include "server.hpp"

Server::Server(char *str)
{
    _sock = -1;
    _bin = -1;
    _lis = -1;
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    //uint16_t port;
    //std::memcpy(&port, str, sizeof(uint16_t));
    int port = atoi(str);
    if(_sock < 0)
    {
        std::cerr << "sock error\n";
            exit(1);
    }
    //_sin = new struct sockaddr_in;
    _sin.sin_family = AF_INET;
    std::cout << port << std::endl;
    _sin.sin_port = htons(port);
    _sin.sin_addr.s_addr = INADDR_ANY;

    _bin = bind(_sock, (struct sockaddr *)&_sin, sizeof(_sin));

    if(_bin)
    {
        std::cerr << "bind error\n";
            exit(1);
    }
    
    _lis = listen(_sock,5);

    if(_lis)
    {
        std::cerr << "list error\n";
            exit(1);
    }

    std::cout << "server is listening\n";   
}


void Server::serving()
{
    int acc;
    char buff[1024];
    int rec;
    socklen_t sock_len = sizeof(_sin);
    
    while(1)
    {
        acc = accept(_sock, (struct sockaddr *)&_sin, &sock_len);
        if(acc < 0)
        {
            std::cerr << "accept error\n";
                exit(1);
        }
    
        while(1)
        {
            std::cout << "client message: ";
            rec = recv(acc, buff, sizeof(buff), 0);
            if(rec == -1)
            {
                std::cerr << "recv error\n";
                    exit(1);
            }
            else
                std::cout << buff << std::endl;
            memset(buff, 0, sizeof(buff));
        }
    }
}
