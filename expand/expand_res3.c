/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_res3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:33:56 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/28 00:24:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_final_input(char *res, char **inputs, int len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < len)
	{
		j = 0;
		while (j < (int)ft_strlen(inputs[i]))
			res[k++] = inputs[i][j++];
		i++;
	}
	return (res);
}

void	handle_expand(t_init *param, t_list_char *tmp, int i, int *j)
{
	if (ft_strchr(tmp->cmd[i], '$'))
	{
		if (i == 0 || ft_strcmp("<<", tmp->cmd[i - 1])
			|| ft_strcmp(">", tmp->cmd[i - 1])
			|| ft_strcmp(">>", tmp->cmd[i - 1])
			|| ft_strcmp("<", tmp->cmd[i - 1]))
		{
			tmp->ind_exp[(*j)++] = i;
			tmp->cmd[i] = expand_word(param, tmp->cmd[i]);
		}
	}
}

char	*handle_double_quote(t_init *param, char *word)
{
	char	*no_quote;
	char	*final_word;

	if (ft_strlen(word) == 0)
		return (NULL);
	no_quote = char_out(word, '"', param->mal);
	if (!ft_strchr(no_quote, '$'))
		return (no_quote);
	final_word = expand_quote(param, no_quote);
	if (!ft_strcmp(final_word, no_quote))
		return (ft_strdup(no_quote, param->mal));
	return (final_word);
}
