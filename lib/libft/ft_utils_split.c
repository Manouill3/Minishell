/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:28:15 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/04 14:22:21 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_quote(int i, const char *s, char c)
{
	i++;
	while (s[i] != c)
		i++;
	return (i);
}

int	ft_split_quote(const char *s, int k, int i, char **tab)
{
	int		tmp;
	int		count;
	char	q;
	int		j;

	q = s[k];
	tmp = k + 1;
	j = 0;
	k++;
	count = 2;
	while (s[tmp] != q)
	{
		tmp++;
		count++;
	}
	tab[i - 1] = ft_calloc(count + 1, sizeof(char));
	tab[i - 1][j++] = q;
	while (s[k] != q)
	{
		tab[i - 1][j] = s[k];
		j++;
		k++;
	}
	tab[i - 1][j] = s[k];
	return (k);                                                                                                           
}

int	ft_check_quote(const char *s, int k, int i, char **tab)
{
	if (s[k] == '"' || s[k] == 39)
	{
		k = ft_split_quote(s, k, i, tab);
		k++;
		i++;
		k = secu(k, s);
	}
	return (k);
}

char	**exec_all(const char *s, int k, int i, char **tab)
{
	int	j;
	int	tmp;
	int	nb_word;

	nb_word = len_first_tab(s);
	while (i++ < nb_word)
	{
		j = 0;
		k = secu(k, s);
		tmp = k;
		k = ft_check_quote(s, k, i, tab);
		if (k == tmp)
		{
			if (tab[i - 1] != NULL)
				i++;
			if (k > (int)ft_strlen(s) - 1)
				break ;
			tab[i - 1] = ft_calloc(len_word(s, k) + 1, sizeof(char));
			if (!tab[i - 1])
				free_all(tab);
			while (is_white(s[k]) != 1 && s[k])
				tab[i - 1][j++] = s[k++];
		}
	}
	return (tab);
}

int	is_white(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
