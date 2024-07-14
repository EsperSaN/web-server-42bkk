/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:23:11 by pruenrua          #+#    #+#             */
/*   Updated: 2024/07/15 00:12:31 by pruenrua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class   Server {

    private :
        std::string _name;
    public :
        void    setup(char  *configFile);
};
