/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:28:15 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/24 16:49:22 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_ope(char c)
{
	int	i;

	i = 0;
	if (c == '|')
		i = 1;
	return (i);
}

int	get_quote(int i, const char *s, char c)
{
	i++;
	while (s[i] != c)
		i++;
	return (i);
}

char	**ft_extract_word(const char *s, int *k, int *i, char **tab)
{
	int		j;
	int		len;
	char	c;

	j = 0;
	len = len_word(s, (*k));
	tab[(*i) - 1] = ft_calloc(len + 1, sizeof(char));
	if (!tab[(*i) - 1])
		free_all(tab);
	while (s[(*k)] && j < len)
	{
		if (s[(*k)] == '"' || s[(*k)] == 39)
		{
			c = s[(*k)];
			tab[(*i) - 1][j++] = s[(*k)++];
			while (s[(*k)] && s[(*k)] != c)
				tab[(*i) - 1][j++] = s[(*k)++];
			tab[(*i) - 1][j++] = s[(*k)++];
		}
		else
			tab[((*i)) - 1][j++] = s[((*k))++];
	}
	return (tab);
}

char	**split_ope(const char *s, int k, int i, char **tab)
{
	int	j;
	int	nb_word;

	nb_word = len_first_tab(s);
	while (i++ < nb_word)
	{
		j = 0;
		k = secu(k, s);
		if (k < (int)ft_strlen(s) && i - 1 < nb_word)
			ft_extract_word(s, &k, &i, tab);
	}
	return (tab);
}

char	**handle_quote(const char *s, int *k, char **tab, int i)
{
	int		j;
	int		len;
	char	c;

	j = 0;
	(*k) = secu((*k), s);
	len = len_word(s, (*k));
	tab[i - 1] = ft_calloc(len + 1, sizeof(char));
	if (!tab[i - 1])
		free_all(tab);
	while (j < len && s[(*k)])
	{
		if (s[(*k)] == '"' || s[(*k)] == 39)
		{
			c = s[(*k)];
			tab[i - 1][j++] = s[(*k)++];
			while (s[(*k)] && s[(*k)] != c)
				tab[i - 1][j++] = s[(*k)++];
			tab[i - 1][j++] = s[(*k)++];
		}
		else
			tab[i - 1][j++] = s[(*k)++];
	}
	return (tab);
}
