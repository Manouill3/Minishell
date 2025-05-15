/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:45:46 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/15 17:34:42 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	check_mixed_redir(t_init *param, char *line, int i)
{
	if ((line[i] == '>' && line[i + 1] == '<')
		|| (line[i] == '<' && line[i + 1] == '>'))
	{
		ft_putstr_fd("Error syntax : different redirections\n", 2);
		param->status = 2;
		return (1);
	}
	return (0);
}

int	check_too_many_redir(t_init *param, char *line, int i)
{
	if (i + 2 <= (int)ft_strlen(line) && (line[i + 2] == '<' || line[i + 2] == '>'))
	{
		ft_putstr_fd("Error syntax : too many redirections\n", 2);
		param->status = 2;
		return (1);
	}
	return (0);
}

int	check_redir_no_file(t_init *param, char *line, int *i)
{
	while (line[*i] && (is_white(line[*i]) || line[*i] == '<'
			|| line[*i] == '>'))
		(*i)++;
	if (*i >= (int)ft_strlen(line)
		|| line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
	{
		ft_putstr_fd("Error syntax : no file after redirection\n", 2);
		param->status = 2;
		return (1);
	}
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
