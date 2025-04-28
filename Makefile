# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/27 21:16:47 by marvin            #+#    #+#              #
#    Updated: 2025/03/27 21:16:47 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[31m
GREEN=\033[32m
PURPLE=\033[35m
RESET=\033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIB = lib/libft
LIBFT = lib/libft/libft.a

SRC = main.c\
	env/env.c\
	lst/lst_funct_char.c\
	lst/lst_funct_env.c\
	signal/signal.c\
	free/free_funct.c\
	utils/utils_funct.c\
	parsing/parse_line.c\
	parsing/token.c\
	expand/expand.c\
	expand/expand_res.c\
	expand/expand_sup.c\
	expand/expand_heredoc.c\
	heredoc/heredoc.c\
	heredoc/heredoc_exec.c\
	exec/exec_init.c\
	exec/exec_cmd.c\
	exec/exec_utils.c\
	exec/exec_utils2.c\
	exec/exec_file.c \
	built-in/pwd.c \
	built-in/cd.c \
	built-in/echo.c \
	built-in/env_built-in.c \
	built-in/export.c \
	built-in/unset.c \
	built-in/exit.c

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
