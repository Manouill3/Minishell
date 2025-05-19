/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:22:33 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/19 16:54:44 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	ft_free_exp(int j, char **str)
{
	while (j + 1 > 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
}

static char	**ft_string_exp(size_t word, char const *s, char **str)
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
		while (s[i] && is_white(s[i]))
			i++;
		while (!is_white(s[i + h]) && s[i + h] != '\0')
			h++;
		str[j] = ft_substr(s, i, h);
		if (str[j] == 0)
		{
			ft_free_exp(j, str);
			return (0);
		}
		j++;
	}
	return (str);
}

static int	ft_count_exp(char const *s, size_t i, size_t word)
{
	size_t	save;

	while (s[i] != '\0')
	{
		save = i;
		while (s[i] && is_white(s[i]))
			i++;
		if (s[i] && !is_white(s[i]))
			word++;
		while (s[i] && is_white(s[i]))
			i++;
		if (save == i)
			i++;
	}
	return (word);
}

char	**ft_exp_split(char const *s)
{
	char	**str;
	size_t	i;
	size_t	word;

	word = 0;
	i = 0;
	if (s == 0)
		return (0);
	if (ft_strlen(s) == 0)
		return (ft_calloc(1, sizeof(char *)));
	word = ft_count_exp(s, i, word);
	if (word == 0)
		return (ft_calloc(1, sizeof(char *)));
	str = ft_calloc(word + 1, sizeof(char *));
	if (str == 0)
		return (0);
	i = 0;
	str = ft_string_exp(word, s, str);
	return (str);
}
