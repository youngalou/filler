# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lyoung <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/07 13:21:13 by lyoung            #+#    #+#              #
#    Updated: 2017/08/22 11:44:12 by lyoung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = filler
CFLAG = -Wall -Werror -Wextra -g
LIBFT = libft/libft.a

FILES = main.c \
		read.c \
		heatmap.c \
		trim_piece.c \
		place_piece.c \

SRC = $(addprefix src/, $(FILES))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) filler.h
	@gcc -o $(NAME) $(CFLAG) $(OBJ) $(LIBFT)
	@echo "\033[32m- $(NAME) executable compiled\033[0m"

$(OBJ): %.o: %.c
	gcc -c $(CFLAG) $< -o $@

$(LIBFT):
	@make -C libft

clean:
	@rm -f $(OBJ)
	@echo "\033[31m- $(NAME) object files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[31m- $(NAME) executable removed\033[0m"
	@make -C libft fclean

re: fclean all
