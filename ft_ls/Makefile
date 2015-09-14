#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anowak <anowak@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/25 14:42:56 by anowak            #+#    #+#              #
#    Updated: 2015/01/07 20:41:06 by anowak           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =		ft_ls
FLAGS =		-Wall -Werror -Wextra
HEAD_DIR =	includes/
SRC =		main.c		\
			sets.c		\
			mode.c		\
			prints.c	\
			sort.c		\
			comps.c		\
			list.c		\
			printlist.c	\
			listdata.c
OBJ =		$(SRC:.c=.o)

all : $(NAME)

$(NAME) :
	@echo ""
	@echo "\033[31m/==================================\\"
	@echo "\033[31m|        \033[33mCreation of ft_ls         \033[31m|"
	@echo "\033[31m\\==================================/"
	@echo "\033[31m| \033[33m- Checking if libft.a exists     \033[31m|\033[0m"
	@[ -e "libft/libft.a" ] && echo "\033[31m|\033[32m        libft.a exists            \033[31m|\033[0m" || (echo "\033[31m|\033[31m        libft.a does'nt exist     \033[31m|\033[0m" ; make -C libft/ ; echo "\033[31m|                                  \033[31m|")
	@echo "\033[31m| \033[33m- Compilation of source files\033[31m    |\033[0m"
	@make $(OBJ)
	@gcc -c $(FLAGS) -I $(HEAD_DIR) $(SRC)
	@echo "\033[31m| \033[33m- Linking object files\033[31m           |\033[0m"
	@gcc -o $(NAME) $(FLAGS) libft/libft.a $(OBJ)
	@echo "\033[31mx============= \033[32mDONE ! \033[31m=============x\033[0m"
	@echo ""

%.o : %.c
	@printf "\033[0m         $?\033[0m\r"
	@gcc $(FLAGS) -I $(HEAD_DIR) -c -o $@ $?

wlib : fcleanlib re

clean :
	@echo "\033[34m  - Deleting ft_ls's object files\033[0m"
	@rm -f $(OBJ)

fclean : clean
	@echo "\033[34m  - Deleting ft_ls\033[0m"
	@rm -f $(NAME)

cleanlib :
	@make -C libft/ clean

fcleanlib :
	@make -C libft/ fclean

re : fclean all

.PHONY : all wlib clean cleanlib fclean fcleanlib re