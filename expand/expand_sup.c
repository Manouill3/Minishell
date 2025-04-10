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

int	get_len_quote(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 39)
			count++;
		i++;
	}
	return (count);
}

char	*get_final_word(char *word_quote, char *expand)
{
	int		i;
	int		j;
	int		len;
	size_t	k;
	char	*res;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(expand) + get_len_quote(word_quote) + 1;
	res = ft_calloc(len, sizeof(char));
	while (i < len - 1)
	{
		while (word_quote[j] == 39)
			res[i++] = word_quote[j++];
		if (k < ft_strlen(expand))
			res[i] = expand[k++];
		else
			res = get_res(j, i, res, word_quote);
		i++;
	}
	return (res);
}

char	*get_res(int j, int i, char *res, char *word_quote)
{
	while (word_quote[j] && word_quote[j] != 39)
		j++;
	if (word_quote[j])
		res[i] = word_quote[j];
	return (res);
}

char	*expand_quote(char *tmp, char *tmp_free, t_env *lst_env)
{
	tmp = char_out(tmp, '"');
	free(tmp_free);
	tmp_free = NULL;
	tmp_free = tmp;
	tmp = change_word(tmp, lst_env);
	free(tmp_free);
	return (tmp);
}
