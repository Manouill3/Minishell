/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:08:09 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/10 13:01:06 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_fonct_suit(t_list_char *tmp, int *i, int *j, char **tmp_tab)
{
	while ((*i) < len_cmd(tmp->cmd))
	{
		while (tmp->cmd[(*i)] && (!ft_strcmp("<", tmp->cmd[(*i)]) || !ft_strcmp(">", tmp->cmd[(*i)])))
		(*i) = (*i) + 2;
		if ((*i) < len_cmd(tmp->cmd))
		{
			tmp_tab[(*j)] = ft_strdup(tmp->cmd[(*i)]);
			break ;
		}
	}
	return (tmp_tab[(*j)]);
}

void	get_funct(t_list_char *lst)
{
	int		i;
	int		j;
	t_list_char	*tmp;
	char		**tmp_tab;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		j = 0;
		tmp_tab = ft_calloc(2, sizeof(char *));
		if (!tmp_tab)
			return ;
		get_fonct_suit(tmp, &i, &j, tmp_tab);
		if (tmp_tab[j])
			tmp->funct = ft_strdup(tmp_tab[0]);
		else
			tmp->funct = NULL;
		free_tab(tmp_tab);
		tmp = tmp->next;
	}
}

void	parsing_line(t_init *param)
{
	t_list_char	*tmp;
	
	get_token(param);
	expand_arg(param);
	get_funct(param->tok);
	tmp = param->tok;
	get_nb_eof(param->tok);
	while (tmp)
	{
		exec_heredoc(tmp, tmp->heredoc, param->lst_env);
		close (tmp->heredoc->fd);
		unlink(tmp->heredoc->name);
		free(tmp->heredoc->name);
		tmp->heredoc->name = NULL;
		tmp = tmp->next;
	}
	if (!param->tok->cmd[0])
		return ;
	exec(param);
}
