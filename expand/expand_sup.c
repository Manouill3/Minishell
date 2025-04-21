/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_sup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:08:00 by marvin            #+#    #+#             */
/*   Updated: 2025/03/29 17:08:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_result(char *cont, char *word)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	i = 0;
	j = 0;
	k = 0;
	result = ft_calloc(ft_strlen(cont) + count_quote(word) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (j < (int)ft_strlen(cont) + count_quote(word))
	{
		if (word[i] != 39 && word[i] != '"')
		{
			while (word[i] && word[i] != 39 && word[i] != '"')
				i++;
			while (cont[k])
				result[j++] = cont[k++];
		}
		else
			result[j++] = word[i++];
	}
	free(cont);
	return (result);
}

int	get_len_w_q(char *word, char quote, int	i)
{
	i++;
	while (word[i] && word[i] != quote)
		i++;
	return (i);
}

char	*all_quote_out(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != 39 && str[i] != '"')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	return (new);
}

char	*char_out(char *str, char c)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	return (new);
}
