#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anowak <anowak@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 13:45:00 by anowak            #+#    #+#              #
#    Updated: 2014/11/15 18:02:52 by anowak           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =		libft.a
FLAGS =		-Wall -Wextra -Werror
SRC =		ft_memset.c		\
			ft_bzero.c		\
			ft_memcpy.c		\
			ft_memccpy.c	\
			ft_memmove.c	\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_strlen.c		\
			ft_strdup.c		\
			ft_strcpy.c		\
			ft_strncpy.c	\
			ft_strcat.c		\
			ft_strncat.c	\
			ft_strlcat.c	\
			ft_strchr.c		\
			ft_strrchr.c	\
			ft_strstr.c		\
			ft_strnstr.c	\
			ft_strcmp.c		\
			ft_strncmp.c	\
			ft_atoi.c		\
			ft_isalpha.c	\
			ft_isdigit.c	\
			ft_isalnum.c	\
			ft_isascii.c	\
			ft_isprint.c	\
			ft_toupper.c	\
			ft_tolower.c	\
			ft_memalloc.c	\
			ft_memdel.c		\
			ft_strnew.c		\
			ft_strdel.c		\
			ft_strclr.c		\
			ft_striter.c	\
			ft_striteri.c	\
			ft_strmap.c		\
			ft_strmapi.c	\
			ft_strequ.c		\
			ft_strnequ.c	\
			ft_strsub.c		\
			ft_strjoin.c	\
			ft_strtrim.c	\
			ft_strsplit.c	\
			ft_itoa.c		\
			ft_putchar.c	\
			ft_putstr.c		\
			ft_putendl.c	\
			ft_putnbr.c		\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c	\
			ft_lstnew.c		\
			ft_lstdelone.c	\
			ft_lstdel.c		\
			ft_lstadd.c		\
			ft_lstiter.c	\
			ft_lstmap.c		\
			ft_strlcpy.c	\
			ft_strndup.c	\
			ft_count_words.c\
			ft_nbrlen.c		\
			ft_strrev.c		\
			ft_isspace.c	\
			ft_puiss10.c	\
			ft_lstaddend.c	\
			ft_lstsplit.c	\
			ft_putlst_str.c
OBJ =		$(SRC:.c=.o)

all : $(NAME)

$(NAME) :
	@echo "Compilation des fichiers .o"
	@gcc -c $(FLAGS) $(SRC)
	@echo "Creation de libft.a"
	@ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean :
	@echo "Suppression des fichiers .o"
	@rm -f $(OBJ)

fclean : clean
	@echo "Suppression de libft.a"
	@rm -f libft.a

re : fclean all

test :
	@echo "Compilation du moulinator ..."
	@gcc -o Test-Moulinator mainmoulinator.c
	@gcc -fPIC -Wall -Werror -Wextra -shared -o libft.so $(OBJ)
	@./Test-Moulinator
	@rm libft.so