/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:28:15 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/25 15:22:33 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int get_quote(int i, const char *s)
{
    i++;
    while(s[i] != 39)
        i++;
    return(i);
}

int get_double_quote(int i, const char *s)
{
    i++;
    while(s[i] != '"')
        i++;
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

