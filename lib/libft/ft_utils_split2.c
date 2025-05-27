/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_split2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:12:37 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/27 16:24:38 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**exec_all(const char *s, int k, t_mal *mal, char **tab)
{
	int	i;
	int	nb_word;

	i = 0;
	nb_word = len_first_tab(s);
	if (ft_strchr(s, '|'))
	{
		tab = split_ope(s, k, tab, mal);
		return (tab);
	}
	while (i++ < nb_word)
		tab[i - 1] = handle_quote(s, &k, tab[i - 1], mal);
	return (tab);
}

int	is_white(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
