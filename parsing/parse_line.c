/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:08:09 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/20 15:50:08 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	check_for_expand(t_list_char *tok, int *i, t_init *param)
{
	int	j;
	int	save;

	j = 0;
	save = (*i);
	while (save == (*i) &&  j < param->len_ind_exp)
	{
		if (tok->ind_exp[j] == (*i))
			(*i)++;
		j++;
	}
	if ((*i) > save)
		return (1);
	return (0);
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

	supp_quote_red(param->tok);
	get_in_out(param->tok);
	get_nb_eof(param->tok);
	tmp = param->tok;
	while (tmp)
	{
		exec_heredoc(tmp, tmp->heredoc, param->lst_env);
		tmp = tmp->next;
	}
	tmp = param->tok;
	while (tmp)
	{
		ft_supp_quote(tmp, tmp->cmd, param);
		check_back_expand(param, tmp, tmp->cmd);
		ft_supp_quote(tmp, tmp->no_red, param);
		check_back_expand(param, tmp, tmp->no_red);
		free(tmp->ind_exp);
		tmp = tmp->next;
	}
	if (!param->tok)
		return ;
	exec(param);
}

void	parsing_line(t_init *param)
{
	if (get_token(param))
	{
		param->status = 2;
		ft_putstr_fd("Syntax error : open quote\n", 2);
		return ;
	}
	if (syntax_error(param, param->line))
		return ;
	if (param->count_cmd == 1 && !only_white(param->line))
	{
		param->status = 0;
		return ;
	}
	expand_arg(param);
	verif_expand(param);
	get_funct(param->tok);
	get_no_red(param->tok);
	before_exec(param);
}
