/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:35:17 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/07 14:11:39 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_print_arg(int n, int i, t_list_char *tok)
{
    if (n == 1 && tok->no_red[i])
    {
        while(tok->no_red[i] && tok->no_red[i + 1])
        {
            printf("%s ",tok->no_red[i]);
            i++;
        }
        printf("%s",tok->no_red[i]);
    }
    else if (n != 1 && tok->no_red[i])
    {
        while(tok->no_red[i] && tok->no_red[i + 1])
        {
            printf("%s ",tok->no_red[i]);
            i++;
        }
        printf("%s\n",tok->no_red[i]);
    }
}

void    ft_echo(t_init *param, t_list_char *tok)
{
    int i;
    int j;
    int n;
    (void)param;

    i = 0;
    j = 1;
    n = 0;
    if (tok->no_red[1] == NULL)
    {
        printf("\n");
        return ;
    }
    while (ft_strcmp(tok->no_red[i], "echo") || ft_strlen(tok->no_red[i]) <= 0)
        i++;
    i++;
    while (tok->no_red[i] && (!ft_strcmp(tok->no_red[i], "-n") || (tok->no_red[i][0] == '-' && tok->no_red[i][j] == 'n')))
    {
        n = 1;
        if (tok->no_red[i][j])
        {
            j = 1;
            i++;
        }
        j++;
    }
    param->status = 0;
    ft_print_arg(n, i, tok);
}
