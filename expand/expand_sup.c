/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_sup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:08:00 by marvin            #+#    #+#             */
/*   Updated: 2025/05/22 19:28:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	inputs_len(char *word)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (word[i])
	{
		if (word[i] == '"' || word[i] == 39)
			i = get_len_w_q(word, word[i], i);
		else if (word[i] == '$')
			i = get_len_w_d(word, i);
		else
		{
			while (word[i] && (word[i] != '$' && word[i] != '"'
					&& word[i] != 39))
				i++;
		}
		len++;
	}
	return (len);
}

int	get_len_w_d(char *word, int i)
{
	i++;
	if (ft_isdigit(word[i]))
	{
		i++;
		return (i);
	}
	while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
		i++;
	return (i);
}

int	get_len_w_q(char *word, char quote, int i)
{
	i++;
	while (word[i] && word[i] != quote)
		i++;
	if (word[i])
		i++;
	return (i);
}

char	*all_quote_out(char *str, t_mal *mal)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = add_calloc(mal, ft_strlen(str) + 1, sizeof(char));
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

char	*char_out(char *str, char c, t_mal *mal)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = add_calloc(mal, ft_strlen(str) + 1, sizeof(char));
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
