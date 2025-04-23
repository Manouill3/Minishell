/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:03:48 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/23 16:36:29 by mdegache         ###   ########.fr       */
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
	size_t	i;

	i = start;
	if (is_ope(s[i]) == 1)
	{
		while (is_ope(s[i]) == 1)
			i++;
		return (i - start);
	}
	while (i < ft_strlen(s) && is_white(s[i]) != 1 && is_ope(s[i]) != 1)
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
	char	c;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == 39)
		{
			c = s[i++];
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
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
	printf("nb_word = %d\n", nb_word);
	tab = ft_calloc(nb_word + 1, sizeof(char *));
	if (!tab)
		return (0);
	tab = exec_all(s, k, i, tab);
	return (tab);
}
