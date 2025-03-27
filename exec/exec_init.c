/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:53:45 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/27 11:08:50 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_exec(t_init *init)
{
    init->fds->pid = fork();
    if (init->fds->pid == -1)
    {
        perror("pid");
        exit(1);
    }
    if (init->fds->pid == 0)
        printf("HERE1"); //child_process();
    else
        printf("HERE2"); //parent_process();
}


void    ft_init_exec(t_init *init)
{
    int i;
    int verif;
    int count_cmd;
    t_list_char *tmp;

    i = 0;
    count_cmd = 0;
    tmp = init->tok;
    while(tmp)
    {
        if (!ft_strcmp(tmp->name, "cmd"))
            count_cmd++;
        tmp = tmp->next;
    }
    tmp = init->tok;
    while(i < count_cmd)
    {
        verif = verif_build(tmp);
        if (count_cmd == 1 && verif == 1)
        {
            ft_check_order(init);
            return ;
        }
        if (verif == 0)
        {
                ft_exec(init);
        }
    }
}
