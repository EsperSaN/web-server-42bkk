/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:23:11 by pruenrua          #+#    #+#             */
/*   Updated: 2024/07/16 01:10:13 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/epoll.h>

class   Server {

    private :
        std::string _host;
        int         _fd;
    public :
        void    setup(char  *configFile);
        void    startServer(void);
};

#endif
