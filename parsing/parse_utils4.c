/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:45:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/20 15:40:53 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

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

void	ft_supp_quote(t_list_char *tok, char **cmd , t_init *param)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (cmd[nb])
		nb++;
	while (i < nb)
	{
		if (check_for_expand(tok, &i, param))
			continue ;
		exec_supp(cmd, i);
		i++;
	}
}

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
