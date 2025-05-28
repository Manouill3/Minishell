/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:26:27 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/28 15:29:01 by mdegache         ###   ########.fr       */
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

static char	**ft_string_exp(size_t word, char const *s, char **str, t_mal *mal)
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
		while (s[i] && is_white(s[i]) && s[i] != '"')
			i++;
		while ((!is_white(s[i + h]) || s[i + h] == '"') && s[i + h] != '\0')
			h++;
		str[j] = ft_substr(s, i, h, mal);
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
		while (s[i] && is_white(s[i]) && s[i] != '"')
			i++;
		if (s[i] && (!is_white(s[i]) || s[i] == '"'))
			word++;
		while (s[i] && (!is_white(s[i]) || s[i] == '"'))
			i++;
		if (save == i)
			i++;
	}
	return (word);
}

char	**ft_exp_split_par(char const *s, t_mal *mal)
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
	word = ft_count_exp(s, i, word);
	if (word == 0)
		return (add_calloc(mal, 1, sizeof(char *)));
	str = add_calloc(mal, word + 1, sizeof(char *));
	if (str == 0)
		return (0);
	i = 0;
	str = ft_string_exp(word, s, str, mal);
	return (str);
}
