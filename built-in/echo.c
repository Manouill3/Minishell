/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:35:17 by tcybak            #+#    #+#             */
/*   Updated: 2025/04/24 14:39:34 by tcybak           ###   ########.fr       */
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
    int n;

    i = 1;
    n = 0;
    printf("tok->cmd[i]%s\n", tok->cmd[0]);
    printf("tok->cmd[i]%s\n", tok->cmd[1]);
    if (tok->cmd[1] == NULL)
    {
        printf("\n");
        return ;
    }
    if (tok->cmd[1][0] == '$' && tok->cmd[1][1] == '?')
        printf("%d", param->exit);
    while (tok->cmd[i] && !ft_strcmp(tok->cmd[i], "-n"))
    {
        n = 1;
        i++;
    }
    ft_print_arg(n, i, tok);

}
