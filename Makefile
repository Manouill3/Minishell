# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 14:14:26 by mdegache          #+#    #+#              #
#    Updated: 2025/03/26 16:42:09 by tcybak           ###   ########.fr        #
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
	Free/all_free.c\
	Parsing/utils_parsing.c\
	utils/utils_lst.c\
	Handle_signaux.c\
	order/built_order.c\
	order/built_cd.c\
	Parsing/Parsing1.c\
	Parsing/token.c\
	Parsing/expand.c\
	Parsing/expand_2.c\
	Heredoc/Heredoc.c\
	Heredoc/utils_heredoc.c\
	exec/exec.c\
	exec/handle_redirection.c\
	exec/exec_init.c
	

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(SRC) $(LIBFT) $(CFLAGS) -o $(NAME) -lreadline -lncurses
	@echo "$(GREEN)SUCCESS$(RESET)"

$(LIBFT):
	@$(MAKE) -s -C $(LIB) bonus

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -s -C $(LIB) clean
	@echo "$(PURPLE)CLEAN$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIB) fclean
	@echo "$(RED)FCLEAN$(RESET)"

re: fclean all

.PHONY: all clean fclean re