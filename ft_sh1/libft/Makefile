#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anowak <anowak@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 13:45:00 by anowak            #+#    #+#              #
#    Updated: 2015/06/11 19:04:55 by anowak           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =		libft.a
FLAGS =		-Wall -Wextra -Werror -O3

SRC_DIR =	sources
SRC =		ft_memset.c				\
			ft_abs.c				\
			ft_bzero.c				\
			ft_memcpy.c				\
			ft_memccpy.c			\
			ft_memmove.c			\
			ft_memchr.c				\
			ft_memcmp.c				\
			ft_strlen.c				\
			ft_strdup.c				\
			ft_strcpy.c				\
			ft_strncpy.c			\
			ft_strcat.c				\
			ft_strncat.c			\
			ft_strlcat.c			\
			ft_strchr.c				\
			ft_strrchr.c			\
			ft_strstr.c				\
			ft_strnstr.c			\
			ft_strcmp.c				\
			ft_strncmp.c			\
			ft_atoi.c				\
			ft_atod.c				\
			ft_isalpha.c			\
			ft_isdigit.c			\
			ft_isalnum.c			\
			ft_isascii.c			\
			ft_isprint.c			\
			ft_toupper.c			\
			ft_tolower.c			\
			ft_memalloc.c			\
			ft_memdel.c				\
			ft_strnew.c				\
			ft_strdel.c				\
			ft_strclr.c				\
			ft_striter.c			\
			ft_striteri.c			\
			ft_strmap.c				\
			ft_strmapi.c			\
			ft_strequ.c				\
			ft_strnequ.c			\
			ft_strsub.c				\
			ft_strjoin.c			\
			ft_strtrim.c			\
			ft_strsplit.c			\
			ft_itoa.c				\
			ft_ltoa_base.c			\
			ft_putchar.c			\
			ft_putstr.c				\
			ft_putendl.c			\
			ft_putnbr.c				\
			ft_putnbrendl.c			\
			ft_putchar_fd.c			\
			ft_putstr_fd.c			\
			ft_putendl_fd.c			\
			ft_putnbr_fd.c			\
			ft_lstnew.c				\
			ft_lstdelone.c			\
			ft_lstdel.c				\
			ft_lstadd.c				\
			ft_lstiter.c			\
			ft_lstmap.c				\
			ft_lstlen.c				\
			ft_strlcpy.c			\
			ft_strndup.c			\
			ft_strcdup.c			\
			ft_count_words.c		\
			ft_nbrlen.c				\
			ft_strrev.c				\
			ft_isspace.c			\
			ft_puiss10.c			\
			ft_lstaddend.c			\
			ft_lstsplit.c			\
			ft_putlst_str.c			\
			ft_lstdelcontent.c		\
			ft_lsttostr.c			\
			ft_lsttotab.c			\
			ft_btree_new.c			\
			ft_btree_prefix.c		\
			ft_btree_infix.c		\
			ft_btree_rev_infix.c	\
			ft_btree_suffix.c		\
			ft_btree_insert.c		\
			ft_btree_free.c			\
			ft_tablen.c				\
			ft_tabfree.c			\
			ft_isquote.c			\
			ft_tabdup.c				\
			ft_tabadd.c				\
			get_next_line.c

OBJ_DIR =	objects
OBJ =		$(SRC:.c=.o)

all : $(NAME)

$(NAME) :
	@echo "\033[31m/==================================\\"
	@echo "\033[31m|        \033[33mCreation of libft         \033[31m|"
	@echo "\033[31m\\==================================/"
	@echo "\033[31m|\033[33m - Compilation of source files    \033[31m|\033[0m"
	@make $(OBJ)
	@echo "\033[31m|\033[33m - Creation of libft.a            \033[31m|\033[0m"
	@ar rc $(NAME) $(addprefix $(OBJ_DIR)/, $(OBJ))
	@ranlib $(NAME)
	@echo "\033[31mx============= \033[32mDONE ! \033[31m=============x\033[0m"
	@echo ""

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $@

%.o : $(SRC_DIR)/%.c
	@printf "                                       \r"
	@printf "         $@\r"
	@gcc -c -I includes/ $(FLAGS) -o $(OBJ_DIR)/$@ $?

clean :
	@echo "\033[34m  - Deleting libft's object files\033[0m"
	@rm -rf $(OBJ_DIR)

fclean : clean
	@echo "\033[34m  - Deleting libft.a\033[0m"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
