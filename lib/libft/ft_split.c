/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:03:48 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/25 15:34:04 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>////// commenrtaire

static void	free_all(char	**tab)
{
	char	**tmp;

	tmp = tab;
	while (*tab)
		free(*tab++);
	free(tmp);
}

static int	len_word(const char *s, int start, char c)
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

static int	len_first_tab(const char *s, char c)
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
			if (s[i] == '"')
				i = get_double_quote(i, s);	
			else				i = get_quote(i, s);
			count++;
		}
		i++;
	}
	printf("||| nb_mot = %d |||\n", count);
	return (count);
}

static int	secu(int k, char c, char const *s)
{
	while (s[k] == c && s[k])
		k++;
	return (k);
}

char	**ft_split(char const *s, char c)
{
	int			i;
	int			j;
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
	while (i++ < nb_word)
	{
		j = 0;
		k = secu(k, c, s);
		if (s[k] == '"' || s[k] == 39)
		{
			k = ft_split_quote(s, k, i, tab);
			i++;
			printf("k = %d\n", k);
			if (k > (int)ft_strlen(s) - 1)
				break;
		}
		tab[i - 1] = ft_calloc(len_word(s, k, c) + 1, sizeof(char));
		if (!tab[i - 1])
			free_all(tab);
		while (s[k] != c && s[k])
			tab[i - 1][j++] = s[k++];
	}
	return (tab);
}
