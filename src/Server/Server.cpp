/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:26:03 by pruenrua          #+#    #+#             */
/*   Updated: 2024/07/17 04:08:51 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*j_str;
	char	*str_joined;

	if (!s1 || !s2)
		return (0);
	j_str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!j_str)
		return (0);
	str_joined = j_str;
	while (*s1)
	{
		*j_str = *s1;
		s1++;
		j_str++;
	}
	while (*s2)
	{
		*j_str = *s2;
		s2++;
		j_str++;
	}
	*j_str = '\0';
	return (str_joined);
}
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
    sStat.sin_port          =   htons(7000);

	if (-1 == bind(this->_fd, (sockaddr   *)&sStat, sizeof(sStat)))
		return (perror("Bind : "));
	if (-1 == listen(this->_fd, 5))
		return (perror("Listen : "));
	int sockLen = sizeof(sStat);

	std::cerr << "this fd = " << this->_fd << std::endl;

	// accept
	//        If no pending connections are present on the queue, and the socket is not marked as nonblocking, accept() blocks the caller until a connection is  present.   If  the
    //    socket is marked nonblocking and no pending connections are present on the queue, accept() fails with the error EAGAIN or EWOULDBLOCK.

    //    In  order  to be notified of incoming connections on a socket, you can use select(2), poll(2), or epoll(7).  A readable event will be delivered when a new connection
    //    is attempted and you may then call accept() to get a socket for that connection.  Alternatively, you can set the socket to deliver SIGIO when activity  occurs  on  a
    //    socket; see socket(7) for details.
	
	int	epoll_fd = epoll_create1(EPOLL_CLOEXEC);
	if (-1 == epoll_fd)
		return (perror("Epoll : "));
	struct epoll_event	ep_event, ep_array[10];

	ep_event.events = EPOLLIN;
	ep_event.data.fd = this->_fd;
	char buffer[10000];
	
	if (-1 == epoll_ctl(epoll_fd, EPOLL_CTL_ADD,	this->_fd, &ep_event))
		return (perror("Epoll CTL : "));
	int Cilent_fd = 0;
	while (1)
	{
		int	ev_num = epoll_wait(epoll_fd, ep_array, 10, -1);
		if (ev_num == -1)
			return (perror("epoll Wait : "));
		for (int i = 0; i < ev_num; ++i)
		{
			//std::cerr << i << " is " << ep_array[i].data.fd << " " << ev_num << std::endl;
			if (ep_array[i].data.fd == this->_fd)
			{
				std::cerr << "here" << std::endl;
				Cilent_fd = accept(this->_fd, (sockaddr   *)&sStat, (socklen_t *)&sockLen);
		    	if (-1 == Cilent_fd)
       				 return (perror("Accept : "));
				ep_array[i].events = EPOLLIN | EPOLLOUT;
				ep_array[i].data.fd = Cilent_fd;
				if (-1 == epoll_ctl(epoll_fd, EPOLL_CTL_ADD,	Cilent_fd,	&ep_array[i]))
					return (perror("epoll ctl : "));
				int n = read(Cilent_fd, buffer, 10000);
				buffer[n] = '\0';
				int ret = open("./testMat/index.html", O_RDONLY);
				n = read(ret, buffer, 10000);
				buffer[n] = '\0';
				char *rett = ft_strjoin("\r\nHTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n", buffer);
				rett[ft_strlen(rett)] = '\0';
				send(Cilent_fd, rett, ft_strlen(rett), 0);
				close(Cilent_fd);
				std::cerr << "accept the Client!!!! : " << Cilent_fd << "\n" << buffer << std::endl;
			}
	}
}
}

void    Server::setup(char  *configFile)
{
    std::cout << "hrere" << std::flush;
    (void) configFile;
    
}
