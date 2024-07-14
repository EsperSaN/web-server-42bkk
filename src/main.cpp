#include <iostream>
#include "Server.hpp"

int main(int ac, char **av)
{
    Server  server;

    if (ac != 2)
        return (1);
    server.setup(av[1]);
}