/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:03:48 by mdegache          #+#    #+#             */
/*   Updated: 2025/04/24 13:42:50 by mdegache         ###   ########.fr       */
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

	if (is_ope(s[start]) == 1)
		start++;
	while (s[start] && is_white(s[start]) == 1)
		start++;
	i = start;
	while (s[i] && is_ope(s[i]) != 1)
		i++;
	if (s[i] && s[i] == '|')
		i--;
	while (s[i] && is_white(s[i - 1]) == 1)
		i--;
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
			c = s[i];
			i++;
			while (s[i] && s[i] != c)
				i++;
		}
		if (is_white(s[i]) != 1 && s[i + 1] == '\0')
			count++;
		if (is_ope(s[i]) == 1 && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

int	secu(int k, char const *s)
{
	while (s[k] && (is_white(s[k]) == 1 || is_ope(s[k]) == 1))
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
