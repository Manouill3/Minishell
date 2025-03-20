/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:28:15 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/20 19:03:50 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_ope(char c)
{
	int	i;

	i = 0;
	if (c == '|' || c == '<' || c == '>')
		i = 1;
	return (i);
}

int	get_quote(int i, const char *s, char c)
{
	i++;
	while (s[i] != c)
		i++;
	return (i);
}

int	ft_split_quote(const char *s, int k, int i, char **tab)
{
	int		tmp;
	int		count;
	char	q;
	int		j;

	q = s[k];
	tmp = k + 1;
	j = 0;
	k++;
	count = 2;
	while (s[tmp] != q)
	{
		tmp++;
		count++;
	}
	tab[i - 1] = ft_calloc(count + 1, sizeof(char));
	tab[i - 1][j++] = q;
	while (s[k] != q)
	{
		tab[i - 1][j] = s[k];
		j++;
		k++;
	}
	tab[i - 1][j] = s[k];
	return (k);                                                                                                           
}

int	ft_check_quote(const char *s, int k, int i, char **tab)
{
	if (s[k] == '"' || s[k] == 39)
	{
		k = ft_split_quote(s, k, i, tab);
		k++;
		i++;
		k = secu(k, s);
	}
	return (k);
}

char	**split_ope(const char *s, int k, int i, char **tab)
{
	int	j;
	int	nb_word;
	
	nb_word = len_first_tab(s);
	while (i++ < nb_word)
	{
		j = 0;
		k = secu(k, s);
		if (is_ope(s[k]) == 1)
		{
			tab[i - 1] = ft_calloc(len_word(s, k) + 1, sizeof(char));
			while (is_ope(s[k]) == 1)
				tab[i - 1][j++] = s[k++];
		}
		if (tab[i - 1] != NULL)
			i++;
		if (k < (int)ft_strlen(s) && i - 1 < nb_word)
		{
			k = secu(k, s);
			j = 0;
			tab[i - 1] = ft_calloc(len_word(s, k) + 1, sizeof(char));
			if (!tab[i - 1])
				free_all(tab);
			while (s[k] && is_white(s[k]) != 1 && is_ope(s[k]) != 1)
			{
				if (s[k] == '"' || s[k] == 39)
				{
					tab[i - 1][j++] = s[k++];
					while (s[k] && s[k] != '"' && s[k] != 39)
						tab[i - 1][j++] = s[k++];
					tab[i - 1][j++] = s[k++];
				}
				else
					tab[i - 1][j++] = s[k++];
			}
		}
	}
	return (tab);
}

char	**exec_all(const char *s, int k, int i, char **tab)
{
	int	j;
	int	nb_word;

	nb_word = len_first_tab(s);
	if (ft_strchr(s, '|') || ft_strchr(s, '<') || ft_strchr(s, '>'))
	{
		tab = split_ope(s, k, i, tab);
		return(tab);
	}
	while (i++ < nb_word)
	{
		j = 0;
		k = secu(k, s);
		tab[i - 1] = ft_calloc(len_word(s, k) + 1, sizeof(char));
		if (!tab[i - 1])
			free_all(tab);
		while (is_white(s[k]) != 1 && s[k])
		{
			if (s[k] == '"' || s[k] == 39)
			{
				while (s[k] && s[k] != '"' && s[k] != 39)
					tab[i - 1][j++] = s[k++];	
			}
			else
				tab[i - 1][j++] = s[k++];
		}
	}
	return (tab);
}

int	is_white(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}



// k = ft_check_quote(s, k, i, tab);
		// if (k == tmp)
		// { 
		// }