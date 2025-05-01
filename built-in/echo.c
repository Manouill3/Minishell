/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:35:17 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/01 14:08:57 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_print_arg(int n, int i, t_list_char *tok)
{
    if (n == 1 && tok->cmd[i])
    {
        while(tok->cmd[i] && tok->cmd[i + 1])
        {
            printf("%s ",tok->cmd[i]);
            i++;
        }
        printf("%s",tok->cmd[i]);
    }
    else if (n != 1 && tok->cmd[i])
    {
        while(tok->cmd[i] && tok->cmd[i + 1])
        {
            printf("%s ",tok->cmd[i]);
            i++;
        }
        printf("%s\n",tok->cmd[i]);
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
    if (tok->cmd[1] == NULL)
    {
        printf("\n");
        return ;
    }
    while (ft_strcmp(tok->cmd[i], "echo"))
        i++;
    i++;
    while (tok->cmd[i] && (!ft_strcmp(tok->cmd[i], "-n") || (tok->cmd[i][0] == '-' && tok->cmd[i][j] == 'n')))
    {
        n = 1;
        if (tok->cmd[i][j])
        {
            j = 1;
            i++;
        }
        j++;
    }
    ft_print_arg(n, i, tok);

}
