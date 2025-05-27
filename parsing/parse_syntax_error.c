/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:14:17 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/28 01:45:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	check_redirections(t_init *param, char *line, int *i)
{
	if (line[*i] == '>' || line[*i] == '<')
	{
		if (check_mixed_redir(param, line, *i))
			return (1);
		if (check_too_many_redir(param, line, *i))
			return (1);
		if (check_redir_no_file(param, line, i))
			return (1);
	}
	return (0);
}

int	check_pipe_context(t_init *param, char *line, int *i)
{
	int	save;

	if (line[*i] == '|')
	{
		save = *i - 1;
		while (save > 0 && is_white(line[save]))
			save--;
		if (*i == 0 || save == 0)
			return (ft_putstr_fd("Error syntax : nothing before pipe\n", 2),
				param->status = 2, 1);
		while (line[*i] && (is_white(line[*i]) || line[*i] == '|'))
			(*i)++;
		if (*i >= (int)ft_strlen(line))
			return (ft_putstr_fd("Error syntax : nothing after pipe\n", 2),
				param->status = 2, 1);
	}
	return (0);
}

int	check_double_pipes(t_init *param, char *line, int i)
{
	int	save;

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
	return (0);
}

int	check_quotes(char *line, int *i)
{
	char	c;

	if (line[*i] == '"' || line[*i] == 39)
	{
		c = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != c)
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

int	syntax_error(t_init *param, char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	if (len == 1 && (line[0] == '!' || line[0] == ':'))
		return (1);
	while (i < len && line[i])
	{
		if (check_quotes(line, &i))
			continue ;
		if (check_double_pipes(param, line, i))
			return (1);
		if (check_pipe_context(param, line, &i))
			return (1);
		if (check_redirections(param, line, &i))
			return (1);
		i++;
	}
	return (0);
}
