#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anowak <anowak@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 13:45:00 by anowak            #+#    #+#              #
#    Updated: 2015/03/14 20:36:19 by anowak           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =		libftprintf.a
FLAGS =		-std=c99 #-Wall -Werror -Wextra
SRC =		ft_printf.c			\
			ft_printf_sets.c	\
			ft_printf_sets_wildcard.c	\
			ft_printf_scan.c	\
			ft_printf_options.c	\
			ft_printf_options_width.c	\
			ft_printf_prints.c	\
			ft_printf_prints_nbr.c	\
			ft_printf_prints_txt.c	\
			ft_putnbr.c			\
			ft_memalloc.c		\
			ft_memcpy.c			\
			ft_memset.c			\
			ft_strdup.c			\
			ft_wstrdup.c		\
			ft_strndup.c		\
			ft_strncpy.c		\
			ft_strnew.c			\
			ft_strclr.c			\
			ft_strchr.c			\
			ft_strrchr.c		\
			ft_strlen.c			\
			ft_wstrlen.c		\
			ft_wcharlen.c		\
			ft_strrev.c			\
			ft_putwchar.c		\
			ft_putwstr.c		\
			ft_toupper.c		\
			ft_tolower.c		\
			ft_btoi.c			\
			ft_ltoa_base.c		\
			ft_ultoa_base.c		\
			ft_atoi_neg.c		\
			ft_isspace.c		\
			ft_isdigit.c		\
			ft_abs.c			\
			ft_puiss.c			\
			ft_puiss10.c		\
			ft_nbrlen.c			\
			ft_lstnew.c			\
			ft_lstaddend.c		\
			ft_lstdel.c			\
			ft_lstdelone.c		\
			ft_lstdelcontent.c
OBJ =		$(SRC:.c=.o)

#cp libft/ft_memset.c libftprintf

all : $(NAME)

$(NAME) :
	@echo "\033[31m/==================================\\"
	@echo "\033[31m|     \033[33mCreation of libftprintf      \033[31m|"
	@echo "\033[31m\\==================================/"
	@echo "\033[31m|\033[33m - Compilation of source files    \033[31m|\033[0m"
	@make $(OBJ)
	@echo "\033[31m|\033[33m - Creation of libftprintf.a      \033[31m|\033[0m"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[31mx============= \033[32mDONE ! \033[31m=============x\033[0m"

%.o : %.c
	@printf "                                       \r"
	@printf "         $?\r"
	@gcc -c -I includes/ $(FLAGS) -o $@ $?

clean :
	@echo "\033[34m  - Deleting libftprintf's object files\033[0m"
	@rm -f $(OBJ)

fclean : clean
	@echo "\033[34m  - Deleting libftprintf.a\033[0m"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
