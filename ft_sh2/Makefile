#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anowak <anowak@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/25 14:42:56 by anowak            #+#    #+#              #
#    Updated: 2015/10/26 18:37:31 by anowak           ###   ########.fr        #
#                                                                              #
#******************************************************************************#


NAME =		ft_minishell2
CC =		clang
CC_FLAGS =	-O3 -Wall -Werror -Wextra

HEAD_DIR =	includes/

SRC_DIR =	sources
SRC =		ft_minishell2.c	\
			execute.c		\
			signals.c		\
			arguments.c		\
			quotes.c		\
			builtin.c		\
			builtin_cd.c	\
			builtin_env.c	\
			builtin_exit.c	\
			builtin_setenv.c\
			builtin_unsetenv.c\
			command_line.c	\
			term.c

SRCS =		$(addprefix $(SRC_DIR)/, $(not_dir $(SRC))

OBJ_DIR =	objects
OBJ =		$(SRC:.c=.o)

OBJS =		$(addprefix $(OBJ_DIR)/, $(OBJ))


all : $(NAME)

$(NAME) :
	@echo "\033[31m/==================================\\"
	@echo "\033[31m|        \033[33mCreation of ft_sh2        \033[31m|"
	@echo "\033[31m\\==================================/"
	@echo "\033[31m|\033[33m  - Checking if libft.a exists    \033[31m|\033[0m"
	@[ -e "libft/libft.a" ] && echo "\033[32m         libft.a exists\033[0m" || (echo "\033[31m         libft.a does'nt exist\033[0m" ; make -C libft/ )
	@make $(OBJ_DIR)
	@echo "\033[31m|\033[33m  - Compilation of source files   \033[31m|\033[0m"
	@make $(OBJ)
	@echo "\033[31m|\033[33m  - Compilation of ft_minishell2  \033[31m|\033[0m"
	@$(CC) $(CC_FLAGS) -lncurses -o $(NAME) -I $(HEAD_DIR) libft/libft.a $(OBJS)
	@echo "\033[31mx============= \033[32mDONE ! \033[31m=============x\033[0m"
	@echo ""
	@echo ""

%.o : $(SRC_DIR)/%.c
	@printf "                                       \r"
	@printf "         $@\r"
	@$(CC) -c $(CC_FLAGS) -I $(HEAD_DIR) -o $(OBJ_DIR)/$@ $?

wlib : fcleanlib re

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $@

clean :
	@echo "\033[34m  - Deleting ft_sh1's object files\033[0m"
	@rm -rf $(OBJ_DIR)

fclean : clean
	@echo "\033[34m  - Deleting ft_minishell1\033[0m"
	@rm -f $(NAME)

cleanlib :
	@make -C libft/ clean

fcleanlib :
	@make -C libft/ fclean

re : fclean all
