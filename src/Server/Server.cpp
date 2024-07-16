/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:26:03 by pruenrua          #+#    #+#             */
/*   Updated: 2024/07/16 01:09:47 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void    Server::startServer(void)
{
    struct sockaddr_in  sStat;
    
    this->_fd   =   socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if (this->_fd == -1)
        return (perror("Socket : "));
    else
        std::cout << "Socket : Create " << this->_fd << std::endl;
    
    sStat.sin_family        =   AF_INET;
    sStat.sin_addr.s_addr   =   INADDR_ANY;
    sStat.sin_port          =   htons(6969);
    if (-1 == bind(this->_fd, (sockaddr   *)&sStat, sizeof(sStat)))
        return (perror("Bind : "));
    if (-1 == listen(this->_fd, 5))
        return (perror("Listen : "));

    // accept
    int sockLen = sizeof(sStat);
   
    int fd = accept(this->_fd, (sockaddr   *)&sStat, (socklen_t *)&sockLen);
    if (-1 == fd)
        return (perror("Accept : "));
}

void    Server::setup(char  *configFile)
{
    std::cout << "hrere" << std::flush;
    (void) configFile;
    
}
