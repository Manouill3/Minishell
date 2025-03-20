/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:52 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/20 11:08:38 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"


typedef struct s_fds
{
	int		fd_infile;
	int		fd_outfile;
	int		pipe_fd[2];
	int		pid;
	int		count_com;
	char	**file_input;
	char	**file_output;
}			t_fds;

typedef struct s_heredoc
{
	int		fd;
	char	*name;
	char	*input;
	char	**eof;
}			t_heredoc;

typedef struct s_list_char
{
	char				*data;
	char				*name;
	int					quote;
	struct s_list_char	*next;
	struct s_list_char	*prev;
}						t_list_char;

typedef struct s_init
{
	int     i;
	char    *line;
	char	*pwd;
	char 	*tmp_data;
	char	**tab;
	struct  s_fds 		*fds;
	struct	s_heredoc 	*heredoc;
	struct	s_list_char	*env;
	struct	s_list_char	*tok;
	
}			t_init;

////////////////////////////////////////
///			main.c	                ///
//////////////////////////////////////

int		ft_init(t_init **init);

////////////////////////////////////////
///			utils/utils_parsing.c   ///
//////////////////////////////////////

int     ft_strcmp(char *s1, char *s2);
char	*ft_strndup(const char *s, int n);

////////////////////////////////////////
///			Handle_signaux.c        ///
//////////////////////////////////////

void    ft_handle_interrupt_signals(void);
void	sigint_handler(int sig);

////////////////////////////////////////
///			Order/built_order.c		///
//////////////////////////////////////

char	*get_pwd(void);
void 	ft_pwd();
void    ft_check_order(t_init *init);

////////////////////////////////////////
///			Order/built_cd.c        ///
//////////////////////////////////////

void    ft_cd(t_list_char *lst);

////////////////////////////////////////
///			Parsing/parsing1.c      ///
//////////////////////////////////////

void    ft_parsing_line(t_init *init);
void	ft_parsing_check_quote(char *data, int *quote);
void	ft_parsing_flag(char *name, char *data);
void    ft_parsing_operator(char *data);

////////////////////////////////////////
///			Parsing/token.c         ///
//////////////////////////////////////

void    token(t_init *init);
void 	get_env(t_init *init, char **env);
void	print_lst(t_list_char *lst);
void	ft_check_name(t_init *init);

////////////////////////////////////////
///			utils/utils_lst.c		///
//////////////////////////////////////

t_list_char *ft_lstnew_char(char *str);
void	ft_lstadd_back_char(t_list_char **lst, t_list_char *new);
void	ft_lstdelone_char(t_list_char *lst);
void	ft_lstclear_char(t_list_char **lst);
void	ft_init_list(t_list_char **lst);

////////////////////////////////////////
///			Heredoc/Heredoc.c		///
//////////////////////////////////////

void    ft_check_heredoc(t_list_char *lst, t_heredoc *heredoc);
void	ft_heredoc(t_heredoc *heredoc);
void	ft_heredoc_oef_before(t_heredoc *heredoc, int i);
void	ft_heredoc_oef_last(t_heredoc *heredoc, int i);
char	*get_eof(char *data, char *eof);


////////////////////////////////////////
///			Parsing/expand_2.c		///
//////////////////////////////////////

char    *verif_simple_quote(char *tmp_data, char *data);
char    *ft_value_var(char *tmp_data, t_list_char *tmp, int i);
char	*expand_quote(t_list_char *tmp, char *data);

////////////////////////////////////////
///			Parsing/expand.c		///
//////////////////////////////////////

char	*quote_out(char *cont, char quote);
char	*get_quote_back(char *data, char quote);
char	*ft_expand_rest(t_init *init, char *data, char *content, int i);
char	*ft_expand(t_init *init);

////////////////////////////////////////
///			Free/all_free.c 		///
//////////////////////////////////////

void    ft_free(t_init *init);
void    ft_free_tab(char **tab);
void    ft_free_all(t_init *init);

////////////////////////////////////////
///		Heredoc/utils_Heredock.c	///
//////////////////////////////////////

char	*get_valid_char(char *buffer);
char	*ft_get_name(void);
int 	count_heredoc(t_list_char *lst);

////////////////////////////////////////
///		exec/exec.c					///
//////////////////////////////////////

void	ft_exec_cmd(t_init *init);

#endif