/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:28:15 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/26 10:24:21 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int get_quote(int i, const char *s)
{
    if (s[i] == 39)
    {
        i++;
        while(s[i] != 39)
            i++;
    }
    else
    {
        i++;
        while(s[i] != '"')
            i++;
    }
    return(i);
}

int ft_split_quote(const char *s, int k, int i, char **tab)
{
    int tmp;
    int count;
    char    q;
    int     j;

    q = s[k];
    tmp = k + 1;
    j = 0;
    k++;
    count = 0;
    while (s[tmp] != q)
    {
        tmp++;
        count++;
    }
    tab[i - 1] = ft_calloc(count + 1, sizeof(char));
    while (s[k] != q)
    {
        tab[i - 1][j] = s[k];
        j++;
        k++;
    }
    k++;
    return (k);
}

int ft_check_quote(const char *s, int k, int i, char **tab, char c)
{
    k = secu(k, c, s);
	if (s[k] == '"' || s[k] == 39)
	{
		k = ft_split_quote(s, k, i, tab);
		i++;
		k = secu(k, c, s);
	}
    return (k);
}

char    **exec_all(const char *s, int k, int i, char **tab, char c)
{
    int j;
    int nb_word;
    
    nb_word = len_first_tab(s, c);
    while (i++ < nb_word)
    {
        j = 0;
        k = ft_check_quote(s, k, i, tab, c);
        if (tab[i - 1] != NULL)
            i++;
        if (k > (int)ft_strlen(s) - 1)
            break;
        tab[i - 1] = ft_calloc(len_word(s, k, c) + 1, sizeof(char));
        if (!tab[i - 1])
            free_all(tab);
        while (s[k] != c && s[k])
            tab[i - 1][j++] = s[k++];
    }
    return (tab);
}

int is_white(char c)
{
    return ((c >= 9 && c <= 13) || c = 32)
}
