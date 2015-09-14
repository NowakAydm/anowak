#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anowak <anowak@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 13:45:00 by anowak            #+#    #+#              #
#    Updated: 2015/05/15 17:22:38 by anowak           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =		libfts.a
CC_ASM =	/nfs/zfs-student-4/users/2014/anowak/Applications/nasm
#CC_ASM =	nasm
FLAGS =		-f macho64
SRC =		ft_bzero.s		\
			ft_isalnum.s	\
			ft_isalpha.s	\
			ft_isascii.s	\
			ft_isdigit.s	\
			ft_isprint.s	\
			ft_tolower.s	\
			ft_toupper.s	\
			ft_puts.s		\
			ft_strlen.s		\
			ft_memset.s		\
			ft_memcpy.s		\
			ft_strdup.s		\
			ft_strcat.s		\
			ft_cat.s		\
			ft_islower.s	\
			ft_isupper.s	\
			ft_strncat.s	\
			ft_strnew.s		\
			ft_putstr.s

OBJ =		$(SRC:.s=.o)


all : $(NAME)

$(NAME) :
	@echo "\033[31m/==================================\\"
	@echo "\033[31m|     \033[33mCreation of libftASM         \033[31m|"
	@echo "\033[31m\\==================================/"
	@echo "\033[31m|\033[33m - Compilation of source files    \033[31m|\033[0m"
	@make $(OBJ)
	@echo "\033[31m|\033[33m - Creation of libfts.a         \033[31m|\033[0m"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[31mx============= \033[32mDONE ! \033[31m=============x\033[0m"

%.o : %.s
	@printf "                                       \r"
	@printf "         $?\r"
	@$(CC_ASM) $(FLAGS) -o $@ $?

clean :
	@echo "\033[34m  - Deleting libftASM's object files\033[0m"
	@rm -f $(OBJ)

fclean : clean
	@echo "\033[34m  - Deleting libfts.a\033[0m"
	@rm -f $(NAME)
	@rm -f bzero_tests
	@rm -f isstuff_tests
	@rm -f tostuff_tests
	@rm -f puts_tests
	@rm -f strnew_tests
	@rm -f strdup_tests
	@rm -f strlen_tests
	@rm -f memcpy_tests
	@rm -f memset_tests
	@rm -f strcat_tests
	@rm -f strncat_tests
	@rm -f cat_tests

tests: bzero isstuff tostuff strcat strncat puts strlen memset memcpy strnew strdup cat

re : fclean all

isstuff: re
	@gcc -c main_isstuff.c
	@gcc -o isstuff_tests main_isstuff.o $(NAME) -Wl,-no_pie
	@rm -f main_isstuff.o
	@./isstuff_tests

tostuff: re
	@gcc -c main_tostuff.c
	@gcc -o tostuff_tests main_tostuff.o $(NAME) -Wl,-no_pie
	@rm -f main_tostuff.o
	@./tostuff_tests

puts: re
	@gcc -c main_puts.c
	@gcc -o puts_tests main_puts.o $(NAME) -Wl,-no_pie
	@rm -f main_puts.o
	@./puts_tests

bzero: re
	@gcc -c main_bzero.c
	@gcc -o bzero_tests main_bzero.o $(NAME) -Wl,-no_pie
	@rm -f main_bzero.o
	@./bzero_tests

memset: re
	@gcc -c main_memset.c
	@gcc -o memset_tests main_memset.o $(NAME) -Wl,-no_pie
	@rm -f main_memset.o
	@./memset_tests

memcpy: re
	@gcc -c main_memcpy.c
	@gcc -o memcpy_tests main_memcpy.o $(NAME) -Wl,-no_pie
	@rm -f main_memcpy.o
	@./memcpy_tests

strlen: re
	@gcc -c main_strlen.c
	@gcc -o strlen_tests main_strlen.o $(NAME) -Wl,-no_pie
	@rm -f main_strlen.o
	@./strlen_tests

strcat: re
	@gcc -c main_strcat.c
	@gcc -o strcat_tests main_strcat.o $(NAME) -Wl,-no_pie
	@rm -f main_strcat.o
	@./strcat_tests

strncat: re
	@gcc -c main_strncat.c
	@gcc -o strncat_tests main_strncat.o $(NAME) -Wl,-no_pie
	@rm -f main_strncat.o
	@./strncat_tests

strnew: re
	@gcc -c main_strnew.c
	@gcc -o strnew_tests main_strnew.o $(NAME) -Wl,-no_pie
	@rm -f main_strnew.o
	@./strnew_tests

strdup: re
	@gcc -c main_strdup.c
	@gcc -o strdup_tests main_strdup.o $(NAME) -Wl,-no_pie
	@rm -f main_strdup.o
	@./strdup_tests

cat: re
	@gcc -c main_cat.c
	@gcc -o cat_tests main_cat.o $(NAME) -Wl,-no_pie
	@rm -f main_cat.o
	@./cat_tests

.PHONY : all clean fclean re tests isstuff tostuff puts bzero memset memcpy strlen strcat strncat strnew strdup cat