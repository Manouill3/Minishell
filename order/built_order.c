/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcybak <tcybak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:56:21 by tcybak            #+#    #+#             */
/*   Updated: 2025/02/18 18:03:00 by tcybak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void    ft_pwd(void)
{
    char *chemin = NULL;

    chemin = getcwd(NULL, 0); 
    printf("Le chemin du repertoire est %s\n", chemin);
    free(chemin);
}

void    ft_check_order(t_init *init)
{
    if (ft_strcmp(init->line, "pwd") == 0)
        ft_pwd();
    return ;
}