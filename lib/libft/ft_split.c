/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:03:48 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/21 13:27:47 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_all(char	**tab)
{
	char	**tmp;

	tmp = tab;
	while (*tab)
		free(*tab++);
	free(tmp);
}

int	len_word(const char *s, int start)
{
	int	i;

	i = start;
	if (is_ope(s[i]) == 1)
	{
		while (is_ope(s[i]) == 1)
			i++;
		return (i - start);
	}
	while (is_white(s[i]) != 1 && is_ope(s[i]) != 1 && s[i])
	{
		if (s[i] == '"' || s[i] == 39)
		{
			i++;
			while (s[i] && s[i] != '"' && s[i] != 39)
				i++;
			i++;
		}
		else
			i++;
	}
	return (i - start);
}

int	len_first_tab(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_white(s[i]) != 1 && (is_white(s[i + 1]) == 1
				|| s[i + 1] == '\0'))
			count++;
		if ((is_ope(s[i]) != 1 && is_ope(s[i + 1]) == 1 && is_white(s[i]) != 1)
			|| (is_ope(s[i]) == 1 && is_ope(s[i + 1]) != 1
				&& is_white(s[i + 1]) != 1))
			count++;
		i++;
	}
	return (count);
}

int	secu(int k, char const *s)
{
	while (is_white(s[k]) == 1 && s[k])
		k++;
	return (k);
}

char	**ft_split(char const *s)
{
	int			i;
	int			k;
	int			nb_word;
	char		**tab;

	i = 0;
	k = 0;
	if (!s)
		return (0);
	nb_word = len_first_tab(s);
	tab = ft_calloc(nb_word + 1, sizeof(char *));
	if (!tab)
		return (0);
	tab = exec_all(s, k, i, tab);
	return (tab);
}
