/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:56:21 by tcybak            #+#    #+#             */
/*   Updated: 2025/03/06 16:25:58 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char    *ft_pwd(void)
{
    char *way = NULL;

    way = getcwd(NULL, 0);
    if (!way) {
        free(way);
        perror("getcwd");
        return (NULL);
    }
    return (way);
}

void    ft_check_order(t_init *init)
{
    if (ft_strcmp(init->line, "pwd") == 0)
        ft_pwd();
    return ;
}