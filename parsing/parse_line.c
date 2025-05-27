/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:08:09 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/27 13:38:37 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	check_for_expand(t_list_char *tok, int *i)
{
	int	j;
	int	save;

	j = 0;
	save = (*i);
	while (save == (*i) && j < tok->len_ind_exp)
	{
		if (tok->ind_exp[j] == (*i))
			(*i)++;
		j++;
	}
	if ((*i) > save)
		return (1);
	return (0);
}

void	get_funct_ann(t_list_char *tmp, int i, t_mal *mal)
{
	while (i < tmp->len_cmd)
	{
		if (i > 0)
		{
			if (ft_strlen(tmp->cmd[i]) > 0 && is_red(tmp->cmd[i])
				&& is_red(tmp->cmd[i - 1]))
			{
				tmp->funct = ft_strdup(tmp->cmd[i], mal);
				break ;
			}
		}
		else if (ft_strlen(tmp->cmd[i]) > 0 && is_red(tmp->cmd[i]))
		{
			tmp->funct = ft_strdup(tmp->cmd[i], mal);
			break ;
		}
		i++;
	}
}

void	get_funct(t_list_char *lst, t_mal *mal)
{
	int			i;
	t_list_char	*tmp;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		get_funct_ann(tmp, i, mal);
		tmp = tmp->next;
	}
}

void	before_exec(t_init *param, t_mal *mal)
{
	t_list_char	*tmp;

	supp_quote_red(param->tok, mal);
	get_in_out(param->tok, mal);
	get_nb_eof(param->tok);
	tmp = param->tok;
	while (tmp)
	{
		exec_heredoc(tmp, tmp->heredoc, param->lst_env, mal);
		tmp = tmp->next;
	}
	tmp = param->tok;
	while (tmp)
	{
		ft_supp_quote(tmp, tmp->cmd, mal);
		check_back_expand(tmp, tmp->cmd, mal);
		ft_supp_quote(tmp, tmp->no_red, mal);
		check_back_expand(tmp, tmp->no_red, mal);
		tmp = tmp->next;
	}
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
	if (!param->tok)
		return ;
	if (syntax_error(param, param->line))
		return ;
	if (param->count_cmd == 1 && !only_white(param->line))
	{
		param->status = 0;
		return ;
	}
	expand_arg(param);
	verif_expand(param);
	get_funct(param->tok, param->mal);
	get_no_red(param->tok, param);
	before_exec(param, param->mal);
}
