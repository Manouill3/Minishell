/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:03:48 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/26 10:20:15 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>////// commenrtaire

void	free_all(char	**tab)
{
	char	**tmp;

	tmp = tab;
	while (*tab)
		free(*tab++);
	free(tmp);
}

int	len_word(const char *s, int start, char c)
{
	int	i;
	int	cmp;

	i = start;
	cmp = 0;
	while (s[i] != c && s[i])
	{
		i++;
		cmp++;
	}
	return (cmp);
}

int	len_first_tab(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		if (s[i] == '"' || s[i] == 39)
		{
			if (s[i] == '"' || s[i] == 39)				
				i = get_quote(i, s);
			count++;
		}
		i++;
	}
	printf("||| nb_mot = %d |||\n", count);
	return (count);
}

int	secu(int k, char c, char const *s)
{
	while (s[k] == c && s[k])
		k++;
	return (k);
}

char	**ft_split(char const *s, char c)
{
	int			i;
	int			k;
	int			nb_word;
	char		**tab;

	i = 0;
	k = 0;
	if (!s)
		return (0);
	nb_word = len_first_tab(s, c);
	tab = ft_calloc(nb_word + 1, sizeof(char *));
	if (!tab)
		return (0);
	tab = exec_all(s, k, i, tab, c);
	return (tab);
}
