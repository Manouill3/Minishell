/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:10:16 by mdegache          #+#    #+#             */
/*   Updated: 2025/05/22 13:39:03 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, t_mal *mal)
{
	size_t	k;
	char	*tab;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup("", mal));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	tab = add_malloc(mal, sizeof(char) * len + 1);
	if (!tab)
		return (NULL);
	k = 0;
	while (k < len && s[start])
	{
		tab[k] = s[start];
		start++;
		k++;
	}
	tab[k] = '\0';
	return (tab);
}
