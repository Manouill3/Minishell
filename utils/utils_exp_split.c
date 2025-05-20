/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exp_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:24:26 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/20 16:45:36 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	white_or_not(char *s)
{
	if (ft_strchr(s, 9))
		return (1);
	if (ft_strchr(s, 10))
		return (1);
	if (ft_strchr(s, 11))
		return (1);
	if (ft_strchr(s, 12))
		return (1);
	if (ft_strchr(s, 13))
		return (1);
	if (ft_strchr(s, 32))
		return (1);
	return (0);
}

char	*no_quote_exec(char *tmp, char *word)
{
	int		i;
	int		j;
	char	q;

	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == 39 || word[i] == '"')
		{
			q = word[i];
			i++;
			while (word[i] && word[i] != q)
				tmp[j++] = word[i++];
			if (word[i])
				i++;
		}
		else
			while (word[i] && word[i] != 39 && word[i] != '"')
				tmp[j++] = word[i++];
	}
	return (tmp);
}
