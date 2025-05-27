/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:28:15 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/27 16:23:47 by mdegache         ###   ########.fr       */
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

char	*ft_extract_word(const char *s, int *k, char *tab, t_mal *mal)
{
	int		j;
	int		len;
	char	c;

	j = 0;
	len = len_word(s, (*k));
	tab = add_calloc(mal, len + 1, sizeof(char));
	while (s[(*k)] && j < len)
	{
		if (s[(*k)] == '"' || s[(*k)] == 39)
		{
			c = s[(*k)];
			tab[j++] = s[(*k)++];
			while (s[(*k)] && s[(*k)] != c)
				tab[j++] = s[(*k)++];
			tab[j++] = s[(*k)++];
		}
		else
			tab[j++] = s[((*k))++];
	}
	return (tab);
}

char	**split_ope(const char *s, int k, char **tab, t_mal *mal)
{
	int	nb_word;
	int	i;

	i = 0;
	nb_word = len_first_tab(s);
	while (i++ < nb_word)
	{
		k = secu(k, s);
		if (k < (int)ft_strlen(s) && i - 1 < nb_word)
			tab[i - 1] = ft_extract_word(s, &k, tab[i - 1], mal);
	}
	return (tab);
}

char	*handle_quote(const char *s, int *k, char *tab, t_mal *mal)
{
	int		j;
	int		len;
	char	c;

	j = 0;
	(*k) = secu((*k), s);
	len = len_word(s, (*k));
	tab = add_calloc(mal, len + 1, sizeof(char));
	while (j < len && s[(*k)])
	{
		if (s[(*k)] == '"' || s[(*k)] == 39)
		{
			c = s[(*k)];
			tab[j++] = s[(*k)++];
			while (s[(*k)] && s[(*k)] != c)
				tab[j++] = s[(*k)++];
			tab[j++] = s[(*k)++];
		}
		else
			tab[j++] = s[(*k)++];
	}
	return (tab);
}
