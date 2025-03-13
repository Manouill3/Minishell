/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:40:44 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/13 15:33:44 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (*s1 == 0)
        return (1);
    while (s1[i])
    {
        if (s1[i] != s2[i])
            return (s1 - s2);
        i++;
    }
    return (0);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*tab;

	tab = malloc(sizeof(char) * n + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
