/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:20:20 by marvin            #+#    #+#             */
/*   Updated: 2025/05/13 19:20:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int    verif_nb_quote(char **tab)
{
    int    i;
    int    j;
    int    count1;
    int    count2;

    i = 0;
    count1 = 0;
    count2 = 0;
    while (tab[i])
    {
        j = 0;
        while (tab[i][j])
        {
            if (tab[i][j] == '"')
                count2++;
            if (tab[i][j] == 39)
                count1++;
            j++;
        }
        i++;
    }
    if (count1 % 2 != 0 || count2 % 2 != 0)
        return (1);
    return (0);
}

int no_supp_redir(char *line, int i)
{
    
    return (0);
}