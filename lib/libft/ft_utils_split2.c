/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_split2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:12:37 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/25 13:57:58 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**exec_all(const char *s, int k, int i, char **tab)
{
	int	nb_word;

	nb_word = len_first_tab(s);
	if (ft_strchr(s, '|') || ft_strchr(s, '<') || ft_strchr(s, '>'))
	{
		tab = split_ope(s, k, i, tab);
		return (tab);
	}
	while (i++ < nb_word)
		tab = handle_quote(s, &k, tab, i);
	return (tab);
}

int	is_white(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
