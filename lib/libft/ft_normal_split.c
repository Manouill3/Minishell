/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normal_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:02:49 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/24 21:28:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(int j, char **str)
{
	while (j + 1 > 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
}

static char	**ft_string(size_t word, char const *s, char **str, char c, t_mal *mal)
{
	size_t	j;
	size_t	h;
	size_t	i;

	j = 0;
	h = 0;
	i = 0;
	while (word--)
	{
		i = i + h;
		h = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i + h] != c && s[i + h] != '\0')
			h++;
		str[j] = ft_substr(s, i, h, mal);
		if (str[j] == 0)
		{
			ft_free(j, str);
			return (0);
		}
		j++;
	}
	return (str);
}

static int	ft_count(char const *s, char c, size_t i, size_t word)
{
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			word++;
		while (s[i] != c && s[i])
			i++;
	}
	return (word);
}

char	**ft_normal_split(char const *s, char c, t_mal *mal)
{
	char	**str;
	size_t	i;
	size_t	word;

	word = 0;
	i = 0;
	if (s == 0)
		return (0);
	if (ft_strlen(s) == 0)
		return (add_calloc(mal, 1, sizeof(char *)));
	word = ft_count(s, c, i, word);
	if (word == 0)
		return (add_calloc(mal, 1, sizeof(char *)));
	str = add_calloc(mal, word + 1, sizeof(char *));
	if (str == 0)
		return (0);
	i = 0;
	str = ft_string(word, s, str, c, mal);
	return (str);
}
