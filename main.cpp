#include "server.hpp"

int main(int ac, char **av)
{
    if(ac ==2)
    {
        Server  ser(av[1]);
        ser.serving();
    }
    else    
    {
        std::cerr << "argument count error\n";
        exit(1);
    }
}