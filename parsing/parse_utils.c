/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:45:46 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/20 15:53:01 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	check_too_many_redir(t_init *param, char *line, int i)
{
	if (i + 2 <= (int)ft_strlen(line)
		&& (line[i + 2] == '<' || line[i + 2] == '>'))
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

int	is_expand_index(t_list_char *tok, int i, t_init *param)
{
	int	k;

	k = 0;
	while (k < param->len_ind_exp && tok->ind_exp[k] != i)
		k++;
	if ( k >= param->len_ind_exp || tok->ind_exp[k] == 0)
		return (0);
	return (1);
}

void	process_cmd_if_expand(char **cmd, int i)
{
	int	j;
	char	*no_quote;

	no_quote = all_quote_out(cmd[i]);
	if (ft_strlen(no_quote) == 1 && no_quote[0] == '$')
		exec_supp(cmd, i);
	if (ft_strchr(cmd[i], '$'))
	{
		j = 0;
		while (cmd[i][j] && cmd[i][j] != '$')
			j++;
		if (cmd[i][j + 1] && (is_white(cmd[i][j + 1]) || cmd[i][j + 1] == '"' || cmd[i][j + 1] == 39))
			exec_supp(cmd, i);
	}
	free(no_quote);
}

void	check_back_expand(t_init *param, t_list_char *tok, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!is_expand_index(tok, i, param))
		{
			i++;
			continue ;
		}
		process_cmd_if_expand(cmd, i);
		i++;
	}
}
