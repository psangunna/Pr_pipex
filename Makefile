# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psangunna <psanguna@student.42madrid>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 18:40:54 by psangunna         #+#    #+#              #
#    Updated: 2024/07/09 18:41:02 by psangunna        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address

RM = rm -rf

SRC = src/pipex.c\
		src/pipex_helpers.c\
		libft/libft.a\

SRC_BONUS = src_bonus/pipex_bonus.c\
				src_bonus/pipex_helpers_bonus.c\
				libft/libft.a\

$(NAME):
	make all -C libft
	gcc $(CFLAGS) $(SRC) -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C libft

re : fclean all

bonus : clean
	make all -C libft
	gcc $(CFLAGS) $(SRC_BONUS) -o $(NAME)
