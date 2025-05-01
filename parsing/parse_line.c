/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:08:09 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/01 09:28:11 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	get_funct(t_list_char *lst)
{
	int		i;
	t_list_char	*tmp;
	char		*tmp_tab;

	tmp = lst;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			tmp_tab = ft_strjoin("/bin/", tmp->cmd[i]);
			if (!tmp_tab)
				return ;
			if (!access(tmp_tab, X_OK))
				tmp->funct = ft_strdup(tmp->cmd[i]);
			free(tmp_tab);
			if (tmp->funct)
				break ;
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
	// print_lst_char(param->tok);
	get_no_red(param->tok);
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
