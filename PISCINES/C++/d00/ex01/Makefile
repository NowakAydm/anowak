#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anowak <anowak@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/25 14:42:56 by anowak            #+#    #+#              #
#    Updated: 2016/01/05 00:40:31 by AdamNowak        ###   ########.fr        #
#                                                                              #
#******************************************************************************#


NAME =		phonebook
CC =		g++
CC_FLAGS =	-Wall -Werror -Wextra

SRC =		phonebook.cpp\
			Contact.Class.cpp;

all : $(NAME)

$(NAME) :
	@echo "\033[31m/==================================\\"
	@echo "\033[31m|      \033[33mCreation of phonebook       \033[31m|"
	@echo "\033[31m\\==================================/"
	@echo "\033[31m|\033[33m  - Compilation of phonebook      \033[31m|\033[0m"
	@$(CC) $(CC_FLAGS) -o $(NAME) $(SRC)
	@echo "\033[31mx============= \033[32mDONE ! \033[31m=============x\033[0m"
	@echo ""

clean :
	@echo "\033[34m  - Deleting phonebook's object files\033[0m"

fclean : clean
	@echo "\033[34m  - Deleting phonebook\033[0m"
	@rm -f $(NAME)

re : fclean all
