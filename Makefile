# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 14:14:26 by mdegache          #+#    #+#              #
#    Updated: 2025/02/17 14:46:10 by mdegache         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[31m
GREEN=\033[32m
PURPLE=\033[35m
RESET=\033[0m

NAME = Minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIB = lib/libft
LIBFT = lib/libft/libft.a

SRC = main.c\
	utils/utils_parsing.c

OBJ = $(SRC:.c=.o)

all: $(NAME) clean

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(SRC) $(LIBFT) $(CFLAGS) -o $(NAME) -lreadline -lncurses
	@echo "$(GREEN)SUCCESS$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIB) bonus

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ) $(OBJ_BONUS) $(OBJ_LIB)
	@echo "$(PURPLE)CLEAN$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)FCLEAN$(RESET)"

re: fclean all

.PHONY: all clean fclean re