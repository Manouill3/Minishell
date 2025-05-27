/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:53:48 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/27 10:51:58 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	count_for_other(char *s, int i, int *cmp)
{
	char	c;

	if (s[i] == '"' || s[i] == 39)
	{
		c = s[i++];
		(*cmp)++;
		while (s[i] && s[i] != c)
		{
			i++;
			(*cmp)++;
		}
		if (s[i])
		{
			i++;
			(*cmp)++;
		}
	}
	else
	{
		i++;
		(*cmp)++;
	}
	return (i);
}

int	count_for_red(char *s, int i, int cmp)
{
	while (s[i] && (s[i] == '<' || s[i] == '>'))
	{
		i++;
		cmp++;
	}
	return (cmp);
}

int	count_for_quote(char *s, int i, int *cmp)
{
	char	c;

	c = s[i++];
	(*cmp)++;
	while (s[i] && s[i] != c)
	{
		i++;
		(*cmp)++;
	}
	if (s[i])
	{
		i++;
		(*cmp)++;
	}
	return (i);
}

int	ft_len_word(char *s, int start)
{
	int		i;
	int		cmp;

	i = start;
	cmp = 0;
	if (s[i] == '"' || s[i] == 39)
	{
		i = count_for_quote(s, i, &cmp);
		if (!s[i] || is_white(s[i]))
			return (cmp);
	}
	if (s[i] == '<' || s[i] == '>')
	{
		cmp = count_for_red(s, i, cmp);
		return (cmp);
	}
	while (s[i] && !is_white(s[i]) && s[i] != '<' && s[i] != '>')
		i = count_for_other(s, i, &cmp);
	return (cmp);
}
