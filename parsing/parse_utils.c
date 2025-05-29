/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:45:46 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/29 15:18:03 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	check_too_many_redir(t_init *param, char *line, int i)
{
	if (i + 2 <= (int)ft_strlen(line)
		&& (line[i + 1] == '<' || line[i + 1] == '>')
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
			|| line[*i] == '>' || line[*i] == '"' || line[*i] == 39))
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

int	is_expand_index(t_list_char *tok, int i)
{
	int	k;

	k = 0;
	while (k < tok->len_ind_exp && tok->ind_exp[k] != i)
		k++;
	if (k >= tok->len_ind_exp || tok->ind_exp[k] == 0)
		return (1);
	return (0);
}

void	process_cmd_if_expand(char **cmd, int i, t_mal *mal)
{
	int		j;
	char	*no_quote;

	no_quote = all_quote_out(cmd[i], mal);
	if (ft_strlen(no_quote) == 1 && no_quote[0] == '$')
		exec_supp(cmd, i, mal);
	if (ft_strchr(cmd[i], '$'))
	{
		j = 0;
		while (cmd[i][j] && cmd[i][j] != '$')
			j++;
		if (cmd[i][j + 1] && (is_white(cmd[i][j + 1])
		|| cmd[i][j + 1] == '"' || cmd[i][j + 1] == 39
		|| cmd[i][j + 1] == '$'))
			exec_supp(cmd, i, mal);
	}
}

void	check_back_expand(t_list_char *tok, char **cmd, t_mal *mal)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!is_expand_index(tok, i))
		{
			i++;
			continue ;
		}
		process_cmd_if_expand(cmd, i, mal);
		i++;
	}
}
