/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:45:52 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/04 10:12:06 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"


typedef struct s_list_char
{
	char				*data;
	char				*name;
	struct s_list_char	*next;
	struct s_list_char	*prev;
}						t_list_char;

typedef struct s_init
{
	int     i;
	char    *line;
	char	**tab;
	struct	s_list_char	*env;
	struct	s_list_char	*tok;
	
}			t_init;

////////////////////////////////////////
///			utils/utils_parsing	    ///
//////////////////////////////////////

int     ft_strcmp(char *s1, char *s2);
void    ft_free(t_init *init);
void    ft_free_tab(char **tab);
char	*ft_strndup(const char *s, int n);
void	ft_get_start(t_list_char **tok);

////////////////////////////////////////
///			Handle_signaux          ///
//////////////////////////////////////

void    ft_handle_interrupt_signals(void);

////////////////////////////////////////
///			Order/pwd.c             ///
//////////////////////////////////////

void    ft_check_order(t_init *init);

////////////////////////////////////////
///			Parsing/parsing1.c      ///
//////////////////////////////////////

void    ft_parsing_line(t_init *init, char **env);

////////////////////////////////////////
///			Parsing/token.c         ///
//////////////////////////////////////

void    token(t_init *init);
void 	get_env(t_init *init, char **env);

////////////////////////////////////////
///			utils/utils_lst.c		///
//////////////////////////////////////

t_list_char *ft_lstnew_char(char *str);
void	ft_lstadd_back_char(t_list_char **lst, t_list_char *new);
void	ft_lstdelone_char(t_list_char *lst);
void	ft_lstclear_char(t_list_char **lst);

////////////////////////////////////////
///			Heredoc/Heredock.c		///
//////////////////////////////////////


#endif