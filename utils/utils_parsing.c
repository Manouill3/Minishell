/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:40:44 by mdegache          #+#    #+#             */
/*   Updated: 2025/02/20 10:58:09 by tcybak           ###   ########.fr       */
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
void    ft_free(t_init *init)
{
    if (init->line)
        free(init->line);
    if (init)
        free(init);
    return ;
}