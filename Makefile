# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pruenrua <pruenrua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/14 22:54:02 by pruenrua          #+#    #+#              #
#    Updated: 2024/07/15 00:17:43 by pruenrua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP

OBJ_DIR = obj

SRC_DIR	= ./src

INCLUDE_DIR = $(SRC_DIR)/include
CLIENT_DIR = $(SRC_DIR)/Client/

CLIENT_FILE = Client.cpp

CLIENT_SRC = $(addprefix $(CLIENT_DIR), $(CLIENT_FILE))

CONFIG_DIR	= $(SRC_DIR)/Config/

CONFIG_FILE = Config.cpp

CONFIG_SRC = $(addprefix $(CONFIG_DIR), $(CONFIG_FILE))

SERVER_DIR	= $(SRC_DIR)/Server/

SERVER_FILE = Server.cpp

SERVER_SRC = $(addprefix $(SERVER_DIR), $(SERVER_FILE))

SRC_FILE =  $(CONFIG_SRC) $(SERVER_SRC) $(CLIENT_SRC) $(SRC_DIR)/main.cpp 

OBJ = $(SRC_FILE:%cpp=$(OBJ_DIR)/%o)

$(OBJ_DIR)/%.o: %.cpp 
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

HPP = $(CLIENT_DIR)Client.hpp $(CONFIG_DIR)Config.hpp $(SERVER_DIR)Server.hpp 

DEPS = $(OBJ:%o=%d)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ) $(DEPS) $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

-include $(DEPS)

.PHONY : all clean fclean re 