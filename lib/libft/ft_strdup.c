/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:06:11 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/24 21:22:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, t_mal *mal)
{
	int		i;
	int		len;
	char	*tab;

	len = ft_strlen(s);
	tab = add_malloc(mal, sizeof(char) * len + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
