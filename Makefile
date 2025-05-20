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
	env/no_env.c\
	lst/lst_funct_char.c\
	lst/lst_funct_env.c\
	signal/signal.c\
	free/free_funct.c\
	utils/utils_funct.c\
	utils/print_funct.c\
	utils/split_exp.c\
	utils/utils_exp_split.c\
	parsing/parse_line.c\
	parsing/parse_utils.c\
	parsing/parse_utils2.c\
	parsing/parsing_utils3.c\
	parsing/parse_utils4.c\
	parsing/parse_syntax_error.c\
	parsing/token.c\
	parsing/len_word.c\
	expand/expand.c\
	expand/expand_res.c\
	expand/expand_res2.c\
	expand/expand_res3.c\
	expand/expand_sup.c\
	expand/expand_heredoc.c\
	heredoc/heredoc.c\
	heredoc/heredoc_exec.c\
	heredoc/heredoc_ann.c\
	exec/exec_init.c\
	exec/exec_init2.c\
	exec/exec_cmd.c\
	exec/exec_cmd2.c\
	exec/exec_utils.c\
	exec/exec_utils2.c\
	exec/set_args.c\
	exec/exec_file.c\
	exec/exec_file2.c\
	built-in/pwd.c\
	built-in/cd_utils.c\
	built-in/cd_utils2.c\
	built-in/cd_utils3.c\
	built-in/cd.c\
	built-in/echo.c\
	built-in/env_built-in.c\
	built-in/export.c\
	built-in/export_var.c\
	built-in/export_add.c\
	built-in/export_add_utils.c\
	built-in/export_var_utils.c\
	built-in/unset.c\
	built-in/exit.c

OBJ_DIR = build
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(SRC) $(LIBFT) $(CFLAGS) -o $(NAME) -lreadline -lncurses
	@echo "$(GREEN)SUCCESS$(RESET)"

$(LIBFT):
	@$(MAKE) -s -C $(LIB) bonus

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

val:
	valgrind --leak-check=full --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=readline.sup ./minishell

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIB) clean
	@echo "$(PURPLE)CLEAN$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIB) fclean
	@echo "$(RED)FCLEAN$(RESET)"

re: fclean all

.PHONY: all clean fclean re
