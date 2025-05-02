/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:08:09 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/02 11:06:43 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_supp_quote(char **cmd)
{
	int	i;
	int	j;
	int	nb;
	char	*tmp;

	i = 0;
	nb = 0;
	while (cmd[i])
	{
		nb++;
		i++;	
	}
	i = 0;
	while (i < nb)
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == 39 || cmd[i][j] == '"')
			{
				tmp = char_out(cmd[i], cmd[i][j]);
				free(cmd[i]);
				cmd[i] = NULL;
				cmd[i] = ft_strdup(tmp);
				free(tmp);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	get_funct(t_list_char *lst)
{
	int		i;
	t_list_char	*tmp;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		while (i < tmp->len_cmd)
		{
			if (i > 0)
			{
				if (ft_strlen(tmp->cmd[i]) > 0 && is_red(tmp->cmd[i]) && is_red(tmp->cmd[i - 1]))
				{
					tmp->funct = ft_strdup(tmp->cmd[i]);
					break ;
				}
			}
			else
				if (ft_strlen(tmp->cmd[i]) > 0 && is_red(tmp->cmd[i]))
				{
					tmp->funct = ft_strdup(tmp->cmd[i]);
					break ;
				}
			i++;
		}
		tmp = tmp->next;
	}
}

void	parsing_line(t_init *param)
{
	t_list_char	*tmp;
	
	get_token(param);
	expand_arg(param);
	get_funct(param->tok);
	get_no_red(param->tok);
	ft_supp_quote(param->tok->cmd);
	ft_supp_quote(param->tok->no_red);
	// print_lst_char(param->tok);
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
