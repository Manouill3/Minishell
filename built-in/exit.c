/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:24:13 by tcybak            #+#    #+#             */
/*   Updated: 2025/05/01 17:20:12 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_exit(t_init *param)
{
    int nb_arg;
    int i;

    i = 0;
    nb_arg = 0;
    while (param->tok->cmd[i])
    {
        nb_arg++;
        i++;
    }
    if (nb_arg > 2)
    {
        param->status = 1;
        write(2, " too many arguments", 19);
        exit(param->status);
    }
    if (param->tok->cmd[1] != NULL)
        param->status = ft_atoi(param->tok->cmd[1]);
    nb_arg = param->status;
    ft_free_all(param);
    free_struct(param);
    printf("exit\n");
    exit(nb_arg);
}
