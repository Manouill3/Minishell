/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:08:09 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/09 10:27:19 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_supp_quote(t_list_char *tok, char **cmd)
{
	int	i;
	int	j;
	int	save;
	int	nb;
	char	*tmp;

	i = 0;
	nb = 0;
	while (cmd[nb])
		nb++;	
	while (i < nb)
	{
		j = 0;
		save = i;
		while (tok->ind_exp[j] && save == i)
		{
			if (tok->ind_exp[j] == i)
				i++;
			j++;
		}
		if (i > save)
			continue ;
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
		i++;
	}
}

void	get_funct(t_init *param, t_list_char *lst)
{
	(void)param;
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
	if (syntax_error(param, param->line))
		return ;
	if (param->count_cmd == 1 && !only_white(param->line))
	{
		param->status = 0;
		return ;
	}
	expand_arg(param);
	get_funct(param, param->tok);
	get_no_red(param->tok);
	get_in_out(param->tok);
	get_nb_eof(param->tok);
	tmp = param->tok;
	while(tmp)
	{
		ft_supp_quote(tmp, tmp->cmd);
		ft_supp_quote(tmp, tmp->no_red);
		free(tmp->ind_exp);
		tmp = tmp->next;
	}
	tmp = param->tok;
	while (tmp)
	{
		exec_heredoc(param, tmp, tmp->heredoc, param->lst_env);
		tmp = tmp->next;
	}
	if (!param->tok)
		return ;
	exec(param);
}

int	syntax_error(t_init *param, char *line)
{
	int	i;
	int	save;
	char c;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == 39)
		{
			c = line[i];
			i++;
			while (line[i] && line[i] != c)
				i++;
			i++;
			continue;
		}
		if (line[i] == '|')
		{
			save = i + 1;
			while (line[save] && is_white(line[save]))
				save++;
			if (line[save] == '|')
			{
				ft_putstr_fd("Two pipes next to each other\n", 2);
				param->status = 2;
				return (1);
			}
		}
		if (line[i] == '|')
		{
			save = i - 1;
			while (save > 0 && is_white(line[save]))
				save--;
			if (i == 0 || save == 0)
			{
				ft_putstr_fd("Error syntax : nothing before pipe\n", 2);
				param->status = 2;
				return (1);
			}
			while (line[i] && (is_white(line[i]) || line[i] == '|'))
				i++;
			if (i >= (int)ft_strlen(param->line))
			{
				ft_putstr_fd("Error syntax : nothing after pipe\n", 2);
				param->status = 2;
				return (1);
			}
		}
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i] == '>' && line[i + 1] == '<')
			{
				ft_putstr_fd("Error syntax : different redirections\n", 2);
				param->status = 2;
				return (1);
			}
			if (line[i] == '<' && line[i + 1] == '>')
			{
				ft_putstr_fd("Error syntax : different redirections\n", 2);
				param->status = 2;
				return (1);
			}
			if (line[i + 2] == '<' || line[i + 2] == '>')
			{
				ft_putstr_fd("Error syntax : too many redirections\n", 2);
				param->status = 2;
				return (1);
			}
			while (line[i] && (is_white(line[i]) || line[i] == '<' || line[i] == '>'))
				i++;
			if (i >= (int)ft_strlen(param->line) || (i < (int)ft_strlen(param->line) && (line[i] == '<' || line[i] == '>' || line[i] == '|')))
			{
				ft_putstr_fd("Error syntax : no file after redirection\n", 2);
				param->status = 2;
				return (1);
			}
		}	
		i++;
	}
	return (0);
}
