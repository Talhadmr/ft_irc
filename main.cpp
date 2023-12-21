#include "server.hpp"

int main(int argc, char *argv[]) {
    if (argc != 3)
    {
        std::cerr << "usage: ./server port password\n";
        return 1;
    }

    Server server(argv[1]);
    server._pass = static_cast<std::string>(argv[2]);
    if(server._pass.empty())
    {
        std::cerr << "password error\n";
        exit(1);
    }
    server.serving();

    return 0;
}