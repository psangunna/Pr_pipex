# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psangunna <psanguna@student.42madrid>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 21:26:43 by psangunna         #+#    #+#              #
#    Updated: 2024/08/01 21:26:47 by psangunna        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Werror -Wall -Wextra -fsanitize=address
RM = rm -rf

# Define source files
SRC = src/pipex.c \
      src/pipex_helpers.c

SRC_BONUS = src_bonus/pipex_bonus.c \
            src_bonus/pipex_helpers_bonus.c

# Define object files
OBJ = $(SRC:.c=.o)
O_BONUS_FILES = $(SRC_BONUS:.c=.o)

# Define cache file
BONUS_CACHE = .cache

# Default target
all: $(NAME)

# Rule to build the main executable
$(NAME): $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

# Rule to build the bonus executable
bonus: $(BONUS_CACHE)

$(BONUS_CACHE): $(O_BONUS_FILES)
	make -C libft
	$(CC) $(CFLAGS) $(O_BONUS_FILES) libft/libft.a -o $(NAME)
	touch $(BONUS_CACHE)

# Rule to build the libft library
libft/libft.a:
	make -C libft

# Clean object files
clean:
	$(RM) $(OBJ) $(O_BONUS_FILES) $(BONUS_CACHE)
	make clean -C libft

# Clean everything
fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

# Rebuild everything
re: fclean all

# Rebuild bonus version
rebonus: fclean bonus
