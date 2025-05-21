/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:45:40 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/21 14:03:44 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	no_quote_word_len(char *word)
{
	int		i;
	char	q;
	int		count;

	i = 0;
	count = 0;
	while (word[i])
	{
		if (word[i] == 39 || word[i] == '"')
		{
			q = word[i];
			i++;
			while (word[i] && word[i] != q)
			{
				count++;
				i++;
			}
			if (word[i])
				i++;
			continue ;
		}
		i++;
		count++;
	}
	return (count);
}

char	*no_quote_word(char *word)
{
	int		len;
	char	*tmp;

	len = no_quote_word_len(word);
	tmp = ft_calloc(len + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	tmp = no_quote_exec(tmp, word);
	return (tmp);
}

void	exec_supp(char **cmd, int i)
{
	char	*tmp;

	if (ft_strchr(cmd[i], 39) || ft_strchr(cmd[i], '"'))
	{
		tmp = no_quote_word(cmd[i]);
		free(cmd[i]);
		cmd[i] = tmp;
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
		if (check_for_expand(tok, &i))
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
