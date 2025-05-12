/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:08:09 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/12 16:14:42 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	check_for_expand(t_list_char *tok, char **cmd, int *i)
{
	int	j;
	int	k;
	int	save;

	j = 0;
	k = 0;
	save = (*i);
	while (tok->ind_exp[j] && save == (*i))
	{
		while (cmd[(*i)][k] && cmd[(*i)][k] != '$')
			k++;
		if (tok->ind_exp[j] == (*i) && !is_white(cmd[(*i)][k + 1])
			&& cmd[(*i)][k + 1] != '"' && cmd[(*i)][k + 1] != 39)
			(*i)++;
		j++;
	}
	if ((*i) > save)
		return (1);
	return (0);
}

void	exec_supp(char **cmd, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (cmd[i][j])
	{
		if (cmd[i][j] == 39 || cmd[i][j] == '"')
		{
			tmp = cmd[i];
			cmd[i] = char_out(cmd[i], cmd[i][j]);
			free(tmp);
			break ;
		}
		j++;
	}
}

void	ft_supp_quote(t_list_char *tok, char **cmd)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (cmd[nb])
		nb++;
	while (i < nb)
	{
		if (check_for_expand(tok, cmd, &i))
			continue ;
		exec_supp(cmd, i);
		i++;
	}
}

void	get_funct_ann(t_list_char *tmp, int i)
{
	while (i < tmp->len_cmd)
	{
		if (i > 0)
		{
			if (ft_strlen(tmp->cmd[i]) > 0 && is_red(tmp->cmd[i])
				&& is_red(tmp->cmd[i - 1]))
			{
				tmp->funct = ft_strdup(tmp->cmd[i]);
				break ;
			}
		}
		else if (ft_strlen(tmp->cmd[i]) > 0 && is_red(tmp->cmd[i]))
		{
			tmp->funct = ft_strdup(tmp->cmd[i]);
			break ;
		}
		i++;
	}
}

void	get_funct(t_list_char *lst)
{
	int			i;
	t_list_char	*tmp;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		get_funct_ann(tmp, i);
		tmp = tmp->next;
	}
}

void	before_exec(t_init *param)
{
	t_list_char	*tmp;

	tmp = param->tok;
	while (tmp)
	{
		ft_supp_quote(tmp, tmp->cmd);
		ft_supp_quote(tmp, tmp->no_red);
		free(tmp->ind_exp);
		tmp = tmp->next;
	}
	get_in_out(param->tok);
	get_nb_eof(param->tok);
	tmp = param->tok;
	while (tmp)
	{
		exec_heredoc(tmp, tmp->heredoc, param->lst_env);
		tmp = tmp->next;
	}
	if (!param->tok)
		return ;
	exec(param);
}

void	parsing_line(t_init *param)
{
	get_token(param);
	if (syntax_error(param, param->line))
		return ;
	if (param->count_cmd == 1 && !only_white(param->line))
	{
		param->status = 0;
		return ;
	}
	expand_arg(param);
	get_funct(param->tok);
	get_no_red(param->tok);
	before_exec(param);
}
